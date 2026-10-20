"""Run changed submissions in disposable, offline, unprivileged containers."""

import argparse
import json
from pathlib import Path
import re
import subprocess
import tempfile
import uuid

import yaml

from contribution import DRAFT_ID, SLUG, copy_problem, validate_problem, validate_submission, write_workspace


def changed_targets(paths, mode):
    if mode == "submission":
        slugs = set()
        for path in paths:
            parts = path.split("/")
            if parts[0] == "submissions":
                if len(parts) < 3 or not SLUG.fullmatch(parts[1]):
                    raise ValueError(f"投稿路径无效: {path}")
                slugs.add(parts[1])
        if slugs and (len(slugs) != 1 or any(
            not p.startswith(f"submissions/{next(iter(slugs))}/") for p in paths
        )):
            raise ValueError("每个投稿 PR 只修改一份投稿；工具和规范修改请单独提 PR")
        return sorted(slugs)
    return sorted({
        match[1] for path in paths
        if (match := re.match(r"^(26DAY\d{2,})(?:/|$)", path))
        or (match := re.fullmatch(r"Solution/(26DAY\d{2,})\.md", path))
    })


def container_command(image, staged, target, mode, name=None):
    return [
        "docker", "run", "--rm", "--init", "--name", name or f"daily-review-{uuid.uuid4().hex}",
        "--network=none", "--cap-drop=ALL",
        "--security-opt=no-new-privileges", "--pids-limit=256",
        "--memory=4g", "--cpus=2", "--read-only", "--user=10001:10001",
        "--tmpfs=/tmp:rw,exec,nosuid,size=2g,mode=1777",
        "--mount", f"type=bind,source={Path(staged).resolve()},target=/input,readonly",
        image, mode, target,
    ]


def validate_official_index(source):
    source = Path(source)
    calendar = json.loads((source / "daily_problems.json").read_text(encoding="utf-8"))
    entries = calendar["problems"]
    numbers = []
    for item in entries:
        pid = item["id"]
        if not re.fullmatch(r"26DAY\d{2,}", pid) or int(pid[5:]) != int(item["day"]):
            raise ValueError("正式发布索引 day/id 不一致")
        numbers.append(int(item["day"]))
        if not (source / pid).is_dir() or not (source / "Solution" / f"{pid}.md").is_file():
            raise ValueError(f"索引中的题目或题解缺失: {pid}")
    if not numbers or len(numbers) != len(set(numbers)) or set(numbers) != set(range(max(numbers) + 1)):
        raise ValueError("正式发布索引必须连续且不重复")
    workspace = yaml.safe_load((source / ".probhub/workspace.yaml").read_text(encoding="utf-8"))
    registered = workspace["problems"]
    ids = [item["id"] for item in registered]
    if len(ids) != len(set(ids)) or any(
        not any(w["id"] == item["id"] and w["directory"] == item["id"] for w in registered)
        for item in entries
    ):
        raise ValueError("工作区与每日发布索引不一致")


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--source", type=Path, required=True)
    parser.add_argument("--base", required=True)
    parser.add_argument("--head", required=True)
    parser.add_argument("--mode", choices=("submission", "official"), default="submission")
    parser.add_argument("--image", default="daily-contribution-review")
    args = parser.parse_args()
    for sha in (args.base, args.head):
        if not re.fullmatch(r"[0-9a-f]{40}", sha):
            raise ValueError("必须指定完整 Git SHA")
    changed = subprocess.run(
        ["git", "-C", str(args.source), "diff", "--name-only", "--no-renames", "-z",
         f"{args.base}...{args.head}"], capture_output=True, check=True
    ).stdout.decode("utf-8").split("\0")
    paths = [p for p in changed if p]
    targets = changed_targets(paths, args.mode)
    if args.mode == "official":
        validate_official_index(args.source)
    if not targets:
        print("无题目变更；由工具测试检查本次修改。")
    for target in targets:
        container_name = f"daily-review-{uuid.uuid4().hex}"
        with tempfile.TemporaryDirectory(prefix="daily-input-") as tmp:
            staged = Path(tmp)
            if args.mode == "submission":
                source = args.source / "submissions" / target
                metadata, cfg = validate_submission(source)
                copy_problem(source / DRAFT_ID, staged / DRAFT_ID)
                for name in ("solution.md", "contribution.json"):
                    (staged / name).write_bytes((source / name).read_bytes())
                write_workspace(staged, DRAFT_ID, cfg["name"])
                command = container_command(args.image, staged, DRAFT_ID, "submission", container_name)
            else:
                source = args.source / target
                solution = args.source / "Solution" / f"{target}.md"
                cfg = validate_problem(source, target, solution)
                copy_problem(source, staged / target)
                (staged / "solution.md").write_bytes(solution.read_bytes())
                write_workspace(staged, target, cfg["name"])
                command = container_command(args.image, staged, target, "official", container_name)
            # TemporaryDirectory is 0700 on Linux; the container runs as a different UID.
            # Only this credential-free staged input is exposed, and its mount stays read-only.
            staged.chmod(0o755)
            try:
                subprocess.run(command, check=True, timeout=1800)
            finally:
                # Killing the Docker client on timeout does not stop its daemon-side container.
                subprocess.run(["docker", "rm", "-f", container_name], check=False,
                               capture_output=True, timeout=30)


if __name__ == "__main__":
    try:
        main()
    except (ValueError, OSError, KeyError, TypeError, subprocess.SubprocessError) as error:
        raise SystemExit(str(error))
