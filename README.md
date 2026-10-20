# 每日一题 · 投稿与审稿

本仓库接收算法竞赛每日一题的 GitHub PR 投稿。请先阅读 [AGENTS.md](AGENTS.md)。
这是公开仓库，题面、标程、数据、题解在提交 PR 时即公开。正式发布由维护者另外排期。

## 出题提示词模板

复制下面的模板，填写【】中的内容后交给 Agent：

~~~text
请先完整阅读并遵守本仓库的 AGENTS.md，按其中规范和流程完成一道每日一题投稿。

题目方向与考点：【填写】
面向人群及已学知识：【填写】
投稿标识（slug）：【填写】
作者署名与来源：【填写】

请实际完成题面、代码、数据和题解，执行规定的验证流程，最后汇报交付文件与验证结果。
~~~

## 环境与创建投稿

需要 Node.js 22、CPython 3.11、g++，固定使用 ProbHub 0.7.1。

    npm install -g probhub@0.7.1
    python -m venv .venv

激活虚拟环境后，安装 ProbHub 自带的依赖锁：

PowerShell：

    .\.venv\Scripts\Activate.ps1
    $probhubRoot = Join-Path (npm root -g) "probhub"
    python -m pip install -r (Join-Path $probhubRoot "requirements.lock")

Linux：

    source .venv/bin/activate
    python -m pip install -r "$(npm root -g)/probhub/requirements.lock"

Fork 并克隆本仓库，创建分支，然后执行：

    python tools/contribution.py new my-problem --title "题目名称" --author "作者署名" --topic "考点"

custom 题添加 --judge custom。每份投稿有独立 Workspace，内部固定使用 P0001，互不抢占正式 DAY 编号。
生成的骨架只是起点：按 AGENTS.md 补齐双标程、错解矩阵、10 ~ 20 个数据配方与完整教学题解。
编辑 contribution.json，填写原创/改编来源，并主动填入发布修改授权。

## 验证与交稿

在仓库根目录执行统一命令：

    python tools/contribution.py prepare submissions/my-problem
    python tools/contribution.py check submissions/my-problem

prepare 在临时副本中依次执行 Lint、Sample Check、Gen、Judge、Checker QA（如适用）、
100 轮固定 seed Stress 和最终零错误零警告 Lint。全部通过后才将数据及平铺 data.zip 写回。
本地会执行自己编写的题目代码；其他作者的稿件交给隔离 CI 或在审查后验证。
仓库三级标题和内嵌样例在临时副本中转换为 ProbHub 0.7.1 的二级标题视图；
规范源题面保持原格式。不要对这份规范源直接执行该版本的原生 lint。
已经生成 data.zip 后，可用 verify 命令重复验证并检查生成数据能否精确复现。

提交这一份 submissions/my-problem/，发起 PR 并填写模板。不提交缓存、PDF 或 DOMjudge 包。
CI 会使用目标分支的审核工具，隔离运行投稿代码，重复完整验证，并核对生成数据与 data.zip。

## 维护者录用

CI 通过后人工审稿，添加 accepted 标签。以审核通过的 PR head SHA 导入正式仓库，
在正式仓库分配 DAY 编号并创建入库 PR。投稿 PR 可以合并归档，导入仍使用原 head SHA。
录用后的正式修订集中在正式仓库；这里保留投稿和审稿记录。

本仓库不连接 OJ 或 QQ，不保存生产 Secrets。共享工具源保存在正式仓库的 contribution-kit/，
更新时整体同步，避免两个仓库分别实现校验规则。
