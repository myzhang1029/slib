#include <slib.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
	char tmp1[]="test-iofile-XXXXXX";
	char tmp2[]="test-iofile-XXXXXX";
       	const char *const str="teststr";
	FILE *fp;
	printf("test-iofile: Testing prtfile() fcopy() iofile()(fcopy() and prtfile() was defined with iofile, so just test fcopy()\n");
	mktemp(tmp1);
	printf("test-iofile: Creating file fp with name %s and vaule \"%s\"\n", tmp1, str);
	if((fp = fopen(tmp1,"w"))==NULL)
	{
		prterr("fopen failed");
		exit(1);
	}
	fputs(str, fp);
	fclose(fp);
	fp=NULL;
	mktemp(tmp2);
	printf("test-iofile: Running fcopy(tmp1, tmp2)\n");
	fcopy(tmp1, tmp2);
	printf("test-iofile: Opening file fp with name %s\n", tmp2);
	if((fp=fopen(tmp2,"r"))==NULL)
	{
		prterr("Fopen failed");
		exit(1);
	}
	printf("test-iofile: Running prtfile(fp)\n");
	prtfile(fp);
	fclose(fp);
	remove(tmp1);
	remove(tmp2);
	return 0;
}
