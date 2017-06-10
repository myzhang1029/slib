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

/*
 * colorprintf - Print in color on the terminal/console
 * Arguments:
 * fcolor: Foreground color
 * bcolor: Background color
 * Return vaule: status of printf returns
 */
OPT int colorprintf(enum cpfcolors fcolor,enum cpfcolors bcolor,ccp format,...)
{
	int stat=1;
	va_list args;
#if PLAT
	HANDLE hstdout=GetStdHandle(STD_OUTPUT_HANDLE);
	WORD wOldColorAttrs;
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
#endif
	va_start(args,format);
#if PLAT
	GetConsoleScreenBufferInfo(handle, &csbiInfo);
	switch(fcolor)
	{
		case red:
			SetConsoleTextAttribute(hstdout,0x40);
			break;
		case green:
			SetConsoleTextAttribute(hstdout,0x20);
			break;
		case yellow:
			SetConsoleTextAttribute(hstdout,0x60);
			break;
		case black:
			SetConsoleTextAttribute(hstdout,0x70);
			break;
		case blue:
			SetConsoleTextAttribute(hstdout,0x10);
			break;
		case magenta:
			SetConsoleTextAttribute(hstdout,0x50);
			break;
	}
	switch(bcolor)
	{
		case red:
			SetConsoleTextAttribute(hstdout,0x4);
		case green:
		case yellow:
		case black:
		case blue:
		case magenta:
			Set
	}
	stat=vprintf(format,args);
	va_end(args);
	SetConsoleTextAttribute(hstdout,wOldColorAttrs);
	return stat;
#else
	switch(fcolor)
	{
		case red:
			printf("\033[31m");
			break;
		case green:
			printf("\033[32m");
			break;
		case yellow:
			printf("\033[33m");
			break;
		case black:
                        printf("\033[30m");
			break;
		case blue:
                        printf("\033[34m");
			break;
		case magenta:
                        printf("\033[35m");
			break;
	}
	switch(bcolor)
	{ 
		case red:
			printf("\033[41m");
			break; 
		case green:
			printf("\033[42m");
			break;
		case yellow:
			printf("\033[43m");
			break;
		case black:
                        printf("\033[40m");
			break;
		case blue:
                        printf("\033[44m");
			break;
		case magenta:
                        printf("\033[45m");
			break;
	}
	stat=vprintf(format,args);
	printf("\033[0m");
	return stat;
#endif
}

