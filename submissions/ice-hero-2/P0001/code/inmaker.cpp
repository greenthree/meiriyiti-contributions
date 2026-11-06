#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char *argv[])
{
    registerGen(argc, argv, 1);
    string mode = argc > 1 ? argv[1] : "random";
    int n;
    vector<string> grid;

    if (mode == "open")
    {
        n = argc > 2 ? atoi(argv[2]) : 10;
        grid.assign(n, string(n, '0'));
    }
    else if (mode == "snake")
    {
        n = 999;
        grid.assign(n, string(n, '0'));
        for (int i = 1; i < n; i += 2)
        {
            grid[i].assign(n, '1');
            if ((i / 2) % 2 == 0)
            {
                grid[i][n - 1] = '0';
            }
            else
            {
                grid[i][0] = '0';
            }
        }
    }
    else
    {
        n = argc > 3 ? atoi(argv[3]) : rnd.next(1, 40);
        int percent = argc > 4 ? atoi(argv[4]) : 35;
        grid.assign(n, string(n, '1'));

        int x = 0;
        int y = 0;
        grid[0][0] = '0';
        while (x < n - 1 || y < n - 1)
        {
            if (x == n - 1)
            {
                y++;
            }
            else if (y == n - 1)
            {
                x++;
            }
            else if (rnd.next(0, 1) == 0)
            {
                x++;
            }
            else
            {
                y++;
            }
            grid[x][y] = '0';
        }

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (grid[i][j] == '1' && rnd.next(0, 99) >= percent)
                {
                    grid[i][j] = '0';
                }
            }
        }
        grid[0][0] = '0';
        grid[n - 1][n - 1] = '0';
    }

    cout << n << "\n";
    for (int i = 0; i < n; i++)
    {
        cout << grid[i] << "\n";
    }
    return 0;
}
