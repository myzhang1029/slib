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

#include <stdarg.h>

#include "slib.h"

/*
 * colorprintf - Print in color on the terminal/console
 * Arguments:
 * fcolor: Foreground color
 * bcolor: Background color
 * Return vaule: status of printf returns
 */
OPT int colorprintf(enum cpfcolors fcolor, enum cpfcolors bcolor,
                    const char *format, ...)
{
    int stat = 1;
    va_list args;
#if PLAT
    HANDLE hstdout = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbInfo;
    WORD colornum = 0x0;
#endif
    va_start(args, format);
#if PLAT
    GetConsoleScreenBufferInfo(hstdout, &csbInfo);
    switch (fcolor)
    {
        case red:
            colornum = 0x4;
            break;
        case green:
            colornum = 0x2;
            break;
        case yellow:
            colornum = 0x6;
            break;
        case black:
            colornum = 0x7;
            break;
        case blue:
            colornum = 0x1;
            break;
        case magenta:
            colornum = 0x5;
            break;
        case cyan:
            colornum = 0x3;
            break;
        case unchanged:
            colornum = 0;
            break;
    }
    switch (bcolor)
    {
        case red:
            colornum += 0x40;
            break;
        case green:
            colornum += 0x20;
            break;
        case yellow:
            colornum += 0x60;
            break;
        case black:
            colornum += 0x70;
            break;
        case blue:
            colornum += 0x10;
            break;
        case magenta:
            colornum += 0x50;
            break;
        case cyan:
            colornum += 0x30;
            break;
        case unchanged:
            break;
    }
    SetConsoleTextAttribute(hstdout, colornum);
    stat = vprintf(format, args);
    SetConsoleTextAttribute(hstdout, csbInfo.wAttributes);
#else
    switch (fcolor)
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
        case cyan:
            printf("\033[36m");
            break;
        case unchanged:
            break;
    }
    switch (bcolor)
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
        case cyan:
            printf("\033[46m");
            break;
        case unchanged:
            break;
    }
    stat = vprintf(format, args);
    printf("\033[0m");
#endif
    va_end(args);
    return stat;
}
