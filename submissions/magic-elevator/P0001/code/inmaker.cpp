#include "testlib.h"
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    string mode = argv[1];

    if (mode == "random") {
        int max_n = opt<int>(2);
        int n = rnd.next(2, max_n);
        int s = rnd.next(1, n);
        int t = rnd.next(1, n);
        int a = rnd.next(1, n);
        int b = rnd.next(1, n);
        cout << n << " " << s << " " << t << " " << a << " " << b << "\n";
    } else if (mode == "unreachable") {
        int n = opt<int>(2);
        // 构造偶数状态空间：s 为偶数，a 为偶数，b 为偶数，t 为奇数
        // 任意偶数 + 偶数 = 偶数，偶数 - 偶数 = 偶数，偶数 * 2 = 偶数，永远无法到达奇数 t
        int s = rnd.next(1, n / 2) * 2;
        int t = rnd.next(0, (n - 1) / 2) * 2 + 1;
        int a = rnd.next(1, max(1, n / 2)) * 2;
        if (a > n) a = 2;
        int b = rnd.next(1, max(1, n / 2)) * 2;
        if (b > n) b = 2;
        cout << n << " " << s << " " << t << " " << a << " " << b << "\n";
    } else if (mode == "same") {
        int max_n = opt<int>(2);
        int n = rnd.next(2, max_n);
        int s = rnd.next(1, n);
        int t = s;
        int a = rnd.next(1, n);
        int b = rnd.next(1, n);
        cout << n << " " << s << " " << t << " " << a << " " << b << "\n";
    } else if (mode == "extreme") {
        int type = opt<int>(2);
        if (type == 1) {
            cout << 100000 << " " << 1 << " " << 100000 << " " << 1 << " " << 1 << "\n";
        } else if (type == 2) {
            cout << 100000 << " " << 100000 << " " << 1 << " " << 1 << " " << 1 << "\n";
        } else {
            cout << 100000 << " " << 1 << " " << 100000 << " " << 3 << " " << 2 << "\n";
        }
    } else if (mode == "kill_greedy") {
        // 贪心优先靠近目标，却错过先下降再翻倍的最优路径
        // 起点 6，终点 14，a = 3, b = 5, n = 20
        // 贪心：6 + 3 = 9 -> 12 -> 无法到达 14
        // 最优：6 - 5 = 1 -> 4 -> 7 -> 14 (共 4 步)
        cout << 20 << " " << 6 << " " << 14 << " " << 3 << " " << 5 << "\n";
    } else if (mode == "kill_dfs") {
        // 构造大规模复杂转移图，最短路较深，DFS 必定 TLE 或被深度截断 WA
        int n = 100000;
        int s = 1;
        int t = 99999;
        int a = 7;
        int b = 3;
        cout << n << " " << s << " " << t << " " << a << " " << b << "\n";
    } else {
        // 兜底随机
        int n = 100;
        cout << n << " " << rnd.next(1, n) << " " << rnd.next(1, n) << " "
             << rnd.next(1, n) << " " << rnd.next(1, n) << "\n";
    }

    return 0;
}
