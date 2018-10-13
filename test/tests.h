#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if defined(QUIET)
#define asrt_or_fail(e, s) ((e) ? (0) : (abort(), 0))
#elif defined(NOABORT)
#define asrt_or_fail(e, s)                                                     \
    ((e) ? (printf("Test %s\nOK\n", (s)))                                      \
         : (printf("Test %s\nFAILED\n", (s))))
#else
#define asrt_or_fail(e, s)                                                     \
    ((e) ? (printf("Test %s\nOK\n", (s)))                                      \
         : (printf("Test %s\nFAILED\n", (s))))
#endif
#ifndef DEBUG
#define asrt_equ(a, b, s) asrt_or_fail((a) == (b), s)
#define asrt_neq(a, b, s) asrt_or_fail((a) != (b), s)
#define asrt_str_equ(a, b, s) asrt_or_fail(strcmp((a), (b)) == 0, s)
#define asrt_str_neq(a, b, s) asrt_or_fail(strcmp((a), (b)) != 0, s)
#else
#define asrt_equ(a, b, s)                                                      \
    (printf("The result should be \"%s\", and it's actually \"%s\"\n", (b), (a)),      \
     asrt_or_fail((a) == (b), s))
#define asrt_neq(a, b, s)                                                      \
    (printf("The result should not be \"%s\", and it's actually \"%s\"\n", (b), (a)),  \
     asrt_or_fail((a) != (b), s))
#define asrt_str_equ(a, b, s)                                                      \
    (printf("The result should be \"%s\", and it's actually \"%s\"\n", (b), (a)),      \
     asrt_or_fail(strcmp((a), (b)) == 0, s))
#define asrt_str_neq(a, b, s)                                                      \
    (printf("The result should not be \"%s\", and it's actually \"%s\"\n", (b), (a)),  \
     asrt_or_fail(strcmp((a), (b)) != 0, s))
#endif
