#include <slib.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    if (ispn(2) == SFALSE)
    {
        printf("test-ispn: Failed on 2\n");
        exit(1);
    }
    else
        printf("test-ispn: 2 is a prime number\n");
    if (ispn(1) == STRUE)
    {
        printf("test-ispn: Failed on 1\n");
        exit(1);
    }
    else
        printf("test-ispn: 1 is not a prime number\n");
    if (ispn(3) == SFALSE)
    {
        printf("test-ispn: Failed on 3\n");
        exit(1);
    }
    else
        printf("test-ispn: 3 is a prime number\n");
    if (ispn(9) == STRUE)
    {
        printf("test-ispn: Failed on 9\n");
        exit(1);
    }
    else
        printf("test-ispn: 9 is not a prime number\n");
    if (ispn(97) == SFALSE)
    {
        printf("test-ispn: Failed on 97\n");
        exit(1);
    }
    else
        printf("test-ispn: 97 is a prime number\n");
    if (ispn(999983) == SFALSE)
    {
        printf("test-ispn: Failed on 999983\n");
        exit(1);
    }
    else
        printf("test-ispn: 999983 is a prime number\n");
    if (ispn(4) == STRUE)
    {
        printf("test-ispn: Failed on 4\n");
        exit(1);
    }
    else
        printf("test-ispn: 4 is not a prime number\n");
    return 0;
}
