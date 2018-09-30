/*
 *  slib.h - This is the header file of the slib
 *
 *  Copyright (C) 2016 - 2018 Zhang Maiyun
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

#if defined(_MSC_VER) && _MSC_VER >= 100
#pragma once
#endif

#ifndef SLIB_H
#define SLIB_H 1

#include <slib/general.h>

#define mtreturn(lenth, ...) return mkret(lenth, __VA_ARGS__)

#if PLAT
#define FOREGROUND_WHITE (FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN)
#endif

_BEGIN_EXTERN_C

/*External variables*/
extern unsigned retind;

typedef struct mtrt
{
    size_t lenth;
    int **val;
} mtret;

enum cpfcolors
{
    red = 1,
    green,
    yellow,
    black,
    blue,
    magenta,
    cyan,
    unchanged
};

/*declation start*/
D_TESTING OPT int colorprintf(enum cpfcolors fcolor, enum cpfcolors bcolor,
                              const char *format, ...);

OPT int *getret(mtret ret);

OPT mtret mkret(size_t lenth, ...);

OPT void sleepS(int seconds);

_END_EXTERN_C

#endif /*SLIB_H*/
