/*
 *  math.h - Arithmetic functions
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
#ifndef SLIB_MATH_H
#define SLIB_MATH_H
#include <slib/general.h>

_BEGIN_EXTERN_C

OPT void slib_prtpn(unsigned long minimum, unsigned long maximum);

OPT int slib_ispn(unsigned long testingnum);

OPT int slib_isrp(unsigned n1, unsigned n2);

OPT double slib_average(unsigned int amt, ...);

OPT unsigned long slib_gcf(unsigned long n1, unsigned long n2);

OPT unsigned long slib_lcm(unsigned long n1, unsigned long n2);

OPT int slib_eular(unsigned n);

_END_EXTERN_C

#endif /* SLIB_MATH_H */
