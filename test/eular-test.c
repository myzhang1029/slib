#include <slib.h>
#include <stdio.h>

int main()
{
	printf("test-eular: phi(123)=%d\n", eular(123));	
	printf("test-eular: phi(9)=%d\n", eular(9));
	printf("test-eular: phi(270)=%d\n", eular(270));
	printf("test-eular: phi(3397)=%d\n", eular(3397));
	printf("test-eular: phi(0)=%d\n", eular(0));
	return 0;
}

