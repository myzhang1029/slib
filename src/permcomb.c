/*
 *  permcomb.c - Factorial, Permutation and Combination
 *
 *  Copyright (C) 2018 Zhang Maiyun
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

OPT slib_uint slib_factorial(slib_uint oper)
{
    slib_uint n = oper;
    /* It's unsigned so I don't have to care about negative n */
    if (n < 2)
        return 1;
    while (n != 2)
        oper *= --n;
    return oper;
}

/* nPr Permutation */
OPT slib_uint slib_permu(slib_uint num, slib_uint chosen)
{
    slib_uint result = 1, choosable = num - chosen;
    /* optimizations */
    if (chosen == 1)
        return num;
    if (chosen == num)
        return slib_factorial(num);
    if (num < chosen)
        return 0;
    /* code */
    while (num > choosable)
        result *= num--;
    return result;
}

/* nCr Combination */
OPT slib_uint slib_combi(slib_uint num, slib_uint chosen)
{
    return slib_permu(num, chosen) / slib_factorial(chosen);
}
