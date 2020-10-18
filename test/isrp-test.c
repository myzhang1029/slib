#include <slib/math.h>
#include "tests.h"

int isrp_main(void)
{
    asrt_equ(slib_isrp(2, 3), 1, "isrp-2,3");
    asrt_equ(slib_isrp(5, 7), 1, "isrp-5,7");
    asrt_equ(slib_isrp(1, 2), 1, "isrp-1,2");
    asrt_equ(slib_isrp(9999, 9959), 1, "isrp-9999,9959");
    asrt_equ(slib_isrp(0, 0), 0, "isrp-0,0");
    asrt_equ(slib_isrp(11, 275), 0, "isrp-11,275");
    return 0;
}
