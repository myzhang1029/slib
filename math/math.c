/*
 *  math.c - Math functions in the slib
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


OPT int ispn( cul testingnum )
{
	long i;
	if( testingnum == 2)
		return STRUE;
	for(i = 2; i<testingnum; ++i)
	{
		if( testingnum%i==0 )
			return SFALSE;
	}
	return STRUE;
}


OPT int  isrp (cul n1,cul n2)
{
	long counter;
	if(n1 == n2)
		return SFALSE;
	if(n1 == 1 || n2 == 1)
		return SFALSE;
	if(n1 % n2 == 0 || n2 % n1 == 0)
		return SFALSE;
	for(counter=2;
	        counter<(n1>n2?n2:n1);
	        ++counter)
	{
		if(n1 % counter == 0 && n2 % counter == 0)
			return SFALSE;
	}
	return STRUE;
}


OPT double average(cui amt,...)
{
	vlist args;
	int count;
	double sum=0.0;
	vstart(args,amt);
	for(count=0; count<amt; ++count)
	{
		sum+=varg(args,double);
	}
	vend(args);
	return (sum/amt);
}


OPT int  gcf(cui n1,cui n2)
{
	int count;
	if(n1==n2)
		return n1;
	if(n2%n1==0)
		return n1;
	if(n1%n2==0)
		return n2;
	for(count=n1>n2?n2/2:n1/2; count>1; --count)
	{
		if(n1%count==0&&n2%count==0)
			return count;
	}
	return 1;
}


OPT int lcm(cui n1,cui n2)
{
	return n1*n2/gcf(n1,n2);
}


OPT int eular(cui n)
{
	int count,result=0;
	for(count=0; count<n; ++count)
	{
		if(isrp(n,count))
			++count;
	}
	return result;
}

