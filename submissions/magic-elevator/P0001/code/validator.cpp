#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "n");
    inf.readSpace();
    int s = inf.readInt(1, n, "s");
    inf.readSpace();
    int t = inf.readInt(1, n, "t");
    inf.readSpace();
    int a = inf.readInt(1, n, "a");
    inf.readSpace();
    int b = inf.readInt(1, n, "b");
    inf.readEoln();
    inf.readEof();

    return 0;
}
