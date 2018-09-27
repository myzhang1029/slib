#include <slib/fileopt.h>
#include <stdio.h>
#include "tests.h"

int main()
{
    FILE *testfile;
    char *str = "HelloFsize";
    testfile = tmpfile();
    asrt_neq(testfile, NULL, "fopen");
    fputs(str, testfile);
    asrt_equ(fsize(testfile), 10, "fsize");
    return 0;
}
