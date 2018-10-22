#include <slib.h>
#include "tests.h"

mtret testfunc(const char *arg1, const char *arg2) { mtreturn(2, arg1, arg2); }

int main()
{
    mtret ret = testfunc("123", "456");
    asrt_str_equ((char *)getret(&ret), "123", "mret-stage1");
    asrt_str_equ((char *)getret(&ret), "456", "mret-stage2");
    asrt_equ(getret(&ret), NULL, "mret-stage3");
    return 0;
}
