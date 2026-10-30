#include <iostream>
#include <vector>
#include <queue>
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

    vector<int> dist_f(n + 1, -1);
    vector<int> dist_b(n + 1, -1);
    queue<int> q_f, q_b;

    dist_f[s] = 0;
    q_f.push(s);

    dist_b[t] = 0;
    q_b.push(t);

    int best = -1;

    while (!q_f.empty() && !q_b.empty()) {
        if (q_f.size() <= q_b.size()) {
            int sz = q_f.size();
            for (int k = 0; k < sz; ++k) {
                int u = q_f.front();
                q_f.pop();

                int nxt[3] = {u + a, u - b, (2LL * u <= n ? 2 * u : -1)};
                for (int i = 0; i < 3; ++i) {
                    int v = nxt[i];
                    if (v >= 1 && v <= n) {
                        if (dist_b[v] != -1) {
                            int total = dist_f[u] + 1 + dist_b[v];
                            if (best == -1 || total < best) {
                                best = total;
                            }
                        }
                        if (dist_f[v] == -1) {
                            dist_f[v] = dist_f[u] + 1;
                            q_f.push(v);
                        }
                    }
                }
            }
        } else {
            int sz = q_b.size();
            for (int k = 0; k < sz; ++k) {
                int v = q_b.front();
                q_b.pop();

                int pre[3] = {v - a, v + b, (v % 2 == 0 ? v / 2 : -1)};
                for (int i = 0; i < 3; ++i) {
                    int u = pre[i];
                    if (u >= 1 && u <= n) {
                        if (dist_f[u] != -1) {
                            int total = dist_f[u] + 1 + dist_b[v];
                            if (best == -1 || total < best) {
                                best = total;
                            }
                        }
                        if (dist_b[u] == -1) {
                            dist_b[u] = dist_b[v] + 1;
                            q_b.push(u);
                        }
                    }
                }
            }
        }
        if (best != -1) {
            cout << best << "\n";
            return 0;
        }
    }

    cout << -1 << "\n";
    return 0;
}
