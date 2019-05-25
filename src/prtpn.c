/*
 *  prtpn.c - Print prime numbers
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

OPT void slib_prtpn(slib_uint minimum, slib_uint maximum)
{
    slib_uint n = 0;
    if (maximum <= 2)
        return;
    if (maximum <= minimum)
        return;
    for (n = minimum; n <= maximum; ++n)
    {
        if (slib_ispn(n))
        {
            printf("%lu\n", n);
        }
    }
}
