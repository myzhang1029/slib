/*
 *  stack.h - Stack functions
 *
 *  Copyright (C) 2018-2020 Zhang Maiyun
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

#ifndef SLIB_STACK_H
#define SLIB_STACK_H 1
#include <slib/general.h>

#define STKELMT 100    /*Stack max. element count*/
#define BUFFERSIZE 100 /*Stack buffer size*/

_BEGIN_EXTERN_C

typedef struct Stack
{
    void *base;
    void *top;
    size_t size;
    size_t type_size;
} stackS;

OPT int slib_stack_new(stackS *s, size_t size, size_t type_size);

OPT int slib_stack_push(stackS *s, void *e);

OPT int slib_stack_pop(stackS *s, void *e);

OPT size_t slib_stack_len(stackS *s);

OPT void slib_stack_clear(stackS *s);

OPT void slib_stack_free(stackS *s);
_END_EXTERN_C

#endif /* SLIB_STACK_H */
