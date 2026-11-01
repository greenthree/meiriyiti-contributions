#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[])
{
    registerGen(argc, argv, 1);

    int n = rnd.next(2, 1000000000);
    int index = rnd.next(0, n - 1);
    int value = rnd.next(1, 1000000000);

    cout << n << " " << index << " " << value << "\n";
    return 0;
}
