#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#define asrt_or_fail(e, s)                                                     \
    ((e) ? printf("Test %s\nOK\n", (s))                                        \
         : (printf("Test %s\nFAILED\n", (s)), abort()))
#ifndef DEBUG
#define asrt_equ(a, b, s) asrt_or_fail((a) == (b), s)
#define asrt_neq(a, b, s) asrt_or_fail((a) != (b), s)
#else
#define asrt_equ(a, b, s) (printf("The result should be %d, and it's actually %d\n", (b), (a)),asrt_or_fail((a) == (b), s))
#define asrt_neq(a, b, s) (printf("The result should not be %d, and it's actually %d\n", (b), (a)),asrt_or_fail((a) != (b), s))
#endif
