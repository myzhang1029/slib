/*
 *  initstack.c - Inital stack function in the slib
 *
 *  Copyright (C) 2017 Zhang Maiyun
 *  Thanks a user on CSDN.NET for most of the code.
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
#include <stdlib.h>
#include "slib.h"

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
