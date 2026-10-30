#include <bits/stdc++.h>
using namespace std;

// 思路层错解：只统计 n/5，漏掉了 25、125 等额外贡献的因子 5。
int main()
{
    long long n;
    cin >> n;
    cout << n / 5 << endl;
    return 0;
}
