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

// 思路层错解：忘记起点和终点相同的情况，统一按“可达”处理。
int main()
{
    int T;
    cin >> T;
    while (T--)
    {
        long long s, t;
        cin >> s >> t;

        if (isSquare(s * t))
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
