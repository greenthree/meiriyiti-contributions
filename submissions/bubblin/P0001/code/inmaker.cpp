#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[])
{
    registerGen(argc, argv, 1);

    int n = rnd.next(1, 1000000000);
    cout << n << "\n";
    return 0;
}
