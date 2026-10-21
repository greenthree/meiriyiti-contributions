
# 每日一题 · 投稿指南

本项目题目统一面向大一新生。你可以选择**通过 AI Agent 全程代办（出题成本约 3M token）**，或**在终端中自行使用命令行完成投稿**。

投稿统一通过 **Fork → 在自己的仓库提交 → 向本仓库发起 PR** 完成。

题目录用后会导入正式题库，并关闭投稿 PR；题目不会合并进本仓库主分支，审稿记录保留在 PR 中。

> **⚠️ 公开说明**：本仓库为完全公开仓库。提交的题面、代码、测试数据和题解在发起 PR 时即对外可见，正式发布时间由维护者另行安排。
>
> 📚 **参考文档**：[出题规范 (AGENTS.md)](AGENTS.md) · [环境配置说明 (docs/ENVIRONMENT.md)](docs/ENVIRONMENT.md)

---

## 方式一：使用 AI Agent 辅助投稿（推荐）

将下方三段提示词依次发送给你的 AI 编程助手（如 Codex、Claude Code、DSH 等），即可引导 AI 完成从环境配置到提交 PR 的全流程。

### 第一步：让 AI 配好环境

~~~text
帮我准备这个投稿项目的本地环境：
https://github.com/greenthree/meiriyiti-contributions

将此仓库 Fork 到我的 GitHub 账号，再从我的 Fork 准备本地项目。
Fork 只复制 main，克隆时只获取 main 分支，避免下载其他投稿。
已有 Fork 或本地项目请复用，保留已有修改，并确认推送目标是我自己的 Fork。
先阅读项目的 AGENTS.md 和 docs/ENVIRONMENT.md，安装所需工具和固定版本依赖，并实际检查能否运行。
需要我操作时，请用简单的步骤说明。完成后告诉我项目文件夹位置，以及是否可以开始出题。
~~~

### 第二步：让 AI 生成并验证题目

填写 `【】` 中的内容，在同一会话中继续发送：

~~~text
先阅读并遵守本项目的 AGENTS.md，完成一道每日一题投稿。

题意描述：【填写你的想法】
作者署名与来源：【填写署名，并说明原创或改编来源】

投稿文件夹名请自动生成。实际完成题面、代码、数据和题解，执行规定的验证流程，最后汇报结果。
~~~

### 第三步：让 AI 提交投稿

确认题目内容无误后，继续发送：

~~~text
按 AGENTS.md 帮我投稿到：
https://github.com/greenthree/meiriyiti-contributions

核对署名、来源和发布修改授权；需要我登录或确认授权时，请用简单的步骤说明。
使用我的 GitHub 账号，在我的 Fork 中创建投稿分支并推送，再向上述仓库的 main 分支发起 Pull Request。
只提交本次题目，保留其他本地修改。已有同题投稿时更新原投稿，不要重复创建。
完成后给我投稿链接，并告诉我自动检查是否通过；未通过时修复后更新同一份投稿。
~~~

---

## 方式二：命令行手动投稿

如果你习惯自己在终端操作，请按以下步骤使用项目的脚手架工具完成投稿（下文中的 `my-problem` 请替换为你自己的英文投稿目录名）。

### 1. 获取项目与配置环境

1. 参照 [环境配置说明](docs/ENVIRONMENT.md) 准备好本地基础工具。
2. 在本仓库右上角点击 **Fork**，保留 **Copy the main branch only**，将仓库复制到你的 GitHub 账号下。
3. 将下方的 `YOUR_NAME` 替换为你的 GitHub 用户名，克隆仓库并创建分支：

```bash
git clone --single-branch --branch main https://github.com/YOUR_NAME/meiriyiti-contributions.git
cd meiriyiti-contributions
git switch -c submit/my-problem

```

4. 进入项目后，按 [环境配置说明](docs/ENVIRONMENT.md) 安装固定版本的 ProbHub 和 Python 依赖（若本地已有项目，直接复用并保留现有修改即可）。

### 2. 初始化题目骨架

在项目根目录运行以下命令（请替换题名、署名和考点）：

```bash
python tools/contribution.py new my-problem --title "题目名称" --author "作者署名" --topic "考点"

```

* **外层投稿目录**：`submissions/my-problem/`
* **题目工作区**：`submissions/my-problem/P0001/`（内部固定使用 `P0001` 编号，互不冲突）
* **题解文件**：`submissions/my-problem/solution.md`

### 3. 编写内容与授权信息

* 按照 [出题规范 (AGENTS.md)](AGENTS.md) 替换默认骨架，编写完整的题面、标程/错解代码、数据生成配置及题解。
* 编辑 `submissions/my-problem/contribution.json`，如实填写作者、来源，并确认填入发布与修改授权。

### 4. 本地构建与验证

在项目根目录依次运行：

```bash
python tools/contribution.py prepare submissions/my-problem
python tools/contribution.py check submissions/my-problem

```

> 💡 `prepare` 命令会自动生成测试数据并打包 `data.zip`。请务必确保两条命令**全部零错误通过**后再进入下一步（详见 [AGENTS.md](AGENTS.md)）。

### 5. 提交代码并发起 PR

仅将当前题目的目录加入 Git 提交，并推送到自己 Fork 中的分支：

```bash
git add submissions/my-problem/
git commit -m "投稿：题目名称"
git push -u origin submit/my-problem

```

然后任选以下一种方式向主仓库发起 Pull Request（即完成投稿）：

* **方式 A：使用 GitHub 网页端**
打开你 Fork 后的 GitHub 仓库页面，点击 **Compare & pull request**，确保目标仓库为 `greenthree/meiriyiti-contributions` 的 `main` 分支，按模板填写后提交。
* **方式 B：使用 GitHub CLI 命令行**（将 `YOUR_NAME` 替换为你的用户名，已登录可跳过第一行）：
```bash
gh auth login
gh pr create --repo greenthree/meiriyiti-contributions --base main --head YOUR_NAME:submit/my-problem

```



---

## 审稿与后续修改

提交 PR 后，系统会自动运行 CI 检查，随后由维护者进行人工审稿：

* 如需根据 CI 报错或审稿意见修改题目，只需在本地原分支继续修改并 `git push`（或让 AI 继续修改并推送），原 PR 会自动同步更新，**无需重新创建 PR**。
* 录用后会标记 `accepted`，按审核版本导入正式题库，再关闭本 PR，**不会合并到本仓库主分支**。此时关闭表示处理完成，并非拒稿；导入完成前请保留投稿分支。
