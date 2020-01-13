/*
 *  overflow.h - C overflow detection
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

#include <slib/general.h>
#include <stdint.h>

/* Static overflow check */
#ifndef SLIB_MATH_CHECK_OVERFLOW
#define slib_add(r, a, b) (r) = ((a) + (b))
#define slib_sub(r, a, b) (r) = ((a) - (b))
#define slib_mul(r, a, b) (r) = ((a) * (b))
#define slib_div(r, a, b) (r) = ((a) / (b))
#else
#include <assert.h>
#define slib_add(r, a, b) (assert(((r) = ((a) + (b))) - (b) == (a)), r)
#define slib_sub(r, a, b) (assert(((r) = ((a) - (b))) + (b) == (a)), r)
#define slib_mul(r, a, b) (assert(((r) = ((a) * (b))) / (b) == (a)), r)
#define slib_div(r, a, b) (assert(((r) = ((a) / (b))) * (b) == (a)), r)
#endif
