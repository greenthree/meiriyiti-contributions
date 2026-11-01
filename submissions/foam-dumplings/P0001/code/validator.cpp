#include "testlib.h"

int main(int argc, char* argv[])
{
    registerValidation(argc, argv);

    int n = inf.readInt(2, 1000000000, "n");
    inf.skipBlanks();
    int index = inf.readInt(0, n - 1, "index");
    inf.skipBlanks();
    int value = inf.readInt(1, 1000000000, "value");
    inf.readEoln();
    inf.readEof();
    return 0;
}
