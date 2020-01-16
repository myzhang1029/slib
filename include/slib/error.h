/*
 *  error.h - Fatal errors handling
 *
 *  Copyright (C) 2020 Zhang Maiyun
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

#include <stdlib.h>

#include "slib/general.h"

static void Sfail_void()
{
#ifndef S_NOABRT
    abort();
#endif
    return;
}

static void *Sfail_ptr(void *ret)
{
#ifndef S_NOABRT
    abort();
#endif
    return ret;
}

static int Sfail_int(int nret)
{
#ifndef S_NOABRT
    abort();
#endif
    return nret;
}
