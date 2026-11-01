#include <bits/stdc++.h>
using namespace std;

// 实现层错解：找最小质因子时写成 i*i < value，漏掉 value 是质数平方的情况。
int main()
{
    long long n, index, value;
    cin >> n >> index >> value;

    if (value == 1)
    {
        cout << -1 << endl;
        return 0;
    }

    long long p;
    if (value % 2 == 0)
    {
        p = 2;
    }
    else
    {
        p = value;
        for (long long i = 3; i * i < value; i += 2)
        {
            if (value % i == 0)
            {
                p = i;
                break;
            }
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
