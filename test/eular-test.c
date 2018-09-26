#include <slib/math.h>
#include "tests.h"

int main()
{
    asrt_equ(80, slib_eular(123));
    asrt_equ(6, slib_eular(9));
    asrt_equ(72, slib_eular(270));
    asrt_equ(3276, slib_eular(3397));
    asrt_equ(0, slib_eular(0));
    return 0;
}
