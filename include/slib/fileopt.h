/*
 *  fileopt.h - File operations of the slib
 *
 *  Copyright (C) 2016-present Zhang Maiyun
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

#ifndef SLIB_FILEOPT_H
#define SLIB_FILEOPT_H 1

#include "slib/general.h"

_BEGIN_EXTERN_C

OPT long fsize(FILE *stream);

OPT void splitpathS(const char *path, char *drive, char *dirname,
                    char *basename, char *ext);

OPT long *slib_count_fl(FILE *file, long *pcount);

OPT long slib_fbsearch(const char *key, FILE *fp,
                       int (*compar)(const char *s1, const char *s2));

OPT void slib_fqsort(FILE *fp, int (*compar)(const char *s1, const char *s2));

#if !PLAT
OPT int getch(void);
OPT int kbhit(void);
#endif

_END_EXTERN_C
#endif
