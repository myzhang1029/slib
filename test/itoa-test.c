#include <slib/itoa.h>
#include "tests.h"
int main(void)
{
    int i = 12;
    long l = 12;
    unsigned long ul = 12;
    char *result = malloc(4);
    itoaS(i, result, 10);
    asrt_equ(strcmp(result, "12"), 0, "itoaS");
    ltoaS(l, result, 10);
    asrt_equ(strcmp(result, "12"), 0, "ltoaS");
    ltoaS(-l, result, 10);
    asrt_equ(strcmp(result, "-12"), 0, "ltoaS");
    ultoaS(ul, result, 16);
    asrt_equ(strcmp(result, "c"), 0, "ultoaS");
    ultoaS(ul, result, 12);
    asrt_equ(strcmp(result, "10"), 0, "ultoaS");
    free(result);
    return 0;
}
