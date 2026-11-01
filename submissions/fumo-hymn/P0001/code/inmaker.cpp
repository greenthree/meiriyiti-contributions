#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[])
{
    registerGen(argc, argv, 1);

    string mode = argc > 1 ? argv[1] : "random";
    vector<pair<int, int>> queries;

    if (mode == "large")
    {
        int T = 100000;
        for (int i = 0; i < T; i++)
        {
            if (i == 0)
            {
                queries.push_back({2, 8});
            }
            else if (i == 1)
            {
                queries.push_back({4, 25});
            }
            else if (i == 2)
            {
                queries.push_back({2, 3});
            }
            else if (i == 3)
            {
                queries.push_back({5, 5});
            }
            else
            {
                queries.push_back({rnd.next(1, 1000000000), rnd.next(1, 1000000000)});
            }
        }
    }
    else if (mode == "prime")
    {
        int T = 100000;
        for (int i = 0; i < T; i++)
        {
            if (i % 2 == 0)
            {
                queries.push_back({999999937, 999999929});
            }
            else
            {
                queries.push_back({999999929, 999999937});
            }
        }
    }
    else
    {
        int T = rnd.next(1, 20);
        for (int i = 0; i < T; i++)
        {
            queries.push_back({rnd.next(1, 10000), rnd.next(1, 10000)});
        }
    }

    cout << queries.size() << "\n";
    for (int i = 0; i < (int)queries.size(); i++)
    {
        cout << queries[i].first << " " << queries[i].second << "\n";
    }
    return 0;
}
