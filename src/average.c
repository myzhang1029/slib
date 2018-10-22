/*
 *  average.c - average function in the slib
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
#include "slib/math.h"

OPT double slib_average(unsigned int amt, ...)
{
    va_list args;
    unsigned int count;
    double sum = 0.0;
    va_start(args, amt);
    for (count = 0; count < amt; ++count)
    {
        sum += va_arg(args, double);
    }
    va_end(args);
    return (sum / amt);
}
