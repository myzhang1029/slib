#include "tests.h"
#include <slib/math.h>

int main()
{
    asrt_equ(slib_eular(123), 80, "eular-123");
    asrt_equ(slib_eular(9), 6, "eular-9");
    asrt_equ(slib_eular(270), 72, "eular-270");
    asrt_equ(slib_eular(3397), 3276, "eular-3397");
    return 0;
}
