#include <bits/stdc++.h>
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
