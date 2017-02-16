#include "slib.h"

OPT long  fsize( FILE * stream )
{
	long size;
	if ( !stream )
	{
		serr=2;
		return SERROR;
	}
	fseek( stream, 0L, SEEK_END );
	size = ftell( stream );
	return size;
}


OPT int  fcopy( ccp oldname, ccp newname ) /* user - sec7 */
{
	FILE * fold, *fnew;
	fold = fopen( oldname, "rb" );
	if ( !fold )
	{
		serr=1;
		puts("1");
		return SERROR;
	}
	fnew = fopen( newname, "wb" );
	if ( !fnew )
	{
		serr=1;
		fclose( fold );
		puts("2");
		return SERROR;
	}
	iofile( fold,fnew );
	fclose( fnew );
	fclose( fold );
	return STRUE;
}


OPT int  iofile(FILE *origin,FILE *dest)
{
	int ch;
	rewind(origin);
	if(feof(origin))
		return SERROR;
	while (1)
     {
         ch = fgetc( origin );
         if ( !feof( origin ) )
             fputc( ch, dest );
         else
             break;
     }
	return STRUE;
}


OPT int prtfile(FILE *stream)
{
	return iofile(stream,stdout);
}


