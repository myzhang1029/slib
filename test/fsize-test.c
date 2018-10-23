#include "tests.h"
#include <stdio.h>
#include <slib/fileopt.h>

int main()
{
    FILE *testfile;
    const char *str = "HelloFsize";
    testfile = tmpfile();
    quiet_asrt_neq(testfile, NULL, "fopen");
    fputs(str, testfile);
    asrt_equ(fsize(testfile), 10, "fsize");
    return 0;
}
