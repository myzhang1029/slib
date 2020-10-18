#include <slib/math.h>
#include "tests.h"

int ispn_main(void)
{
    asrt_equ(slib_ispn(2), 1, "ispn-2");
    asrt_equ(slib_ispn(1), 0, "ispn-1");
    asrt_equ(slib_ispn(3), 1, "ispn-3");
    asrt_equ(slib_ispn(9), 0, "ispn-9");
    asrt_equ(slib_ispn(97), 1, "ispn-97");
    asrt_equ(slib_ispn(999983), 1, "ispn-999983");
    return 0;
}
