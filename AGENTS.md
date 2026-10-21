# 每日一题投稿仓库 — Agent 与出题协作规范

本规范参考正式仓库的 AGENTS.md，保留相同的题目质量、数据与教学要求。
这里是公开投稿与审稿工作区；正式 DAY 编号、日历排期、OJ 上传和公告由正式仓库维护。

## 1. 工作区与编号

- 每个 PR 只提交一份 submissions/<slug>/，slug 使用小写英文、数字及单连字符。
- 每份投稿是独立的 ProbHub Workspace Schema v1，内部固定使用 P0001。
- 不自行分配 26DAY 编号，不修改其他投稿、tools/、工作流或本规范。工具与规范修改另提 PR。
- 使用 tools/contribution.py new 创建独立工作区，不在仓库根目录运行 probhub new。
- 投稿全部公开，包括 PR 中的题面、标程、数据与题解。录用以 accepted 标签为准，不表示已经发布。
- 投稿内容只保留在 PR 中，不合并进本仓库 main；main 只维护工具、规范和文档。

标准布局：

    submissions/<slug>/
      .probhub/workspace.yaml
      contribution.json
      solution.md
      P0001/
        probhub.yaml
        problem.md
        code/
        assets/                  # 可选题面资源
        judge-fixtures/          # custom Checker QA，可选
        data/sample/
        data/secret/
        data.zip

## 2. 规范源与生成物边界

- 工作区登记唯一题目：id: P0001，directory: P0001。
- 题目配置必须为 schema_version: 1、id: P0001、difficulty: 0。
- 规范源包括工作区配置、probhub.yaml、problem.md、code/、assets/、judge-fixtures/ 和 data/。
- contribution.json 登记作者、考点、原始来源与授权；solution.md 为官方题解源。
- 禁止手改 meta.json、problems.json、problem.yaml、domjudge-problem.ini、Manifest、generation、checkpoint 和 Judge evidence。
- 不提交 .exe、编译缓存、临时日志、对拍缓存或其他本地生成物。
- 不生成 PDF；不执行 probhub typeset、build、package、checkpoint、seal、verify-package 或 status。
- 唯一必需交付归档是 P0001/data.zip；它在 Judge 与 Stress 通过后由工具平铺生成。
- 不允许链接、越界路径、可执行钩子；每文件至多 64 MiB，每份题目规范源及数据合计至多 512 MiB。

## 3. 题面规范

- problem.md 恰好一个 H1：# <题名>，题名与 probhub.yaml 的 name 完全一致。
- 顺序使用三级标题：题面描述、输入描述、输出描述、样例、提示。
- 样例必须在 Markdown 内完整呈现，并与 data/sample 中的正式样例一致。
- 样例输入、样例输出使用粗体标签和代码块，严禁用含“样例输入/输出”的 Markdown 标题。
- 样例解释使用四级标题：#### 样例解释 #1：，依序编号。
- 数学变量与范围使用 LaTeX 行内公式，乘号使用 \times。
- 引言寄语写在 statement.quote 中，不放在 H1 下。
- 无输入题统一表述“本题无输入。”，样例 .in 为 0 字节。
- 所有题目不强求末行换行；不得把选手输出末尾缺少换行当作 WA/PE。
- 严禁含糊题意、无逻辑特判、卡常和仅针对已有标程的弱数据。

## 4. 代码矩阵

- code/validator.cpp 使用 testlib.h、registerValidation，严格校验范围、格式、逻辑约束与 EOF。
- code/std.cpp 与 code/std2.cpp 是两份独立实现，均声明 expected: {status: AC, all: true}。
- std2.cpp 声明 independence.from: code/std.cpp，basis 为 algorithm 或 key_implementation，
  并用 note 说明具体独立性。独立性来自算法或关键实现差异，不来自作者/模型名称。
- code/wrong*.cpp 覆盖思路层、复杂度层和实现层的典型错误，在数据组中明确定向击杀。
- 错解不得依靠末行换行差异被击杀。Validator、Checker 的 FAIL 或基础设施故障不能算错解击杀。
- code/inmaker.cpp 使用 testlib.h，main 开头调用 registerGen(argc, argv, 1)，只向 stdout 输出数据。
- stress.generator 位于 code/ 内，stress.brute 固定指向 code/std2.cpp，用独立第二标程对拍。
- 所有代码路径必须是题目目录内的 code/...，不得指向父目录或其他投稿。
- 当前 OJ 发布链支持 standard 和 C++ Checker 的 custom，暂不接收 interactive。
- custom 必须配置 judge.checker 与 judge.qa，真实运行 Checker QA。
  说明 OJ Checker 协议兼容性；不能仅因本地 ProbHub 评测通过就承诺 OJ 兼容。
- 禁止访问凭据、网络、宿主文件、执行破坏操作或绕过资源限制的程序。

## 5. 数据纪律

- 隐藏测试点控制在 10 ~ 20 个，覆盖边界、极值与典型错解，不能以数量代替强度。
- data/sample/ 和 data/secret/ 使用成对的同名 .in 与 .ans，sample 与 secret 之间不得重名。
- 所有文件使用 LF；选手输出末行有无换行均应视为等价。
- secret 每个测试点都在 data.recipes 中登记，严禁孤儿测试点。
- 手工构造数据声明 manual: true；其余使用 generator 与确定性 args。
- Gen 必须能复现提交的数据；CI 不会以新生成数据静默替换不一致的投稿。
- data.zip 根目录直接是全部样例和隐藏测试点，不包含 sample/、secret/ 等子目录。

## 6. 验证 SOP

先按 [环境配置说明](docs/ENVIRONMENT.md) 准备工具和依赖，使用固定版本 ProbHub 0.7.1，补齐规范源。仓库根目录执行：

    python tools/contribution.py prepare submissions/<slug>

工具在临时副本中按顺序执行：Lint → Sample Check --no-cache → Gen --apply →
Judge --no-cache → Checker QA --no-cache（custom）→ Stress --rounds 100 --seed 12345 →
最终 Lint。每一步都必须退出码为 0，全部通过后才平铺打包 data.zip 并写回数据。
当前 ProbHub 0.7.1 原生题面解析要求二级标题且样例来自数据目录，与本项目格式不同。
工具只在临时验证副本中转换章节标题和样例标签，源题面继续遵守本规范，不修改已安装 Core。
不要对保留本项目格式的源题面直接运行这个版本的原生 lint；通过统一工具运行完整 SOP。

- Judge 最终事件必须为 all_expectations_met，双标程全 AC，错解符合期望。
- Stress 必须 passed、100/100、counterexample: null，基础设施失败或取消不能算通过。
- custom 的 Checker QA 结果必须 passed。
- 首次 Lint 可能因缺少本机 Judge/QA 证据出现提示；完成验证后重跑 Lint，
  最终必须 errors: 0、warnings: 0。不因缩短 CI 而降低验证深度。
- prepare 已在 Judge、Stress 全通过后平铺打包；随后静态检查：

    python tools/contribution.py check submissions/<slug>

- 最后可运行 python tools/contribution.py verify submissions/<slug> 复核完整链路。
  本地完整验证会执行投稿代码，仅对自己编写或已审查的题目使用。
- PR CI 在临时 GitHub 托管 runner 的无网络、非 root、有限资源容器内运行；
  ProbHub 本地资源限制本身不等于执行敌意代码的安全容器。
- 人工审核题意、证明、教学适配、独立性与数据强度不可省略。

## 7. 题解与入门教学

- 题解放在投稿根目录 solution.md，包含题意简述、解题思路与复杂度、常见易错点、参考代码与语法精讲。
- 固定章节：
  - ## 1. 题意简述
  - ## 2. 解题思路
  - ## 3. 常见易错点
  - ## 4. 参考代码与语法精讲
  - ### 4.1 C++ 参考代码、#### C++ 语法细节讲解
  - ### 4.2 Python 参考代码、#### Python 语法细节讲解
- 明确说明“所有题目均不强求在最后一行输出后换行”。
- 面向大一入门新生，解释关键语法与思维过程，不炫技、不超前引入尚未学习的数据结构。
- 顺序结构仅变量与算术，分支结构用 if/else，循环结构用循环和单变量流式处理；
  正式学习数组后才使用数组、vector、list。
- C++ 参考代码使用 #include<bits/stdc++.h>，大括号换行，不压行；
  使用直接的 cin >> ... 和 cout << ... << endl，不写 if (!(cin >> ...)) return 0。
- 禁用与教学核心无关的快读快写、ios::sync_with_stdio(false)、cin.tie(nullptr)、手写 getchar。
- Python 使用 input()、int(input())、map(int, input().split())、print()，
  不使用 sys.stdin.read().split()、sys.stdout.write() 或字节码优化。

## 8. 作者、来源与授权

- contribution.json 的 authors 至少填写一个真实署名，可附 github 用户名。
- topic 填写考点；source 写明原创或改编来源，不能隐瞒转载或第三方素材。
- permission 必须由作者主动填写：
  “允许署名发布、修改并用于本项目教学与评测”。
- 该授权只针对此次投稿，不替第三方素材授权，也不代表整个仓库统一采用某开源许可证。
- 作者与维护者共同确认题目、代码、数据和资源具备足够的使用与发布权利。

## 9. PR 审核与正式导入

- Fork 本仓库，创建分支，一份投稿一个 PR，填写 PR 模板。
- Fork 时只复制 main，克隆时使用 --single-branch --branch main，不拉取其他投稿分支。
- CI 全通过后由维护者验题，审核通过的 PR 添加 accepted 标签。
- 维护者导入时必须锁定完整 head SHA；之后若作者修改，必须重新审核。
- 正式仓库导入 PR 分配 26DAY 编号，重新验证实际入库版本，并保留来源 PR、SHA 和作者。
- 不向投稿仓库添加 OJ、QQ、正式仓库写入令牌或其他生产 Secrets。
- 正式入库完成后关闭投稿 PR，保留 accepted 标签和审稿历史，不合并投稿内容。
- 导入完成前保留源分支和审核版本。已关闭、未合并的 PR 仍可按 accepted 标签与固定 head SHA 导入。
- 录用后的正式修订在正式仓库进行；本仓库工具、规范和文档修改仍正常合并。
