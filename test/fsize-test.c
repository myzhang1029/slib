#include <stdio.h>
#include <slib/fileopt.h>
#include "tests.h"

int fsize_main(void)
{
    FILE *testfile;
    const char *str = "HelloFsize";
    testfile = tmpfile();
    check_neq(testfile, NULL);
    fputs(str, testfile);
    asrt_equ(fsize(testfile), 10, "fsize");
    return 0;
}
