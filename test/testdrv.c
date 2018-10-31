#include "testdrv.h"

int main(void)
{
    int total = 0, faileds = 0, i;
    for (i = 0; testcases[i].name; ++i)
    {
        ++total;
        printf("Test %s\t", testcases[i].name);
        switch (testcases[i].entry())
        {
            case 0:
                puts("OK");
                break;
            case 114:
                puts("NOT FINISHED");
                break;
            case 115:
                puts("SKIP");
                break;
            case 116:
                puts("NOT OK");
                break;
            case 117:
                puts("INTERNAL ERROR");
                /* pass thru */
            default:
                puts("FAIL");
                ++faileds;
        }
    }
    printf("%d/%d tests failed\n", faileds, total);
    return !(faileds == 0);
}
