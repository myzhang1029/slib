#include <slib/math.h>
#include "tests.h"

int main(void)
{
    asrt_neq(slib_ispn(2), SFALSE, "ispn-2");
    asrt_neq(slib_ispn(1), STRUE, "ispn-1");
    asrt_neq(slib_ispn(3), SFALSE, "ispn-3");
    asrt_neq(slib_ispn(9), STRUE, "ispn-9");
    asrt_neq(slib_ispn(97), SFALSE, "ispn-97");
    asrt_neq(slib_ispn(999983), SFALSE, "ispn-999983");
    return 0;
}
