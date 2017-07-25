#include <slib.h>

int main()
{
	int saveerr=errno;
	prterr("Testing prterr with errno %d", errno);
	__set_errno(EDOM);
	prterr("Testing prterr with errno %d", errno);
	__set_errno(saveerr);
	return 0;
}

