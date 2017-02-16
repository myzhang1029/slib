#include "slib.h"

int ser;

OPT int  prterr(ccp fmt,... )
{
	vlist argptr;
	vstart(argptr, fmt);
	fprintf(stderr,"Error:");
	vfprintf(stderr,fmt,argptr);
	if(errno != 0)
		fprintf(stderr,"errcode:%d,more facts:%s\n",errno,strerror(errno));
	else
		fprintf(stderr,"errcode:%d",serr);
	vend(argptr);
	return STRUE;
}


OPT int *  _serrloc( void )
{
	return &ser;
}

 
