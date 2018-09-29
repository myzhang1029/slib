#include <stdio.h>
#include <slib/fileopt.h>
#include "tests.h"

int filediff(FILE *f1, FILE *f2)
{
    int ch1 = getc(f1);
    int ch2 = getc(f2);

    while ((ch1 != EOF) && (ch2 != EOF) && (ch1 == ch2))
    {
        ch1 = getc(f1);
        ch2 = getc(f2);
    }
    return ch1 == ch2;
}

int main()
{
    const char *str = "teststr";
    FILE *tmp1 = tmpfile(), *tmp2 = tmpfile();
    quiet_asrt_neq(tmp1 && tmp2, 0, "tmpfile");
    fputs(str, tmp1);
    iofile(tmp1, tmp2);
    asrt_equ(filediff(tmp1, tmp2), 1, "iofile");
    fclose(tmp1);
    fclose(tmp2);
    return 0;
}
