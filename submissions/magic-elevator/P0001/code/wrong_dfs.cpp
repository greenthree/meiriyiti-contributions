#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n, s, t, a, b;
int best_ans = 1e9;
bool vis[100005];

void dfs(int u, int depth) {
    if (depth >= best_ans || depth > 20) {
        return;
    }
    if (u == t) {
        best_ans = min(best_ans, depth);
        return;
    }
    vis[u] = true;

    // 错误地使用 DFS 搜索最短路
    if (2LL * u <= n && !vis[2 * u]) {
        dfs(2 * u, depth + 1);
    }
    if (u + a <= n && !vis[u + a]) {
        dfs(u + a, depth + 1);
    }
    if (u - b >= 1 && !vis[u - b]) {
        dfs(u - b, depth + 1);
    }

    vis[u] = false;
}

int main() {
    if (!(cin >> n >> s >> t >> a >> b)) {
        return 0;
    }
    dfs(s, 0);
    if (best_ans > 1e8) {
        cout << -1 << "\n";
    } else {
        cout << best_ans << "\n";
    }
    return 0;
}
