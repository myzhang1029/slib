/*
 *  mret.c - Multi return functions of the slib
 *
 *  Copyright (C) 2017-present Zhang Maiyun
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
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

#include "slib.h"

OPT mtret *mkret(size_t length, ...)
{
    mtret *ret = (mtret *)malloc(sizeof(mtret));
    int **elems = (int **)malloc(sizeof(int *) * length);
    va_list args;
    if (elems == NULL)
        return (mtret *)memset(ret, 0, sizeof(mtret));
    va_start(args, length);
    ret->length = length;
    ret->base = ret->val = elems;
    while (length--)
        *elems++ = va_arg(args, int *);
    va_end(args);
    return ret;
}

OPT int *getret(mtret *ret)
{
    if (ret->length)
    {
        --(ret->length);
        return *(ret->val)++;
    }
    free(ret->base);
    free(ret);
    return NULL;
}
