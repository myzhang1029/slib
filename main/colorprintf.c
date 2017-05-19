/*
 *  colorprintf.c - colorprintf function of the slib
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

OPT int colorprintf(enum cpfcolors fcolor,ccp format,...)
{
	int stat=1;
	va_list args;
#if PLAT
	HANDLE hstdout=GetStdHandle(STD_OUTPUT_HANDLE);
#else
	char *clstr=malloc(sizeof(format)+9);
#endif
	va_start(args,format);
#if PLAT
	switch(fcolor)
	{
		case red:
			SetConsoleTextAttribute(hstdout,FOREGROUND_RED);
			stat=vprintf(format,args);
			SetConsoleTextAttribute(hstdout,FOREGROUND_WHITE);
			break;
		case green:
			SetConsoleTextAttribute(hstdout,FOREGROUND_GREEN);
			stat=vprintf(format,args);
			SetConsoleTextAttribute(hstdout,FOREGROUND_WHITE);
			break;
		case yellow:
			SetConsoleTextAttribute(hstdout,FOREGROUND_RED|FOREGROUND_GREEN);
			stat=vprintf(format,args);
			SetConsoleTextAttribute(hstdout,FOREGROUND_WHITE);
			break;
		case black:
			SetConsoleTextAttribute(hstdout,BACKGROUND_RED|BACKGROUND_BLUE|BACKGROUND_GREEN);
			stat=vprintf(format,args);
			SetConsoleTextAttribute(hstdout,FOREGROUND_WHITE);
			break;
		case blue:
			SetConsoleTextAttribute(hstdout,FOREGROUND_BLUE);
			stat=vprintf(format,args);
			SetConsoleTextAttribute(hstdout,FOREGROUND_WHITE);
			break;
		case purple:
			SetConsoleTextAttribute(hstdout,FOREGROUND_RED|FOREGROUND_BLUE);
			stat=vprintf(format,args);
			SetConsoleTextAttribute(hstdout,FOREGROUND_WHITE);
			break;
		}
	va_end(args);
	return stat;
#else
	switch(fcolor)
	{
		case red:
			clstr="\x1b[31m";
			stat=vprintf(strcat(clstr,format),args);
			break;
		case green:
			clstr="\x1b[32m";
			stat=vprintf(strcat(clstr,format),args);
			break;
		case yellow:
			clstr="\x1b[33m";
			stat=vprintf(strcat(clstr,format),args);
			break;
		case black:
                        clstr="\x1b[30m";
			stat=vprintf(strcat(clstr,format),args);
			break;
		case blue:
                        clstr="\x1b[33m";
			stat=vprintf(strcat(clstr,format),args);
			break;
		case purple:
                        clstr="\x1b[35m";
			stat=vprintf(strcat(clstr,format),args);
			break;
	}
	free(clstr);
	clstr=NULL;
	return stat;
#endif
}


