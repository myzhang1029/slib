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
#define SLIB_MATH_H 1
#include <slib/general.h>

#ifndef slib_uint
#define slib_uint unsigned long
#endif

_BEGIN_EXTERN_C

OPT void slib_prtpn(slib_uint minimum, slib_uint maximum);

OPT void slib_pnlst(slib_uint minimum, slib_uint *buffer, slib_uint bufsize);

OPT int slib_ispn(slib_uint testingnum);

OPT int slib_isrp(slib_uint n1, slib_uint n2);

OPT slib_uint slib_gcf(slib_uint n1, slib_uint n2);

OPT slib_uint slib_lcm(slib_uint n1, slib_uint n2);

OPT slib_uint slib_eular(slib_uint n);

OPT slib_uint slib_factorial(slib_uint oper);

OPT slib_uint slib_combi(slib_uint num, slib_uint chosen);

OPT slib_uint slib_permu(slib_uint num, slib_uint chosen);
_END_EXTERN_C

#endif /* SLIB_MATH_H */
