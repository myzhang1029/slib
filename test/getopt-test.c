#include "tests.h"
#include <slib/getopt.h>

int getopt_main(void)
{
    int c;
    static const struct optionGS opts[] = {
        {"one", no_argument, NULL, '1'},
        {"two", no_argument, NULL, '2'},
        {"three", optional_argument, NULL, '3'},
        {"four", required_argument, NULL, '4'},
        {NULL, 0, NULL, 0}};

    const char *argv[] = {"test", "--on", "--two", "-3", "-4", "90"};
    int argc = 6;
    struct should
    {
        int ret;
        const char *arg;
        int isok;
    } shouldlst[] = {
        {1, NULL, 0}, {2, NULL, 0}, {3, NULL, 0}, {4, "90", 0}, {0, NULL, 0}};
    while ((c = getopt_longGS(argc, (char *const *)argv, "123::4:", opts,
                              NULL)) != -1)
    {
#ifdef DEBUG
        printf("%d returned\n", c);
#endif
        c -= '1' - 1;
        if (shouldlst[c - 1].arg == NULL || shouldlst[c - 1].arg == optargGS)
            shouldlst[c - 1].isok = 1;
    }
    c = 0;
    while (shouldlst[c].ret)
    {
        asrt_equ(shouldlst[c].isok, 1, "getopt");
        ++c;
    }
    return 0;
}
