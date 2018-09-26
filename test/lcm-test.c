#include <slib/math.h>

int main(void)
{
    int errorlevel = 0;
    if (slib_lcm(1, 2) != 2)
    {
        errorlevel = 1;
        error("test-lcm: 1, 2failed\n");
    }
    if (slib_lcm(2, 4) != 4)
    {
        errorlevel = 1;
        error("test-lcm: 2, 4failed\n");
    }
    if (slib_lcm(17, 23) != 391)
    {
        errorlevel = 1;
        error("test-lcm: 17, 23failed\n");
    }
    if (slib_lcm(3, 9) != 9)
    {
        errorlevel = 1;
        error("test-lcm: 3, 9failed\n");
    }
    printf("test-lcm: End\n");
    return errorlevel;
}
