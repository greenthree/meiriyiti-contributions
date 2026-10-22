# 冰之勇者记2 题解

## 1. 题意简述

给定一个 $n \times n$ 的网格，`0` 表示可以通行，`1` 表示障碍。勇者从左上角 $(1,1)$ 出发，公主在右下角 $(n,n)$，每次可以向上、下、左、右移动一格，不能走出网格或走进障碍。题目保证至少有一条合法路径，要求输出从起点到终点的最短步数。

## 2. 解题思路

把每个可以通行的格子看成一个点，相邻的可通行格子之间连一条边，整张图的所有边权都是 $1$。要求的是从起点到终点的最短路径长度，因此使用广度优先搜索（BFS）。

BFS 从起点开始，先访问所有距离为 $1$ 的格子，再访问所有距离为 $2$ 的格子，依此类推。由于队列中的距离是单调不减的，每个格子第一次被访问时得到的距离就是它到起点的最短距离。当搜索结束时，终点记录的距离就是答案。

具体做法：

1. 用二维数组 `dist` 记录距离，初始全部为 $-1$，表示还没有访问过。
2. 起点的距离设为 $0$，把起点放入队列。
3. 每次从队首取出一个格子，尝试向上下左右四个方向移动。
4. 如果新位置在网格内、不是障碍、且还没有被访问过，就把它的距离设为当前距离加 $1$，并加入队列。
5. 搜索结束后输出终点的距离。

因为每个格子最多入队一次，每次只检查四个方向，所以时间复杂度是 $O(n^2)$，空间复杂度也是 $O(n^2)$。

## 3. 常见易错点

- **用 DFS 代替 BFS**：深度优先搜索第一次到达终点时，得到的路径不一定是最短的，必须搜索完所有路径才能比较，容易超时或得到错误答案。
- **只允许向右、向下走**：样例 3 的路线需要向左移动，只向右、向下会误判为不可达。
- **把八个方向都当成一步**：题目只允许上下左右，斜着走会算出比真实答案更小的步数。
- **访问标记的时机不对**：应当在入队时就标记已访问；如果在出队时才标记，同一个格子可能被重复加入队列，导致队列膨胀甚至超时。
- **起点步数写成 1**：起点到自己的距离是 $0$，输出时不要额外加一。
- **忘记处理 $n=1$**：此时起点就是终点，答案是 $0$。
- 输出末尾有没有换行都算正确，所有题目均不强求在最后一行输出后换行。

## 4. 参考代码与语法精讲

### 4.1 C++ 参考代码

```cpp
#include<bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    cin >> n;
    vector<string> grid(n);
    for (int i = 0; i < n; i++)
    {
        cin >> grid[i];
    }
    vector<vector<int>> dist(n, vector<int>(n, -1));
    queue<pair<int, int>> q;
    dist[0][0] = 0;
    q.push(make_pair(0, 0));
    int dx[4] = {1, -1, 0, 0};
    int dy[4] = {0, 0, 1, -1};
    while (!q.empty())
    {
        pair<int, int> cur = q.front();
        q.pop();
        int x = cur.first;
        int y = cur.second;
        for (int d = 0; d < 4; d++)
        {
            int nx = x + dx[d];
            int ny = y + dy[d];
            if (nx < 0 || nx >= n || ny < 0 || ny >= n)
            {
                continue;
            }
            if (grid[nx][ny] == '1' || dist[nx][ny] != -1)
            {
                continue;
            }
            dist[nx][ny] = dist[x][y] + 1;
            q.push(make_pair(nx, ny));
        }
    }
    cout << dist[n - 1][n - 1] << endl;
    return 0;
}
```

#### C++ 语法细节讲解

- `vector<string> grid(n)` 创建一个长度为 $n$ 的字符串数组，每个字符串保存网格的一行。用 `cin >> grid[i]` 读入时，字符串会自动跳过空白，正好读入一整行。
- `vector<vector<int>> dist(n, vector<int>(n, -1))` 创建 $n \times n$ 的二维数组，并把所有元素初始化为 $-1$。`-1` 同时表示“未访问”。
- `queue<pair<int, int>>` 是队列，存放格子的行列坐标。`pair<int, int>` 把两个整数打包成一个整体，`cur.first` 是行，`cur.second` 是列。
- `dx` 和 `dy` 两个数组配合循环，依次表示下、上、右、左四个方向，避免写四段重复代码。
- 边界检查 `nx < 0 || nx >= n || ny < 0 || ny >= n` 必须放在使用 `grid[nx][ny]` 之前，否则会越界。
- BFS 中“第一次访问就是最短距离”依赖于队列先进先出的顺序，因此不能把 `queue` 换成栈。

### 4.2 Python 参考代码

```python
from collections import deque

n = int(input())
grid = [input().strip() for _ in range(n)]

dist = [[-1] * n for _ in range(n)]
dist[0][0] = 0
q = deque([(0, 0)])
directions = [(1, 0), (-1, 0), (0, 1), (0, -1)]

while q:
    x, y = q.popleft()
    for dx, dy in directions:
        nx = x + dx
        ny = y + dy
        if 0 <= nx < n and 0 <= ny < n and grid[nx][ny] == '0' and dist[nx][ny] == -1:
            dist[nx][ny] = dist[x][y] + 1
            q.append((nx, ny))

print(dist[n - 1][n - 1])
```

#### Python 语法细节讲解

- `input().strip()` 读入一行并去掉首尾空白（包括换行符）。网格行本身只含 `0` 和 `1`，去掉空白后就是这一行的内容。
- `[[-1] * n for _ in range(n)]` 用列表推导式创建二维列表。不能写成 `[[-1] * n] * n`，那样每一行会指向同一个列表，修改一行会影响所有行。
- `deque` 是双端队列，`popleft()` 从队首取出元素，`append()` 从队尾加入元素，正好符合 BFS 的需要。
- `x, y = q.popleft()` 把队列中保存的元组拆成两个变量，写起来更直观。
- `0 <= nx < n` 是 Python 特有的连续比较，等价于 `0 <= nx and nx < n`。
- 条件用 `and` 连接，从左到右判断；只有前面的边界检查通过后，才会访问 `grid[nx][ny]`，不会越界。
