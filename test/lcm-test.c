#include <slib/math.h>
#include "tests.h"

int main(void)
{
    asrt_equ(slib_lcm(1, 2), 2, "lcm-1,2");
    asrt_equ(slib_lcm(2, 4), 4, "lcm-2,4");
    asrt_equ(slib_lcm(17, 23), 391, "lcm-17,23");
    asrt_equ(slib_lcm(3, 9), 9, "lcm-3,9");
    return 0;
}
