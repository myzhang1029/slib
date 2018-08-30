/*
 *  permcomb.c - Factorial, Permutation and Combination
 *
 *  Copyright (C) 2018 Zhang Maiyun
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

#include "slib/math.h"

OPT unsigned long slib_factorial(unsigned long oper)
{
    unsigned long n = oper;
    while (n != 2)
        oper *= --n;
    return oper;
}

/* nPr Permutation */
OPT unsigned long slib_permu(unsigned long num, unsigned long chosen)
{
    unsigned long result = 1, choosable = num - chosen;
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
OPT unsigned long slib_combi(unsigned long num, unsigned long chosen)
{
    return slib_permu(num, chosen) / slib_factorial(chosen);
}
