#include <bits/stdc++.h>
using namespace std;

// 与 std.cpp 的“枚举 5 的幂并累加”不同，这里递归地把 n 除以 5 并累加。
long long countZeros(long long n)
{
    if (n < 5)
    {
        return 0;
    }
    return n / 5 + countZeros(n / 5);
}

int main()
{
    long long n;
    cin >> n;
    cout << countZeros(n) << endl;
    return 0;
}
