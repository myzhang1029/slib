#include <slib/itoa.h>
#include "tests.h"
int main(void)
{
    int i = 12;
    long l = 12;
    unsigned long ul = 12;
    char *result = "init";
    itoaS(i, result, 10);
    asrt_equ(result, "12", "itoaS");
    ltoaS(l, result, 10);
    asrt_equ(result, "12", "ltoaS");
    ultoaS(ul, result, 10);
    asrt_equ(result, "12", "ultoaS");
    return 0;
}
