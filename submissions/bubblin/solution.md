# Bubblin 题解

## 1. 题意简述

给出一个正整数 $n$，求 $n!$ 的十进制表示末尾有多少个连续的 $0$。

## 2. 解题思路

### 2.1 末尾的 0 从哪里来

十进制末尾的一个 $0$，来自一对因子 $2\times 5$。因此 $n!$ 末尾 $0$ 的个数，等于 $n!$ 的质因数分解中 $2$ 的指数与 $5$ 的指数的最小值。

在 $1,2,\ldots,n$ 中，偶数比 $5$ 的倍数多得多，所以 $2$ 的指数一定不小于 $5$ 的指数。于是只需要统计 $n!$ 中因子 $5$ 的总个数。

### 2.2 统计因子 5

$1 \sim n$ 中：

- 是 $5$ 的倍数的数，每个至少贡献一个 $5$；
- 是 $25$ 的倍数的数，还会额外贡献一个 $5$；
- 是 $125$ 的倍数的数，再额外贡献一个 $5$；
- 以此类推。

所以答案是

$$
\left\lfloor\frac{n}{5}\right\rfloor+
\left\lfloor\frac{n}{25}\right\rfloor+
\left\lfloor\frac{n}{125}\right\rfloor+\cdots
$$

只保留所有不超过 $n$ 的 $5$ 的幂。

### 2.3 算法与复杂度

可以用一个变量 `power` 依次表示 $5,25,125,\ldots$，只要 `power <= n` 就累加 `n / power`。

也可以反复令 `n = n / 5` 并累加新的 `n`，两种写法得到的结果相同。

$5$ 的幂增长很快，循环次数是 $O(\log_5 n)$，空间复杂度 $O(1)$。即使 $n=10^9$，也只需要循环十几次。

## 3. 常见易错点

- 只计算 `n / 5`，漏掉 $25,125,\ldots$ 额外贡献的因子 $5$。
- 枚举 $5$ 的幂时写成 `power < n`，漏掉 `power == n` 的情况。
- 真的用 `long long` 去计算 $n!$，$21!$ 就会溢出。
- 用高精度真正算出 $n!$，当 $n$ 很大时会超时或占用过多内存。
- 把 $0!$ 或 $1!$ 的特殊情况处理错。本题 $n \ge 1$。
- 所有题目均不强求在最后一行输出后换行。

## 4. 参考代码与语法精讲

### 4.1 C++ 参考代码

```cpp
#include<bits/stdc++.h>
using namespace std;

int main()
{
    long long n;
    cin >> n;

    long long answer = 0;
    for (long long power = 5; power <= n; power *= 5)
    {
        answer += n / power;
    }

    cout << answer << endl;
    return 0;
}
```

#### C++ 语法细节讲解

- `long long n;` 用来保存 $n$。虽然 $n \le 10^9$ 用 `int` 也够，但后面涉及乘法，用 `long long` 更稳妥。
- `long long power = 5;` 表示当前正在统计的 $5$ 的幂。
- `power <= n` 是循环条件；当 `power` 超过 $n$ 时，`n / power` 已经等于 $0$，不需要继续。
- `answer += n / power;` 统计 $1 \sim n$ 中有多少个数是 `power` 的倍数。
- `power *= 5;` 依次得到 $5,25,125,\ldots$。
- 最后输出 `answer` 即可，不需要真正计算 $n!$。

### 4.2 Python 参考代码

```python
n = int(input())

answer = 0
while n > 0:
    n //= 5
    answer += n

print(answer)
```

#### Python 语法细节讲解

- `n = int(input())` 读入一个整数。
- `while n > 0` 反复把 $n$ 除以 $5$，每除一次，`n // 5` 就相当于统计当前这一层 $5$ 的倍数个数。
- `n //= 5` 是整除赋值，等价于 `n = n // 5`，不会产生小数。
- `answer += n` 把每一层的贡献累加起来。
- 循环结束时 `answer` 就是 $n!$ 末尾 $0$ 的个数。
- `print(answer)` 会自动换行，输出格式符合要求。
