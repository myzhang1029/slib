#include "tests.h"
#include <slib/math.h>

int main(void)
{
    asrt_equ(slib_isrp(2, 3), STRUE, "isrp-2,3");
    asrt_equ(slib_isrp(5, 7), STRUE, "isrp-5,7");
    asrt_equ(slib_isrp(1, 2), STRUE, "isrp-1,2");
    asrt_equ(slib_isrp(9999, 9959), STRUE, "isrp-9999,9959");
    asrt_equ(slib_isrp(0, 0), SFALSE, "isrp-0,0");
    asrt_equ(slib_isrp(11, 275), SFALSE, "isrp-11,275");
    return 0;
}
