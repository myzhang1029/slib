#include "tests.h"
#include <slib/math.h>

int permcomb_main(void)
{
    asrt_equ(slib_factorial(0), 1, "factorial-0");
    asrt_equ(slib_factorial(1), 1, "factorial-1");
    asrt_equ(slib_factorial(2), 2, "factorial-2");
    asrt_equ(slib_factorial(3), 6, "factorial-3");
    asrt_equ(slib_factorial(4), 24, "factorial-4");
    asrt_equ(slib_factorial(5), 120, "factorial-5");
    asrt_equ(slib_factorial(6), 720, "factorial-6");
    asrt_equ(slib_permu(9, 9), 362880, "permutation-9,9");
    asrt_equ(slib_permu(11, 10), 39916800, "permutation-11,10");
    asrt_equ(slib_combi(9, 9), 1, "combination-9,9");
    asrt_equ(slib_combi(11, 10), 11, "combination-11,10");
    return 0;
}
