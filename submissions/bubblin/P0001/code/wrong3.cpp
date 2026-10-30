#include <bits/stdc++.h>
using namespace std;

// 复杂度层错解：用十进制高精度真正算出 n!，在 n 很大时会超时。
int main()
{
    int n;
    cin >> n;

    vector<int> digits(1, 1);
    for (int i = 2; i <= n; i++)
    {
        long long carry = 0;
        for (int j = 0; j < (int)digits.size(); j++)
        {
            long long current = 1LL * digits[j] * i + carry;
            digits[j] = current % 10;
            carry = current / 10;
        }
        while (carry > 0)
        {
            digits.push_back(carry % 10);
            carry /= 10;
        }
    }

    int zeros = 0;
    for (int i = 0; i < (int)digits.size(); i++)
    {
        if (digits[i] == 0)
        {
            zeros++;
        }
        else
        {
            break;
        }
    }

    cout << zeros << endl;
    return 0;
}
