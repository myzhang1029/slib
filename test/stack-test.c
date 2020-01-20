#include "tests.h"
#include <slib/stack.h>

int stack_main(void)
{
    stackS s;
    int poper, pusher[] = {5, 6, 4766, -1, 30000, -30000, 0}, count;
    asrt_neq(slib_stack_new(&s, sizeof(int) * 7, sizeof(int)), -1, "new");
    for (count = 0; count < 7; ++count)
        slib_stack_push(&s, &(pusher[count]));
    asrt_equ(slib_stack_len(&s), 7, "push, len");
    slib_stack_pop(&s, &poper);
    asrt_equ(poper, 0, "pop");
    asrt_equ(slib_stack_len(&s), 6, "pop, len");
    slib_stack_clear(&s);
    asrt_equ(slib_stack_len(&s), 0, "clear");
    slib_stack_free(&s);
    return 0;
}
