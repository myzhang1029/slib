/*
 *  eular.c - eular function in the slib
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

#include "slib/math.h"

OPT slib_uint slib_eular(slib_uint n)
{
    slib_uint count;
    slib_uint result = 0;
    for (count = 0; count < n; ++count)
    {
        if (slib_isrp(n, count))
            ++result;
    }
    return result;
}
