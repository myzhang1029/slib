/*
 *  splitpathS.c - Path seperate function splitpathS (aka _splitpath on MS-Windows) of the slib.
 *
 *  Copyright (C) 2014 CSDN chinaeran
 *	- The original file was not copyrighted.
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

#include <string.h>
#include "slib.h"

/*File path seperater*/
#if PLAT
#define pathsep '\\'
#else
#define pathsep '/'
#endif

/*To seperate file name and file extend name*/

static void __split_whole_name(const char *whole_name, char *fname, char *ext)
{
	char *p_ext;

	/*The start of extend name*/
	p_ext = strrchr(whole_name, '.');

	/*If p_ext is null, the file is a file without real file name(hided in unix), like .gitignore, or it is a not
	 * allowed file in MS-Windows*/
	if (NULL != p_ext)
	{
		if (NULL != ext)
			strcpy(ext, p_ext);
		if (NULL != fname)
			snprintf(fname, p_ext - whole_name + 1, "%s", whole_name);
	}
	else
	{
		if (NULL != ext)
			ext[0] = '\0';
		if (NULL != fname)
			strcpy(fname, whole_name);
	}
}

void splitpathS(const char *path, char *drive, char *dir, char *fname, char *ext)
{
	char *p_whole_name;
	if (NULL != drive)
	{
#if !PLAT
		/*No such concept "drive" in unix*/
		drive[0] = '\0';
#else
		snprintf(drive, ((int *)strchr(path, '\\') - (int *)path), "%s", path);
#endif
	}

	/*If the path is null, just set all the vaules blank*/
	if (NULL == path)
	{
		if (NULL != dir)
			dir[0] = '\0';
		if (NULL != fname)
			fname[0] = '\0';
		if (NULL != ext)
			ext[0] = '\0';
		return;
	}

	/*If there is just directory in the path, don't seperate file name*/
	if (pathsep == path[strlen(path)])
	{
		if (NULL != dir)
			strcpy(dir, path);
		if (NULL != fname)
			fname[0] = '\0';
		if (NULL != ext)
			ext[0] = '\0';
		return;
	}

	/*The start of whole file name*/
	p_whole_name = strrchr(path, pathsep);

	/*If p_whole_name is null, means there is no directory infomation in path*/
	if (NULL != p_whole_name)
	{
		p_whole_name++;
		__split_whole_name(p_whole_name, fname, ext);

		if (NULL != dir)
			snprintf(dir, p_whole_name - path, "%s", path);
	}
	else
	{
		__split_whole_name(path, fname, ext);
		if (NULL != dir)
			dir[0] = '\0';
	}
	return;
}
