/*
 *  itoa.h - itoa, ltoa ultoa
 *
 *  Copyright (C) 2016-2020 Zhang Maiyun
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

#ifndef SLIB_ITOA_H
#define SLIB_ITOA_H 1
#include "slib/general.h"

_BEGIN_EXTERN_C

OPT char *itoaS(int value, char *string, int radix);

OPT char *ltoaS(long value, char *string, int radix);

OPT char *ultoaS(unsigned long value, char *string, int radix);

_END_EXTERN_C
#endif /* SLIB_ITOA_H */
