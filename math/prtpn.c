/*
 *  prtpn.c - prtpn function in the slib
 *
 *  Copyright (C) 2017 Zhang Maiyun
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 *  This file is part of slib.
 *  slib is free software; you can redistribute it and/or modify
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

OPT int  prtpn( FILE*fp, cul minimum, cul maximum )
{
	long n=0,i=0;
	_Bool torf=0;
	if ( maximum<=2)
	{
		serr=2;
		prterr("input not allowed!");
	}

	if( minimum <= 2)
		fprintf(fp,"2\n");
	for(n=minimum; n<=maximum; ++n)
	{
		for(i=2; i<n; ++i)
		{
			if(n%i!=0)
				torf = 1;
			else
			{
				torf =0;
				break;
			}
		}
		if(torf==1)
		{
			fprintf(fp,"%lu\n",n);
		}
	}
	return STRUE;
}



