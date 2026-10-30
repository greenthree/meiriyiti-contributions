#include <bits/stdc++.h>
using namespace std;

// 思路层错解：直接用 long long 计算 n!，超过 20 后会溢出。
int main()
{
    long long n;
    cin >> n;

    unsigned long long factorial = 1;
    for (int i = 2; i <= n; i++)
    {
        factorial *= i;
    }

    int zeros = 0;
    while (factorial > 0 && factorial % 10 == 0)
    {
        zeros++;
        factorial /= 10;
    }

    cout << zeros << endl;
    return 0;
}
