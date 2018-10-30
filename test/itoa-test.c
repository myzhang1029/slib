#include "tests.h"
#include <slib/itoa.h>

int itoa_main(void)
{
    int i = 12;
    long l = 12;
    unsigned long ul = 12;
    char *result = (char *)malloc(4);
    itoaS(i, result, 10);
    asrt_str_equ(result, "12", "itoaS");
    ltoaS(l, result, 10);
    asrt_str_equ(result, "12", "ltoaS");
    ltoaS(-l, result, 10);
    asrt_str_equ(result, "-12", "ltoaS");
    ultoaS(ul, result, 16);
    asrt_str_equ(result, "c", "ultoaS");
    ultoaS(ul, result, 12);
    asrt_str_equ(result, "10", "ultoaS");
    free(result);
    return 0;
}
