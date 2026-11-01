# 热情高唱~芙兰朵露和她的小fumo 题解

## 1. 题意简述

有无限多个结界编号 $1,2,3,\ldots$。编号 $i$ 和 $j$ 之间可以直接通行，当且仅当 $i\times j$ 是完全平方数。给出 $T$ 组起点 $s$ 和终点 $t$，求最少经过多少个结界可以到达终点（起点不计入）；相同输出 $0$，无法到达输出 `-1`。

## 2. 解题思路

### 2.1 什么情况下两个结界可以直接到达

如果 $s\times t$ 是完全平方数，那么根据题意，$s$ 和 $t$ 之间有一条边，经过 $1$ 个结界就能到达。

如果 $s=t$，已经在终点，答案是 $0$。

### 2.2 不能直接到达时，能不能绕路

假设存在一条路径

$$
s=x_0,x_1,\ldots,x_k=t.
$$

每一步都有 $x_i\times x_{i+1}$ 是完全平方数。

把所有编号写成

$$
x=(x\text{ 的平方自由部分})\times(\text{某个完全平方数}).
$$

两个数乘积是完全平方数，当且仅当它们的平方自由部分相同。因此，沿着路径走，平方自由部分始终不变。于是 $s$ 和 $t$ 的平方自由部分必须相同，也就等价于 $s\times t$ 是完全平方数。

所以：

- $s=t$：答案 $0$；
- 否则，如果 $s\times t$ 是完全平方数：答案 $1$；
- 否则：永远无法到达，答案 `-1`。

### 2.3 判断乘积是否为完全平方数

$s,t\le 10^9$，所以 $s\times t\le 10^{18}$，可以用 `long long` 保存。

用整数平方根判断：先取 `sqrt(x)` 的整数近似，再把结果上下调整，直到满足

$$
r^2\le x<(r+1)^2.
$$

如果此时 $r^2=x$，就是完全平方数。

### 2.4 复杂度

每组询问只需要一次平方根判断，时间复杂度 $O(T)$，空间复杂度 $O(1)$。

## 3. 常见易错点

- 忘记 $s=t$ 时应输出 $0$，误输出 $1$。
- 认为最大公约数大于 $1$ 就能到达。例如 $4$ 和 $25$ 互质，但 $4\times 25=100$ 是完全平方数，可以直接到达。
- 用 `int` 保存 $s\times t$，乘积超过 $2^{31}-1$ 时会溢出。
- 直接用浮点数平方根比较，遇到接近完全平方数的大数可能因为精度误差判断错误。
- 每个询问都用试除法分解质因数，询问很多时会超时。
- 所有题目均不强求在最后一行输出后换行。

## 4. 参考代码与语法精讲

### 4.1 C++ 参考代码

```cpp
#include<bits/stdc++.h>
using namespace std;

bool isSquare(long long x)
{
    long long r = sqrt((long double)x);
    while ((__int128)r * r < x)
    {
        r++;
    }
    while ((__int128)r * r > x)
    {
        r--;
    }
    return (__int128)r * r == x;
}

int main()
{
    int T;
    cin >> T;
    while (T--)
    {
        long long s, t;
        cin >> s >> t;

        if (s == t)
        {
            cout << 0 << endl;
        }
        else if (isSquare(s * t))
        {
            cout << 1 << endl;
        }
        else
        {
            cout << -1 << endl;
        }
    }
    return 0;
}
```

#### C++ 语法细节讲解

- `long long` 保存 $s,t$ 和乘积。$10^9\times 10^9=10^{18}$，在 `long long` 范围内。
- `sqrt((long double)x)` 先得到一个接近整数平方根的值，但浮点运算可能有误差。
- `(__int128)r * r` 先把 `r` 转成 128 位整数再平方，避免 $r^2$ 在 64 位中溢出，也能精确比较。
- 两个 `while` 循环把 `r` 调整到正确的整数平方根附近。
- `if (s == t)` 必须放在最前面，因为此时答案应该是 $0$，不是 $1$。
- 否则只需要判断 `s * t` 是否为完全平方数。

### 4.2 Python 参考代码

```python
import math

T = int(input())
for _ in range(T):
    s, t = map(int, input().split())

    if s == t:
        print(0)
        continue

    product = s * t
    root = math.isqrt(product)
    if root * root == product:
        print(1)
    else:
        print(-1)
```

#### Python 语法细节讲解

- `map(int, input().split())` 把一行中的两个整数读成 `s` 和 `t`。
- `s == t` 时直接输出 $0$，并跳过本轮循环剩下的代码。
- Python 的整数没有固定位数，`s * t` 不会像 C++ 的 `int` 那样溢出。
- `math.isqrt(product)` 返回精确的整数平方根，不会产生浮点误差。
- `root * root == product` 成立就说明乘积是完全平方数，输出 $1$；否则输出 `-1`。
