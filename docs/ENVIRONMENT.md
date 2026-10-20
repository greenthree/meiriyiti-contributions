# 环境配置说明（供 AI 阅读）

投稿者使用 README 中的提示词即可。Agent 负责检查、安装和验证环境，不要求投稿者逐条执行命令。

## 支持环境

- Windows 或 Linux x86_64；当前 ProbHub 0.7.1 不支持原生 macOS，遇到不支持的平台应如实说明。
- Git、Node.js 22、CPython 3.11、g++。
- ProbHub 固定为 0.7.1，Python 依赖使用该包附带的 requirements.lock。
- 提交投稿需要 GitHub CLI（gh）和投稿者自己的 GitHub 登录。没有写权限时使用 Fork 和 PR。
- 投稿者本地验证不要求安装 Docker；PR 的隔离验证由 GitHub Actions 执行。

## 安装项目依赖

先确认基础工具可用，再在投稿仓库根目录安装 ProbHub 并创建虚拟环境：

    npm install -g probhub@0.7.1
    python -m venv .venv

Windows PowerShell：

    .\.venv\Scripts\Activate.ps1
    $probhubRoot = Join-Path (npm root -g) "probhub"
    python -m pip install -r (Join-Path $probhubRoot "requirements.lock")

Linux：

    source .venv/bin/activate
    python -m pip install -r "$(npm root -g)/probhub/requirements.lock"

后续操作使用该虚拟环境的 Python。不要为了安装依赖而覆盖已有题目、清空工作区或修改投稿规范。

## 实际检查

检查 Git、Node.js、Python、g++、ProbHub 和 gh 是否能执行，并核对版本。
确认虚拟环境能导入 yaml，并执行 python tools/contribution.py --help，不能把安装成功直接当作验证完成。

提交前用 gh auth status 检查登录；需要登录时引导投稿者通过浏览器完成。
作者署名、来源与发布修改授权必须由本人确认，不替作者填入同意，不索取密码或令牌。

题目验证与交付继续遵守 AGENTS.md，统一使用 prepare/check 等投稿工具；
不要对本项目题面直接运行 ProbHub 0.7.1 的原生 lint。
