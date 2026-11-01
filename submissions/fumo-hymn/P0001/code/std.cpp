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
            cout << 0 << '\n';
        }
        else if (isSquare(s * t))
        {
            cout << 1 << '\n';
        }
        else
        {
            cout << -1 << '\n';
        }
    }
    return 0;
}
