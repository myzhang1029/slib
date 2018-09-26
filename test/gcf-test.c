#include <slib.h>

int main(void)
{
    int errorlevel = 0;
    if (gcf(1, 2) != 1)
    {
        errorlevel = 1;
        prterr("test-gcf: 1, 2failed\n");
    }
    if (gcf(2, 4) != 2)
    {
        errorlevel = 1;
        prterr("test-gcf: 2, 4failed\n");
    }
    if (gcf(17, 23) != 1)
    {
        errorlevel = 1;
        prterr("test-gcf: 17, 23failed\n");
    }
    if (gcf(3, 9) != 3)
    {
        errorlevel = 1;
        prterr("test-gcf: 3, 9failed\n");
    }
    printf("test-gcf: End\n");
    return errorlevel;
}
