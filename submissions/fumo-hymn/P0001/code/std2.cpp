#include <bits/stdc++.h>
using namespace std;

vector<int> makePrimes(int limit)
{
    vector<bool> isPrime(limit + 1, true);
    isPrime[0] = false;
    isPrime[1] = false;
    for (int i = 2; i * i <= limit; i++)
    {
        if (!isPrime[i])
        {
            continue;
        }
        for (long long j = 1LL * i * i; j <= limit; j += i)
        {
            isPrime[(int)j] = false;
        }
    }

    vector<int> primes;
    for (int i = 2; i <= limit; i++)
    {
        if (isPrime[i])
        {
            primes.push_back(i);
        }
    }
    return primes;
}

// 去掉所有偶数次幂的质因子，得到平方自由部分（squarefree core）。
long long squarefreeCore(long long x, const vector<int>& primes)
{
    long long result = 1;
    for (int p : primes)
    {
        int parity = 0;
        while (x % p == 0)
        {
            x /= p;
            parity ^= 1;
        }
        if (parity)
        {
            result *= p;
        }
    }

    if (x > 1)
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
        if ((__int128)r * r != x)
        {
            result *= x;
        }
    }
    return result;
}

int main()
{
    vector<int> primes = makePrimes(1000);

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
        else if (squarefreeCore(s, primes) == squarefreeCore(t, primes))
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
