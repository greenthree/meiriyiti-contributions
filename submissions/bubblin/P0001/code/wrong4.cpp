#include <bits/stdc++.h>
using namespace std;

// 实现层错解：枚举 5 的幂时写成 power < n，漏掉了 power == n 的情况。
int main()
{
    long long n;
    cin >> n;

    long long answer = 0;
    for (long long power = 5; power < n; power *= 5)
    {
        answer += n / power;
    }

    cout << answer << endl;
    return 0;
}
