# 环境配置说明

可以让 AI 按本文检查、安装和验证环境，也可以自行按步骤配置。

## 支持环境

- Windows 或 Linux x86_64；当前 ProbHub 0.7.1 不支持原生 macOS，遇到不支持的平台应如实说明。
- Git、Node.js 22、CPython 3.11、g++。
- ProbHub 固定为 0.7.1，Python 依赖使用该包附带的 requirements.lock。
- GitHub CLI（gh）可用于投稿者自行提交，也可供 AI 代提交；使用投稿者自己的账号登录。投稿统一先 Fork 到自己的账号，再从自己的 Fork 向原仓库发起 PR，也可以通过网页完成。
- Fork 时只复制 main，克隆时使用 git clone --single-branch --branch main <自己的 Fork 地址>，避免下载其他投稿分支。题目只留在 PR 中，录用后导入正式题库并关闭 PR，不合并进投稿仓库 main。
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

检查 Git、Node.js、Python、g++ 和 ProbHub 是否能执行，并核对版本；使用 GitHub CLI 提交时另外检查 gh。
确认虚拟环境能导入 yaml，并执行 python tools/contribution.py --help，不能把安装成功直接当作验证完成。

使用 gh 提交前，用 gh auth status 检查登录；需要登录时引导投稿者通过浏览器完成。
作者署名、来源与发布修改授权必须由本人确认，不替作者填入同意，不索取密码或令牌。

题目验证与交付继续遵守 AGENTS.md，统一使用 prepare/check 等投稿工具；
不要对本项目题面直接运行 ProbHub 0.7.1 的原生 lint。
