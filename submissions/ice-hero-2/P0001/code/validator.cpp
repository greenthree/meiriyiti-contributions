#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char *argv[])
{
    registerValidation(argc, argv);
    int n = inf.readInt(1, 1000, "n");
    inf.readEoln();
    vector<string> grid(n);
    for (int i = 0; i < n; i++)
    {
        grid[i] = inf.readLine("[01]{1,1000}", "row");
        ensuref((int)grid[i].size() == n, "row %d length must be n", i + 1);
    }
    ensuref(grid[0][0] == '0', "start cell must be 0");
    ensuref(grid[n - 1][n - 1] == '0', "princess cell must be 0");

    vector<char> seen(n * n, 0);
    queue<int> q;
    seen[0] = 1;
    q.push(0);
    int dx[4] = {1, -1, 0, 0};
    int dy[4] = {0, 0, 1, -1};
    while (!q.empty())
    {
        int id = q.front();
        q.pop();
        int x = id / n;
        int y = id % n;
        for (int d = 0; d < 4; d++)
        {
            int nx = x + dx[d];
            int ny = y + dy[d];
            if (nx < 0 || nx >= n || ny < 0 || ny >= n)
            {
                continue;
            }
            if (grid[nx][ny] == '1')
            {
                continue;
            }
            int nid = nx * n + ny;
            if (seen[nid])
            {
                continue;
            }
            seen[nid] = 1;
            q.push(nid);
        }
    }
    ensuref(seen[n * n - 1], "there must be at least one path from start to princess");
    inf.readEof();
    return 0;
}
