#include <slib.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE *testfile;
    char *str = "HelloFsize";
    testfile = tmpfile();
    printf("test-fsize: Opening a temporary file\n");
    if (testfile == NULL)
    {
        prterr("Error opening file");
        exit(1);
    }
    colorprintf(green, unchanged, "finished\n");
    printf("test-fsize: Writing string str=\"%s\" into file\n", str);
    fputs(str, testfile);
    if (fsize(testfile) != 10)
    {
        prterr("Size not match");
        return 1;
    }
    else
        printf("test-fsize: Size matched(success)\n");
}
