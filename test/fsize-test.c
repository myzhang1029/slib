#include "tests.h"
#include <slib/fileopt.h>
#include <stdio.h>

int fsize_main(void)
{
    FILE *testfile;
    const char *str = "HelloFsize";
    testfile = tmpfile();
    quiet_asrt_neq(testfile, NULL, "fopen");
    fputs(str, testfile);
    asrt_equ(fsize(testfile), 10, "fsize");
    return 0;
}
