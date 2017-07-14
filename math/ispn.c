/*
 *  ispn.c - ispn function in the slib
 *
 *  Copyright (C) 2017 Zhang Maiyun
 *  Function Hsqrt from Quake III and modifyed
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 *  This file is part of the slib.
 *  The slib is free software; you can redistribute it and/or modify
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

static long Hsqrt(long x)
{
    double long xhalf = 0.5f*x;
    int i = *(int*)&x;      // get bits for floating VALUE
    i = 0x5f375a86- (i>>1); // gives initial guess y0
    x = *(double*)&i;       // convert bits BACK to double
    x = x*(1.5f-xhalf*x*x); // Newton step, repeating increases accuracy
    x = x*(1.5f-xhalf*x*x); // Newton step, repeating increases accuracy
    x = x*(1.5f-xhalf*x*x); // Newton step, repeating increases accuracy
    
    return ((long)(1/x))+1l;
}

OPT int ispn( unsigned long testingnum )
{
	register unsigned long i;
    register unsigned long k=Hsqrt(testingnum);
	if( testingnum == 2)
		return STRUE;
	for(i = 2; i<k; ++i)
	{
		if( testingnum%i==0 )
			return SFALSE;
	}
	return STRUE;
}
