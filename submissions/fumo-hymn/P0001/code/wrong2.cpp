#include <bits/stdc++.h>
using namespace std;

// 思路层错解：误以为最大公约数大于 1 就能直接到达。
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
        else if (std::gcd(s, t) > 1)
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
