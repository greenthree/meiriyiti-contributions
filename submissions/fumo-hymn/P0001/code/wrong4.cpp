#include <bits/stdc++.h>
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

// 实现层错解：用 int 保存 s*t，乘积超过 2^31-1 时会溢出。
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
            continue;
        }

        int product = (int)(s * t);
        if (isSquare(product))
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
