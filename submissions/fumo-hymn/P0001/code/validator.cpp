#include "testlib.h"

int main(int argc, char* argv[])
{
    registerValidation(argc, argv);

    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();
    for (int i = 0; i < T; i++)
    {
        inf.readInt(1, 1000000000, "s");
        inf.skipBlanks();
        inf.readInt(1, 1000000000, "t");
        inf.readEoln();
    }
    inf.readEof();
    return 0;
}
