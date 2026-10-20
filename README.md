# 每日一题 · 投稿与审稿

本仓库接收算法竞赛每日一题的 GitHub PR 投稿。请先阅读 [AGENTS.md](AGENTS.md)。
这是公开仓库，题面、标程、数据、题解在提交 PR 时即公开。正式发布由维护者另外排期。

## 出题提示词模板

复制下面的模板，将【】中的内容替换为你的需求后，交给具备本地代码执行能力的 AI Agent。

~~~text
请先阅读并遵守本仓库的 AGENTS.md，使用 ProbHub 0.7.1，完成一份可提交 PR 的每日一题投稿。
请实际编写文件、生成数据并执行验证，遇到失败应定位原因、修复后重跑，如实报告未完成项。

我的出题需求：
- 投稿标识 slug：【小写英文、数字与连字符，例如 array-walk】
- 题目名称或创意方向：【填写题名、背景或希望解决的问题】
- 核心考点：【填写考点，例如一维数组与循环】
- 面向人群与学习阶段：【例如刚学完一维数组的大一新生】
- 允许使用的知识与语法：【填写范围，不得超前引入未学内容】
- 训练难度与预期复杂度：【填写教学难度、预期做法及复杂度；probhub.yaml 的 difficulty 仍固定为 0】
- 作者署名与来源：【填写署名；原创或改编须由作者说明，改编附来源链接】
- 发布修改授权：【由作者本人确认是否同意“允许署名发布、修改并用于本项目教学与评测”】
- 其他要求：【例如无输入、输出精度、背景风格或数据规模；无则填“无”】

执行要求：
1. 使用 tools/contribution.py new 创建 submissions/<slug>/ 独立工作区，内部题目 ID 固定为 P0001。
   先给出算法、正确性依据、约束与典型错法，再完成题目；正式 DAY 编号由维护者在录用后分配。
2. 按 AGENTS.md 编写 probhub.yaml 与 problem.md，完整呈现样例、解释及输入输出约束。
   题面必须清晰严谨；不能卡常，也不能把选手输出末行缺少换行作为错误。
3. 提供 testlib 输入校验器、两份独立标程 std.cpp/std2.cpp、生成器及分层错解矩阵，
   声明 std2 独立性，并用数据组明确哪些测试点击杀哪些错解。
4. 设计 10 ~ 20 个隐藏测试点，覆盖边界、极值和典型错误；全部登记 recipes，使用 LF，
   通过固定种子复现。采用 standard 或 C++ Checker 的 custom；custom 必须提供 Checker QA。
5. 编写 solution.md，包含题意、思路与复杂度、常见易错点、C++/Python 参考代码及语法讲解。
   面向新生使用朴素语法，不使用快读快写或超出学习阶段的技巧。
6. 填写 contribution.json 的作者、考点、来源与授权。不得替作者确认原创性或发布授权；
   缺少必要信息时列出缺项，并先推进不依赖这些信息的工作。
7. 在仓库根目录运行：
   python tools/contribution.py prepare submissions/<slug>
   python tools/contribution.py check submissions/<slug>
   通过统一工具完成 Lint、样例检查、数据生成、Judge、Checker QA（如适用）及 100 轮 Stress，
   最终 Lint 零错误零警告；验证成功后交付包含全部 sample/secret 数据的平铺 data.zip。
8. 只修改这一份投稿；不要通过修改工具或降低验证标准来绕过失败。
   不生成 PDF、DOMjudge 包或缓存交付物，不操作 OJ、QQ 或正式发布索引。

完成后列出交付目录、算法与复杂度、错解覆盖、实际验证结果，以及仍需人工审查的事项。
若依赖、权限或执行环境导致某一步无法完成，请明确标记，不得声称已验证通过。
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
