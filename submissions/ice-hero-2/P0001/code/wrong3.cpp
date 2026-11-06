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
    vector<vector<int>> dist(n, vector<int>(n, -1));
    vector<pair<int, int>> visited;
    queue<pair<int, int>> q;
    dist[0][0] = 0;
    visited.push_back(make_pair(0, 0));
    q.push(make_pair(0, 0));
    int dx[4] = {1, -1, 0, 0};
    int dy[4] = {0, 0, 1, -1};
    while (!q.empty())
    {
        pair<int, int> cur = q.front();
        q.pop();
        int x = cur.first;
        int y = cur.second;
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
            bool seen = false;
            for (int k = 0; k < (int)visited.size(); k++)
            {
                if (visited[k].first == nx && visited[k].second == ny)
                {
                    seen = true;
                    break;
                }
            }
            if (seen)
            {
                continue;
            }
            visited.push_back(make_pair(nx, ny));
            dist[nx][ny] = dist[x][y] + 1;
            q.push(make_pair(nx, ny));
        }
    }
    cout << dist[n - 1][n - 1] << endl;
    return 0;
}
