#include "tests.h"
#include <slib/fileopt.h>
#include <stdio.h>
#include <string.h>

/* tmpfile */
#ifdef _MSC_VER
#pragma warning(disable: 4996)
#endif

int bsearchfile_main(void)
{
    FILE *testfile1, *testfile2;
    long found, should;
    char readbuf[5];
    testfile1 = tmpfile();
    testfile2 = tmpfile();
    quiet_asrt_neq(testfile1, NULL, "fopen");
    /* test for list prepend */
    fputs("fff\n", testfile1);
    /* test for repeated in-place */
    fputs("aaa\n", testfile1);
    fputs("bbb\n", testfile1);
    fputs("ccc\n", testfile1);
    fputs("fff\n", testfile1);
    /* test for random position */
    fputs("ddd\n", testfile1);
    /* test for repeated seq */
    fputs("fff\n", testfile1);
    fputs("fff\n", testfile1);
    fputs("fff\n", testfile1);
    slib_fqsort(testfile1, testfile2, strcmp);
    rewind(testfile2);
    while (fgetc(testfile2) != 'b')
        /* nothing */;
    should = ftell(testfile2) - 1;
    found = slib_fbsearch("aaa", testfile2, &strcmp);
    fseek(testfile2, found, SEEK_SET);
    quiet_asrt_neq(fgets(readbuf, 5, testfile2), NULL, "fgets");
    asrt_str_equ(readbuf, "aaa\n", "slib_fbsearch-found1");
    found = slib_fbsearch("bbb", testfile2, &strcmp);
    fseek(testfile2, found, SEEK_SET);
    quiet_asrt_neq(fgets(readbuf, 5, testfile2), NULL, "fgets");
    asrt_str_equ(readbuf, "bbb\n", "slib_fbsearch-found2");
    asrt_equ(found, should, "slib_fbsearch-found2-num");
    found = slib_fbsearch("eee", testfile2, &strcmp);
    asrt_equ(found, -1, "slib_fbsearch-notfound");
    fclose(testfile1);
    fclose(testfile2);
    return 0;
}
