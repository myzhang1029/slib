/*
 *  error.c - Error digest in the slib
 *
 *  Copyright (C) 2017 Zhang Maiyun
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation; either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
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

 
