/*
 *  stack.c - stack in the slib
 *
 *  Copyright (C) 2017 Zhang Maiyun
 *  Thanks a user on CSDN.NET for most of the code.
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
#include <string.h>
#include "slib/stack.h"

OPT int InitStack(sqStack *s, unsigned stackSize, unsigned typeSize)
{
    s->base = malloc(stackSize);
    if (!s->base)
        return SERROR;
    s->top = s->base;
    s->stackSize = stackSize;
    s->typeSize = typeSize;
    return STRUE;
}

OPT int Push(sqStack *s, void *e)
{
    if ((int)s->top - (int)s->base + s->typeSize > s->stackSize)
        return SFALSE;
    memcpy(s->top, e, s->typeSize);
    s->top = (void *)((int)s->top + s->typeSize);
    return STRUE;
}

OPT int Pop(sqStack *s, void *e)
{
    if (s->top == s->base)
        return SFALSE;
    s->top = (void *)((int)s->top - (int)s->typeSize);
    memcpy(e, s->top, s->typeSize);
    return STRUE;
}

OPT int GetLen(sqStack *s)
{
    return ((int)s->top - (int)s->base) / s->typeSize;
}

OPT int ClearStack(sqStack *s)
{
    s->top = s->base;
    return STRUE;
}

OPT int DestroyStack(sqStack *s)
{
    free(s->base);
    s->top = s->base = NULL;
    s->stackSize = s->typeSize = 0;
    return STRUE;
}
