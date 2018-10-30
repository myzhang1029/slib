#include "tests.h"
#include <slib/math.h>

int average_main()
{
    asrt_equ(slib_average(5, 1.0, 3.0, 5.0, 7.0, 9.0), 5.0, "average-positive");
    asrt_equ(slib_average(5, -1.0, -3.0, -5.0, -7.0, -9.0), -5.0,
             "average-negative");
    return 0;
}
