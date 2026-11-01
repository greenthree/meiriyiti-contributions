#include <bits/stdc++.h>
using namespace std;

// 复杂度层错解：对每个数从 2 一直试除到 sqrt(x)，询问很多时会超时。
long long squarefreeCore(long long x)
{
    long long result = 1;
    for (long long d = 2; d * d <= x; d++)
    {
        int parity = 0;
        while (x % d == 0)
        {
            x /= d;
            parity ^= 1;
        }
        if (parity)
        {
            result *= d;
        }
    }
    if (x > 1)
    {
        result *= x;
    }
    return result;
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
        else if (squarefreeCore(s) == squarefreeCore(t))
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
