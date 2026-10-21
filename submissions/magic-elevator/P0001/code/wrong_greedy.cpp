#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

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

    vector<bool> vis(n + 1, false);
    int cur = s;
    int steps = 0;
    vis[cur] = true;

    while (cur != t && steps <= 1000) {
        int best_next = -1;
        int min_diff = 1e9;

        // 贪心策略：盲目选择离目标最近的下一个状态
        int candidates[3] = {cur + a, cur - b, (2LL * cur <= n ? 2 * cur : -1)};
        for (int nxt : candidates) {
            if (nxt >= 1 && nxt <= n && !vis[nxt]) {
                int diff = abs(nxt - t);
                if (diff < min_diff) {
                    min_diff = diff;
                    best_next = nxt;
                }
            }
        }

        if (best_next == -1) {
            cout << -1 << "\n";
            return 0;
        }

        cur = best_next;
        vis[cur] = true;
        steps++;
    }

    if (cur == t) {
        cout << steps << "\n";
    } else {
        cout << -1 << "\n";
    }
    return 0;
}
