/*
 *  module.c - Module name process function of the slib
 *
 *  Copyright (C) 2017 Zhang Maiyun
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 *  This file is part of the slib.
 *  The slib  is free software; you can redistribute it and/or modify
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

OPT int getmname(ccp fullpath,char *mname)
{
	int count,count2=0,fpathl=strlen(fullpath);
	for(count=fpathl;count>=0;--count)
	{
		if(fullpath[count]==pathsep)
		{
			for(++count;count<=fpathl;++count,++count2)
			{
				mname[count2]=fullpath[count];
			}
			return STRUE;
		}
	}
	return SFALSE;
}


OPT int getmpath(ccp fullpath,char *mpath)
{
	int count,count2,fpathl=strlen(fullpath);
	for(count=fpathl;count>=0;--count)
	{
		if(fullpath[count]==pathsep)
		{
			for(count2=0;count2<count;++count2)
			{
				mpath[count2]=fullpath[count2];
			}
			mpath[count2+1]='\0';
			mpath[count2]=pathsep;
			return STRUE;
		}
	}
	return SFALSE;
}


