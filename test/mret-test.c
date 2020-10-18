#include <slib.h>
#include "tests.h"

mtret *testfunc(const char *arg1, const char *arg2) { mtreturn(2, arg1, arg2); }

int mret_main(void)
{
    char *retstr;
    mtret *ret = testfunc("123", "456");
    retstr = (char *)getret(ret);
    asrt_str_equ(retstr, "123", "mret-stage1");
    retstr = (char *)getret(ret);
    asrt_str_equ(retstr, "456", "mret-stage2");
    retstr = (char *)getret(ret);
    asrt_equ(retstr, NULL, "mret-stage3");
    return 0;
}