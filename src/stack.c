/*
 *  stack.c - stack in the slib
 *
 *  Copyright (C) 2017-2020 Zhang Maiyun
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

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "slib/error.h"
#include "slib/stack.h"

OPT int slib_stack_new(stackS *s, size_t size, size_t type_size)
{
    s->base = malloc(size);
    if (s->base == NULL)
        return Sfail_int(-1);
    s->top = s->base;
    s->size = size;
    s->type_size = type_size;
    return 0;
}

OPT int slib_stack_push(stackS *s, void *e)
{
    if ((intptr_t)s->top - (intptr_t)s->base + s->type_size > s->size)
        return 1;
    memcpy(s->top, e, s->type_size);
    s->top = (void *)((intptr_t)s->top + s->type_size);
    return 0;
}

OPT int slib_stack_pop(stackS *s, void *e)
{
    if (s->top == s->base)
        return 1;
    s->top = (void *)((intptr_t)s->top - (intptr_t)s->type_size);
    memcpy(e, s->top, s->type_size);
    return 0;
}

OPT size_t slib_stack_len(stackS *s)
{
    return ((intptr_t)s->top - (intptr_t)s->base) / s->type_size;
}

OPT void slib_stack_clear(stackS *s) { s->top = s->base; }

OPT void slib_stack_free(stackS *s)
{
    free(s->base);
    s->top = s->base = NULL;
    s->size = s->type_size = 0;
}
