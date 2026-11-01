#include <bits/stdc++.h>
using namespace std;

vector<int> makePrimes(int limit)
{
    vector<bool> isPrime(limit + 1, true);
    isPrime[0] = false;
    isPrime[1] = false;
    for (int i = 2; 1LL * i * i <= limit; i++)
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

int main()
{
    vector<int> primes = makePrimes(31623);

    long long n, index, value;
    cin >> n >> index >> value;

    if (value == 1)
    {
        cout << -1 << endl;
        return 0;
    }

    long long p;
    if (value % 2 == 0)
    {
        p = 2;
    }
    else
    {
        p = value;
        for (int q : primes)
        {
            if (1LL * q * q > value)
            {
                break;
            }
            if (value % q == 0)
            {
                p = q;
                break;
            }
        }
    }

    long long capacity = (value % 2 == 0) ? value / 2 - 1 : (value - p) / 2;
    if (index > capacity)
    {
        cout << -1 << endl;
        return 0;
    }

    if (index == n - 1)
    {
        cout << value << endl;
        return 0;
    }

    long long answer;
    if (value % 2 == 0)
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
