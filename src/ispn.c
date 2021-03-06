/*
 *  ispn.c - primary test
 *
 *  Copyright (C) 2017 Zhang Maiyun
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

#include <math.h>

#include "slib/math.h"

OPT slib_bool slib_old_ispn(slib_uint testingnum)
{
    slib_uint k = (slib_uint)sqrt((double)testingnum), i = 3;

    if (testingnum == 1 || ((testingnum & 1) == 0 && testingnum != 2))
        return 0;

    for (; i <= k; i++)
        if (testingnum % i == 0)
            return 0;

    return 1;
}

OPT slib_bool slib_ispn(slib_uint testingnum)
{
    slib_uint i = 3;

    if (((testingnum & 1) == 0 && testingnum != 2) || testingnum == 1)
        return 0;

    for (; i * i <= testingnum; i++)
        if (testingnum % i == 0)
            return 0;

    return 1;
}
