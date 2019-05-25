/*
 *  pnlst.c - Generate prime number list
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

OPT void slib_pnlst(slib_uint minimum, slib_uint *buffer, slib_uint bufsize)
{
    slib_uint n, count = 0;
    for (n = minimum; count < bufsize; ++n)
        if (slib_ispn(n))
            buffer[count++] = n;
}
