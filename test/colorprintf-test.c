#include <slib.h>
int colorprintf_main()
{
    colorprintf(red, yellow, "red on yellow");
    printf(" ");
    colorprintf(green, black, "green on black");
    printf(" ");
    return 0;
}
