#include<bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    cin >> n;
    vector<string> grid(n);
    for (int i = 0; i < n; i++)
    {
        cin >> grid[i];
    }
    int total = n * n;
    vector<int> dist(total, -1);
    vector<int> current;
    vector<int> nxt;
    dist[0] = 0;
    current.push_back(0);
    int step = 0;
    int dx[4] = {1, -1, 0, 0};
    int dy[4] = {0, 0, 1, -1};
    while (!current.empty())
    {
        nxt.clear();
        for (int id : current)
        {
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
                int nid = nx * n + ny;
                if (grid[nx][ny] == '1' || dist[nid] != -1)
                {
                    continue;
                }
                dist[nid] = step + 1;
                nxt.push_back(nid);
            }
        }
        current.swap(nxt);
        step++;
    }
    cout << dist[total - 1] << endl;
    return 0;
}
