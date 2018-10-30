#include "tests.h"
#include <stdio.h>
#include <string.h>
#include <slib/fileopt.h>

int bsearchfile_main()
{
    FILE *testfile;
    long found, should;
    char readbuf[5];
    testfile = tmpfile();
    quiet_asrt_neq(testfile, NULL, "fopen");
    fputs("aaa\n", testfile);
    fputs("bbb\n", testfile);
    fputs("ccc\n", testfile);
    fputs("ddd\n", testfile);
    fputs("fff\n", testfile);
    rewind(testfile);
    while (fgetc(testfile) != 'b')
        /* nothing */;
    should = ftell(testfile) - 1;
    found = slib_fbsearch("aaa", testfile, &strcmp);
    fseek(testfile, found, SEEK_SET);
    fgets(readbuf, 5, testfile);
    asrt_str_equ(readbuf, "aaa\n", "slib_fbsearch-found1");
    found = slib_fbsearch("bbb", testfile, &strcmp);
    fseek(testfile, found, SEEK_SET);
    fgets(readbuf, 5, testfile);
    asrt_str_equ(readbuf, "bbb\n", "slib_fbsearch-found2");
    asrt_equ(found, should, "slib_fbsearch-found2-num");
    found = slib_fbsearch("eee", testfile, &strcmp);
    asrt_equ(found, -1, "slib_fbsearch-notfound");
    fclose(testfile);
    return 0;
}
