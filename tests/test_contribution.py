import copy
import json
import os
from pathlib import Path
import sys
import shutil
import subprocess
import tempfile
import unittest
from unittest.mock import patch
import zipfile

import yaml

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "tools"))
import contribution as c
import review


def fixture(root):
    root = Path(root)
    problem = root / c.DRAFT_ID
    (problem / "code").mkdir(parents=True)
    (problem / "data/sample").mkdir(parents=True)
    (problem / "data/secret").mkdir()
    for name in ("validator.cpp", "std.cpp", "std2.cpp", "wrong.cpp", "inmaker.cpp"):
        (problem / "code" / name).write_text("int main() {}\n", encoding="utf-8")
    cfg = {
        "schema_version": 1, "id": c.DRAFT_ID, "name": "测试题", "difficulty": 0,
        "limits": {"time": 1, "memory": 256},
        "statement": {"source": "problem.md"}, "judge": {"type": "standard", "validator": "code/validator.cpp"},
        "solutions": {
            "accepted": [
                {"file": "code/std.cpp", "expected": {"status": "AC", "all": True}},
                {"file": "code/std2.cpp", "expected": {"status": "AC", "all": True},
                 "independence": {"from": "code/std.cpp", "basis": "algorithm", "note": "独立实现"}},
            ],
            "wrong": [{"file": "code/wrong.cpp", "expected": {"status": "WA"}}],
        },
        "stress": {"generator": "code/inmaker.cpp", "brute": "code/std2.cpp"},
        "data": {"sample_dir": "data/sample", "secret_dir": "data/secret",
                 "recipes": [{"case": f"test{i:02d}", "manual": True} for i in range(10)]},
    }
    (problem / "probhub.yaml").write_text(yaml.safe_dump(cfg, allow_unicode=True), encoding="utf-8")
    (problem / "problem.md").write_text(
        "# 测试题\n\n### 题面描述\n内容\n### 输入描述\n输入\n### 输出描述\n输出\n"
        "### 样例\n**样例输入：**\n### 提示\n提示\n", encoding="utf-8")
    (root / "solution.md").write_text(
        "# 测试题 题解\n\n## 1. 题意简述\n\n## 2. 解题思路\n\n## 3. 常见易错点\n\n"
        "## 4. 参考代码与语法精讲\n\n### 4.1 C++ 参考代码\n\n### 4.2 Python 参考代码\n",
        encoding="utf-8")
    for folder, names in (("sample", ["sample1"]), ("secret", [f"test{i:02d}" for i in range(10)])):
        for name in names:
            (problem / "data" / folder / f"{name}.in").write_bytes(b"1\n")
            (problem / "data" / folder / f"{name}.ans").write_bytes(b"2")
    c.write_workspace(root, c.DRAFT_ID, "测试题")
    c.write_json(root / "contribution.json", {
        "schema_version": 1, "problem_id": c.DRAFT_ID, "topic": "测试",
        "authors": [{"name": "投稿人"}], "permission": "允许署名发布、修改并用于本项目教学与评测",
        "source": "原创",
    })
    c.package_data(problem)
    return cfg


class ContributionTests(unittest.TestCase):
    def setUp(self):
        self.temp = tempfile.TemporaryDirectory()
        self.addCleanup(self.temp.cleanup)
        self.root = Path(self.temp.name) / "submission"
        self.cfg = fixture(self.root)
        self.problem = self.root / c.DRAFT_ID

    def update_config(self, update):
        cfg = copy.deepcopy(self.cfg)
        update(cfg)
        (self.problem / "probhub.yaml").write_text(yaml.safe_dump(cfg, allow_unicode=True), encoding="utf-8")

    def test_valid_submission_and_copy_excludes_local_evidence(self):
        c.validate_submission(self.root)
        (self.problem / ".probhub").mkdir()
        (self.problem / ".probhub/judge-evidence-v2.json").write_text("{}", encoding="utf-8")
        target = Path(self.temp.name) / "copied"
        c.copy_problem(self.problem, target)
        self.assertFalse((target / ".probhub").exists())
        self.assertEqual((target / "data.zip").read_bytes(), (self.problem / "data.zip").read_bytes())

    def test_rejects_stale_zip(self):
        (self.problem / "data/secret/test00.ans").write_bytes(b"3\n")
        with self.assertRaisesRegex(ValueError, "不一致"):
            c.validate_submission(self.root)

    def test_rejects_extra_file_in_zip(self):
        with zipfile.ZipFile(self.problem / "data.zip", "a") as archive:
            archive.writestr("../evil", b"x")
        with self.assertRaisesRegex(ValueError, "平铺"):
            c.validate_submission(self.root)

    def test_rejects_missing_recipe(self):
        self.update_config(lambda cfg: cfg["data"]["recipes"].pop())
        with self.assertRaisesRegex(ValueError, "recipes"):
            c.validate_submission(self.root)

    def test_rejects_missing_second_solution(self):
        self.update_config(lambda cfg: cfg["solutions"]["accepted"].pop())
        with self.assertRaisesRegex(ValueError, "独立标程"):
            c.validate_submission(self.root)

    def test_rejects_validator_escape(self):
        self.update_config(lambda cfg: cfg["judge"].update(validator="../validator.cpp"))
        with self.assertRaisesRegex(ValueError, "不安全"):
            c.validate_submission(self.root)

    def test_rejects_difficulty_and_interactive(self):
        for change in (lambda cfg: cfg.update(difficulty=1),
                       lambda cfg: cfg["judge"].update(type="interactive")):
            self.update_config(change)
            with self.assertRaises(ValueError):
                c.validate_submission(self.root)

    def test_rejects_unconsented_submission(self):
        metadata = c.read_json(self.root / "contribution.json")
        metadata["permission"] = ""
        c.write_json(self.root / "contribution.json", metadata)
        with self.assertRaisesRegex(ValueError, "授权"):
            c.validate_submission(self.root)

    def test_rejects_non_source_files_and_case_collisions(self):
        (self.problem / "hook.sh").write_text("echo bad", encoding="utf-8")
        with self.assertRaisesRegex(ValueError, "规范源"):
            c.validate_submission(self.root)

    def test_rejects_symlink(self):
        path = self.problem / "code/link.cpp"
        try:
            path.symlink_to(self.problem / "code/std.cpp")
        except OSError:
            self.skipTest("当前用户无创建符号链接权限")
        with self.assertRaisesRegex(ValueError, "符号链接"):
            c.validate_submission(self.root)

    def test_paths_reject_windows_and_posix_escapes(self):
        for path in ("../x", "/tmp/x", "C:/x", "code\\x", "code/../x", "code/NUL.cpp",
                     "code/x.", "code/x ", ".github/x"):
            with self.subTest(path=path), self.assertRaises(ValueError):
                c.safe_relative(path)

    def test_changed_targets_enforces_one_submission(self):
        self.assertEqual(review.changed_targets(["submissions/a/P0001/problem.md"], "submission"), ["a"])
        for paths in (["submissions/a/x", "submissions/b/y"], ["submissions/a/x", "tools/x"]):
            with self.assertRaises(ValueError):
                review.changed_targets(paths, "submission")
        self.assertEqual(review.changed_targets(["tools/x"], "submission"), [])
        self.assertEqual(review.changed_targets(["Solution/26DAY36.md"], "official"), ["26DAY36"])

    def test_core_view_adapts_only_headings_outside_fences(self):
        original = "### 题面描述\n正文\n### 样例\n~~~text\n### 输入描述\n~~~\n### 输入描述\n正文\n"
        converted = c.core_statement(original)
        self.assertEqual(converted, "## 题目描述\n正文\n**样例**\n~~~text\n### 输入描述\n~~~\n## 输入格式\n正文\n")

    def test_sample_text_that_looks_like_headings_is_not_a_markdown_heading(self):
        path = self.problem / "problem.md"
        with path.open("a", encoding="utf-8") as stream:
            stream.write("\n~~~text\n# sample output\n### 样例输入\n~~~\n")
        c.validate_submission(self.root)

    def test_hidden_git_attributes_cannot_be_imported(self):
        (self.problem / "code/.gitattributes").write_text("* filter=unsafe\n", encoding="utf-8")
        with self.assertRaisesRegex(ValueError, "Git"):
            c.validate_submission(self.root)

    def test_container_has_no_credentials_network_or_host_socket(self):
        args = review.container_command("image", self.root, "P0001", "submission")
        for flag in ("--network=none", "--cap-drop=ALL", "--read-only", "--user=10001:10001",
                     "--security-opt=no-new-privileges"):
            self.assertIn(flag, args)
        self.assertNotIn("--privileged", args)
        self.assertNotIn("-e", args)
        self.assertNotIn("docker.sock", " ".join(args))

    def test_verification_checks_final_codes_and_completed_rounds(self):
        def results(root, command, *args):
            if command == "sample-check":
                return {"ok": True, "problems": {c.DRAFT_ID: {"final": {"code": "sample_answers_match"}}}}
            if command == "judge":
                return {"ok": True, "problems": {c.DRAFT_ID: {"final": {"code": "all_expectations_met"}}}}
            if command == "stress":
                return {"ok": True, "problems": {c.DRAFT_ID: {
                    "status": "passed", "rounds_completed": 99, "counterexample": None}}}
            return {"ok": True, "problems": []}
        with patch.object(c, "run_probhub", side_effect=results), self.assertRaisesRegex(ValueError, "100"):
            c.verify_problem(self.root, c.DRAFT_ID, self.root / "solution.md")

    def test_failed_prepare_preserves_original_data_and_statement(self):
        paths = [self.problem / "data.zip", self.problem / "problem.md",
                 self.problem / "data/secret/test00.ans"]
        before = {path: path.read_bytes() for path in paths}
        with patch.object(c, "verify_problem", side_effect=ValueError("Judge failure")), \
                self.assertRaisesRegex(ValueError, "Judge failure"):
            c.prepare_submission(self.root)
        for path, content in before.items():
            self.assertEqual(path.read_bytes(), content)

    def test_review_timeout_always_removes_daemon_side_container(self):
        repo = Path(self.temp.name) / "repo"
        shutil.copytree(self.root, repo / "submissions/test")
        diff = subprocess.CompletedProcess(["git"], 0, stdout=b"submissions/test/P0001/problem.md\0")
        calls = [diff, subprocess.TimeoutExpired("docker", 1800), subprocess.CompletedProcess(["docker"], 0)]
        with patch.object(sys, "argv", ["review", "--source", str(repo), "--base", "a" * 40,
                                      "--head", "b" * 40]), \
                patch.object(review.subprocess, "run", side_effect=calls) as run, \
                self.assertRaises(subprocess.TimeoutExpired):
            review.main()
        self.assertEqual(run.call_args_list[-1].args[0][:3], ["docker", "rm", "-f"])

    @unittest.skipIf(os.name == "nt", "Requires POSIX directory permissions")
    def test_review_staging_is_traversable_by_the_container_uid(self):
        repo = Path(self.temp.name) / "repo"
        shutil.copytree(self.root, repo / "submissions/test")
        observed = []

        def run(args, **kwargs):
            if args[0] == "git":
                return subprocess.CompletedProcess(args, 0, stdout=b"submissions/test/P0001/problem.md\0")
            if args[:2] == ["docker", "run"]:
                mount = args[args.index("--mount") + 1]
                staged = Path(mount.split("source=", 1)[1].split(",target=", 1)[0])
                self.assertEqual(staged.stat().st_mode & 0o777, 0o755)
                for path in staged.rglob("*"):
                    mode = path.stat().st_mode
                    self.assertTrue(mode & 0o004, str(path))
                    if path.is_dir():
                        self.assertTrue(mode & 0o001, str(path))
                self.assertIn("--user=10001:10001", args)
                self.assertIn("readonly", mount)
                observed.append(staged)
            return subprocess.CompletedProcess(args, 0)

        with patch.object(sys, "argv", ["review", "--source", str(repo), "--base", "a" * 40,
                                      "--head", "b" * 40]), \
                patch.object(review.subprocess, "run", side_effect=run):
            review.main()
        self.assertEqual(len(observed), 1)


if __name__ == "__main__":
    unittest.main()
