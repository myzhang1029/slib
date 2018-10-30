#include "tests.h"
#include <slib/math.h>

int pnlst_main(void)
{
    slib_uint min = 1, buffer[25], bufsize = 25;
    slib_pnlst(min, buffer, bufsize);
    asrt_equ(buffer[0], 2, "pnlst-0");
    asrt_equ(buffer[24], 97, "pnlst-24");
    return 0;
}
