#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main() {
    int n, s, t, a, b;
    if (!(cin >> n >> s >> t >> a >> b)) {
        return 0;
    }

    if (s == t) {
        cout << 0 << "\n";
        return 0;
    }

    vector<int> dist(n + 1, -1);
    queue<int> q;

    dist[s] = 0;
    q.push(s);

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        if (u == t) {
            cout << dist[t] << "\n";
            return 0;
        }

        // 按钮 1：上 a 层
        if (u + a <= n && dist[u + a] == -1) {
            dist[u + a] = dist[u] + 1;
            q.push(u + a);
        }

        // 按钮 2：下 b 层
        if (u - b >= 1 && dist[u - b] == -1) {
            dist[u - b] = dist[u] + 1;
            q.push(u - b);
        }

        // 按钮 3：翻倍
        if (2LL * u <= n && dist[2 * u] == -1) {
            dist[2 * u] = dist[u] + 1;
            q.push(2 * u);
        }
    }

    cout << -1 << "\n";
    return 0;
}
