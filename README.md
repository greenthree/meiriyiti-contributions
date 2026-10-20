# 每日一题 · 投稿与审稿指南

本项目的题目统一面向新生。可以把下方三段提示词依次交给 AI，也可以按后面的手动方法完成投稿。

**公开说明：** 提交的题面、代码、数据和题解都会公开，正式发布时间由维护者安排。

## 1. 让 AI 配好环境

~~~text
请帮我准备这个投稿项目的本地环境：
https://github.com/greenthree/meiriyiti-contributions

如果本地已有这个项目，请直接使用并保留已有修改；否则帮我下载。
先阅读项目的 AGENTS.md 和 docs/ENVIRONMENT.md，安装所需工具和固定版本依赖，并实际检查能否运行。
需要我操作时，请用简单的步骤说明。完成后告诉我项目文件夹位置，以及是否可以开始出题。
~~~

## 2. 让 AI 完成题目

填写【】中的内容，在刚才的项目中继续发送：

~~~text
请先阅读并遵守本项目的 AGENTS.md，完成一道每日一题投稿。

题意描述：【填写你的想法】
作者署名与来源：【填写署名，并说明原创或改编来源】

投稿文件夹名请自动生成。实际完成题面、代码、数据和题解，执行规定的验证流程，最后汇报结果。
~~~

## 3. 让 AI 提交投稿

确认题目内容后，继续发送：

~~~text
请按 AGENTS.md 检查本次题目，完成规定的验证，并帮我投稿到：
https://github.com/greenthree/meiriyiti-contributions

核对署名、来源和发布修改授权；需要我登录或确认授权时，请用简单的步骤说明。
使用我的 GitHub 账号创建投稿分支并发起 Pull Request；没有仓库写入权限时，通过我的 Fork 提交。
只提交本次题目，保留其他本地修改。已有同题投稿时更新原投稿，不要重复创建。
完成后给我投稿链接，并告诉我自动检查是否通过；未通过时修复后更新同一份投稿。
~~~

## 4. 手动投稿

这里的“手动”指由投稿者自己执行各步骤，仍然使用 ProbHub、投稿脚本和 Git 等工具。以下命令在本地终端执行，my-problem 可换成自己的英文投稿文件夹名。

1. **获取项目并配置环境。** 先准备 [环境说明](docs/ENVIRONMENT.md) 中列出的基础工具，再在仓库首页点击 Fork，将仓库复制到自己的账号。把下面的 YOUR_NAME 换成你的 GitHub 用户名，再运行：

   ~~~bash
   git clone https://github.com/YOUR_NAME/meiriyiti-contributions.git
   cd meiriyiti-contributions
   git switch -c submit/my-problem
   ~~~

   进入项目后，按 [环境配置说明](docs/ENVIRONMENT.md) 安装 ProbHub 和 Python 依赖。已有本地项目时直接使用，不要覆盖已有修改。

2. **创建题目。** 在项目根目录运行，替换题名、署名和考点：

   ~~~bash
   python tools/contribution.py new my-problem --title "题目名称" --author "作者署名" --topic "考点"
   ~~~

   题目位于 submissions/my-problem/P0001/，题解位于 submissions/my-problem/solution.md。
   my-problem 是整份投稿的外层目录名，P0001 是里面固定的题目编号。

3. **完成内容。** 按 [AGENTS.md](AGENTS.md) 替换示例骨架，完成题面、代码、数据配置和题解；
   在 contribution.json 填写作者、来源和本人确认的发布修改授权。

4. **验证题目。** 在项目根目录运行：

   ~~~bash
   python tools/contribution.py prepare submissions/my-problem
   python tools/contribution.py check submissions/my-problem
   ~~~

   全部通过后再投稿，data.zip 由工具自动生成。详细验证要求见 AGENTS.md。

5. **提交投稿。** 只提交这一份题目：

   ~~~bash
   git add submissions/my-problem/
   git commit -m "投稿：题目名称"
   git push -u origin submit/my-problem
   ~~~

   可以使用 GitHub CLI 创建投稿，将 YOUR_NAME 换成自己的 GitHub 用户名；已登录时可跳过登录命令：

   ~~~bash
   gh auth login
   gh pr create --repo greenthree/meiriyiti-contributions --base main --head YOUR_NAME:submit/my-problem
   ~~~

   按提示填写标题和 PR 模板，完成提交。也可以在自己的 GitHub 仓库点击 Compare & pull request，
   将目标选择为 greenthree/meiriyiti-contributions 的 main 分支。这个 Pull Request 就是你的投稿。
   如需修改，继续在同一分支提交并推送，原投稿会自动更新。

提交后，等待自动检查和维护者审核；按审稿意见自行修改或继续让 AI 协助即可。

详细说明：[出题规范](AGENTS.md) · [环境配置说明](docs/ENVIRONMENT.md)
