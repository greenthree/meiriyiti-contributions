#include <bits/stdc++.h>
using namespace std;

// 复杂度层错解：为了只检查质数因子，对每个 i 都重新判断一次 i 是否为质数，
// 遇到大质数 value 时会在 1 秒内跑不完。
bool isPrime(long long x)
{
    if (x < 2)
    {
        return false;
    }
    for (long long d = 2; d * d <= x; d++)
    {
        if (x % d == 0)
        {
            return false;
        }
    }
    return true;
}

int main()
{
    long long n, index, value;
    cin >> n >> index >> value;

    if (value == 1)
    {
        cout << -1 << endl;
        return 0;
    }

    long long p = value;
    for (long long i = 2; i <= value; i++)
    {
        if (!isPrime(i))
        {
            continue;
        }
        if (value % i == 0)
        {
            p = i;
            break;
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
