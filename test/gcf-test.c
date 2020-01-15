#include "tests.h"
#include <slib/math.h>
int gcf_main(void)
{
    asrt_equ(slib_gcf(1, 2), 1, "gcf-1,2");
    asrt_equ(slib_gcf(2, 4), 2, "gcf-2,4");
    asrt_equ(slib_gcf(17, 23), 1, "gcf-17,23");
    asrt_equ(slib_gcf(3, 9), 3, "gcf-3,9");
    return 0;
}
