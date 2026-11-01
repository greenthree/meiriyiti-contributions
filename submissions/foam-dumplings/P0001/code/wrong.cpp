#include <bits/stdc++.h>
using namespace std;

// 思路层错解：完全不检查前面的团子数量是否足够，永远输出一个构造结果。
int main()
{
    long long n, index, value;
    cin >> n >> index >> value;

    long long p = value;
    if (value % 2 == 0)
    {
        p = 2;
    }
    else
    {
        for (long long i = 3; i * i <= value; i += 2)
        {
            if (value % i == 0)
            {
                p = i;
                break;
            }
        }
    }

    if (index == n - 1)
    {
        cout << value << endl;
        return 0;
    }

    long long answer;
    if (p == 2)
    {
        answer = value + 2 * (n - 1 - index);
    }
    else
    {
        answer = value + p + 2 * (n - 2 - index);
    }

    cout << answer << endl;
    return 0;
}
