#include <slib/itoa.h>
#include "tests.h"
int main(void)
{
    int i = 12;
    long l = 12;
    unsigned long ul = 12;
    char *result = malloc(4);
    itoaS(i, result, 10);
    asrt_equ(result, "12", "itoaS");
    ltoaS(l, result, 10);
    asrt_equ(result, "12", "ltoaS");
    ultoaS(ul, result, 16);
    asrt_equ(result, "c", "ultoaS");
    ultoaS(-ul, result, 10);
    asrt_equ(result, "-12", "ultoaS");
    free(result);
    return 0;
}
