#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define asrt_or_fail(e, s)                                                     \
    if (!(e))                                                                  \
    return 1
#ifndef DEBUG
#define asrt_equ(a, b, s) asrt_or_fail((a) == (b), s)
#define asrt_neq(a, b, s) asrt_or_fail((a) != (b), s)
#define asrt_str_equ(a, b, s) asrt_or_fail(strcmp((a), (b)) == 0, s)
#define asrt_str_neq(a, b, s) asrt_or_fail(strcmp((a), (b)) != 0, s)
#else
/* Note a and b will be evaluated twice */
#define asrt_equ(a, b, s)                                                      \
    do                                                                         \
    {                                                                          \
        printf("The result should be %d, and it's actually %d\n", (b), (a));   \
        asrt_or_fail((a) == (b), s);                                           \
    } while (0)
#define asrt_neq(a, b, s)                                                      \
    do                                                                         \
    {                                                                          \
        printf("The result should not be %d, and it's actually %d\n", (b),     \
               (a));                                                           \
        asrt_or_fail((a) != (b), s);                                           \
    } while (0);
#define asrt_str_equ(a, b, s)                                                  \
    do                                                                         \
    {                                                                          \
        printf("The result should be \"%s\", and it's actually \"%s\"\n", (b), \
               (a));                                                           \
        asrt_or_fail(strcmp((a), (b)) == 0, s);                                \
    } while (0)
#define asrt_str_neq(a, b, s)                                                  \
    do                                                                         \
    {                                                                          \
        printf("The result should not be \"%s\", and it's actually \"%s\"\n",  \
               (b), (a));                                                      \
        asrt_or_fail(strcmp((a), (b)) != 0, s);                                \
    } while (0)
#endif
#define quiet_asrt_equ(a, b, s)                                                \
    if ((a) != (b))                                                            \
    return 117
#define quiet_asrt_neq(a, b, s)                                                \
    if ((a) == (b))                                                            \
    return 117
