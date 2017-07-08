#include<stdio.h>
#include<time.h>

OPT void
sleepS(int seconds)
{
	clock_t t=clock();
	while(1)
	{
		if(((clock()-t)/CLOCKS_PER_SEC)>=seconds)
			return;
	}
}
int main()
{
sleepS(1);
return 0;
}

