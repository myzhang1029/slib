/*
 *  mret.c - Multi return functions of the slib
 *
 *  Copyright (C) 2017 Zhang Maiyun
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
#include <stdarg.h>
#include <stdlib.h>
#include "slib.h"

mtret mkret(size_t lenth, ...)
{
    mtret ret;
    int **elems = malloc(sizeof(int *) * lenth);
    int count = 0;
    va_list args;
    if (elems == NULL)
        return (mtret){0, 0, NULL};
    va_start(args, lenth);

    ret.lenth = lenth;
    for (; count < (int)lenth; ++count)
    {
        elems[count] = va_arg(args, int *);
    }
    ret.val = elems;
    va_end(args);
    elems = NULL;
    ret.retind = 0;
    return ret;
}

int *getret(mtret *ret)
{
    if (ret->retind < ret->lenth)
        return ret->val[ret->retind++];
    free(ret->val);
    return NULL;
}
