# 泡沫啊请不要离去 题解

## 1. 题意简述

要摆放长度为 $n$ 的正整数序列

$$a_0<a_1<\cdots<a_{n-1},$$

满足相邻两项的最大公约数大于 $1$，并且指定 $a_{index}=value$。求 $a_{n-1}$ 的最小可能值；无解输出 `-1`。

## 2. 解题思路

### 2.1 $value=1$ 一定无解

$1$ 和任何正整数的最大公约数都是 $1$，所以只要 $value=1$，就不可能和相邻团子满足条件，直接输出 `-1`。

### 2.2 偶数：整条序列都可以用偶数

如果 $value$ 是偶数，那么所有团子都可以取偶数：

$$
2,4,6,\ldots,value,value+2,value+4,\ldots
$$

这样相邻两项的最大公约数至少是 $2$。

在 $value$ 前面，比它小的正偶数一共有 $value/2-1$ 个：

$$
2,4,\ldots,value-2.
$$

因此：

- 如果 $index>value/2-1$，前面的位置不够放，输出 `-1`；
- 如果 $index=n-1$，最后一个团子就是 $value$；
- 否则，从 $value$ 开始每次加 $2$，最后一个团子是

$$
value+2(n-1-index).
$$

### 2.3 奇数：先找最小质因子

如果 $value$ 是奇数，不能全用偶数。设 $p$ 是 $value$ 的最小质因子。

为了让 $value$ 前面能放尽量多的团子，可以用偶数一直排到 $value-p$，再放 $value$：

$$
2,4,\ldots,value-p,value.
$$

因为 $value$ 和 $value-p$ 的最大公约数是 $p$，所以最后一步合法。前面的偶数数量是

$$
\frac{value-p}{2}.
$$

如果 $value$ 本身是质数，那么 $p=value$，前面一个团子也放不了。

在 $value$ 后面，最小的合法下一个团子是 $value+p$：它是偶数，并且和 $value$ 共享因子 $p$。之后继续每次加 $2$：

$$
value+p,\ value+p+2,\ value+p+4,\ldots
$$

因此：

- 如果 $index>(value-p)/2$，输出 `-1`；
- 如果 $index=n-1$，最后一个团子就是 $value$；
- 否则，最后一个团子是

$$
value+p+2(n-2-index).
$$

### 2.4 求最小质因子

从 $3$ 开始，只枚举奇数，检查是否能整除 $value$。第一个找到的因子就是最小奇质因子，因为 $2$ 已经单独处理。

如果一直没有找到因子，说明 $value$ 是质数，令 $p=value$。

只需要枚举到 $\sqrt{value}$，时间复杂度 $O(\sqrt{value})$，空间复杂度 $O(1)$。

## 3. 常见易错点

- 忘记 $value=1$ 一定无解。
- 奇数时没有找最小质因子，随便取了一个因子，导致前面的容量算小。
- 把容量判断写成 `<` 或 `<=`，边界会多算或少算一个位置。
- 找因子时写成 `i * i < value`，漏掉 $value$ 是某个质数平方的情况，例如 $9,25,49$。
- 从 $2$ 一直枚举到 $value$ 找因子，遇到大质数会超时。
- 答案可能超过 `int` 范围，例如 $value\cdot 2+2n$，要用 `long long`。
- 所有题目均不强求在最后一行输出后换行。

## 4. 参考代码与语法精讲

### 4.1 C++ 参考代码

```cpp
#include<bits/stdc++.h>
using namespace std;

int main()
{
    long long n, index, value;
    cin >> n >> index >> value;

    if (value == 1)
    {
        cout << -1 << endl;
        return 0;
    }

    long long p = -1;
    if (value % 2 == 0)
    {
        p = 2;
    }
    else
    {
        for (long long i = 3; i * i <= value; i += 2)
        {
            if (value % i == 0)
            {
                p = i;
                break;
            }
        }
        if (p == -1)
        {
            p = value;
        }
    }

    long long capacity = (value % 2 == 0) ? value / 2 - 1 : (value - p) / 2;
    if (index > capacity)
    {
        cout << -1 << endl;
        return 0;
    }

    if (index == n - 1)
    {
        cout << value << endl;
        return 0;
    }

    long long answer;
    if (value % 2 == 0)
    {
        answer = value + 2 * (n - 1 - index);
    }
    else
    {
        answer = value + p + 2 * (n - 2 - index);
    }

    cout << answer << endl;
    return 0;
}
```

#### C++ 语法细节讲解

- `long long n, index, value;` 三个变量都用 `long long`，因为 $n$ 可以达到 $10^9$，答案还可能超过 `int`。
- `if (value == 1)` 是最重要的特判：$1$ 和任何数都互质，一定放不出合法序列。
- 偶数时直接令 `p = 2`；奇数时从 $3$ 开始枚举奇数因子。
- `i * i <= value` 保证枚举到 $\sqrt{value}$，同时能正确处理 $value=9,25$ 这种平方数。
- 如果循环结束 `p` 仍然是 `-1`，说明 $value$ 是质数，最小质因子就是它自己。
- `capacity` 是 $value$ 前面最多能放的团子数量；`index > capacity` 时直接无解。
- `index == n - 1` 时最后一个团子就是固定的 $value$，不需要再往后构造。
- 偶数时每次加 $2$；奇数时先加 $p$，再每次加 $2$。

### 4.2 Python 参考代码

```python
import math

n, index, value = map(int, input().split())

if value == 1:
    print(-1)
    exit(0)

if value % 2 == 0:
    p = 2
    capacity = value // 2 - 1
else:
    p = value
    for i in range(3, math.isqrt(value) + 1, 2):
        if value % i == 0:
            p = i
            break
    capacity = (value - p) // 2

if index > capacity:
    print(-1)
elif index == n - 1:
    print(value)
elif p == 2:
    print(value + 2 * (n - 1 - index))
else:
    print(value + p + 2 * (n - 2 - index))
```

#### Python 语法细节讲解

- `map(int, input().split())` 把一行中的三个整数分别读成 `n`、`index`、`value`。
- `value == 1` 时直接输出 `-1` 并退出。
- `value % 2 == 0` 时，最小质因子固定是 $2$，容量是 `value // 2 - 1`。
- `math.isqrt(value)` 返回 $\lfloor\sqrt{value}\rfloor$，比浮点平方根更安全。
- `range(3, math.isqrt(value) + 1, 2)` 只枚举奇数，并且包含 $\sqrt{value}$。
- 如果循环没有找到因子，`p` 仍然是 `value`，说明 $value$ 是质数。
- 最后根据 `index` 是否越界、是否在末尾，分别输出 `-1`、`value` 或公式结果。
