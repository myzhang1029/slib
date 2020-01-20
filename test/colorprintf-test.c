#include <slib.h>
int colorprintf_main(void)
{
    colorprintf(red, yellow, "red on yellow");
    printf(" ");
    colorprintf(green, black, "green on black");
    printf(" ");
    return 0;
}
