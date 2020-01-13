/*
 *  timedate.h - Time and date operations of the slib
 *
 *  Copyright (C) 2018-2020 Zhang Maiyun
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

#ifndef SLIB_TIMEDATE_H
#define SLIB_TIMEDATE_H 1

#include "slib/general.h"

/* leap year: every four years before 1582 or exclude non-four-hundredth if it's
 * a centennial year */
/* leap year here: proleptic */
#define isleap(year) (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0))

_BEGIN_EXTERN_C

OPT void slib_h2hms(double in_hours, double *out_hours, double *out_minutes,
                    double *out_seconds);

OPT double slib_hms2h(double hours, double minutes, double seconds);

OPT int slib_d2dn(int year, int month, int day);

OPT double slib_true_time_diff(double longitude);

OPT double slib_local_time(double longitude, double hours, double timezone);

OPT double slib_tm2jd(struct tm *tm);

OPT void slib_jd2tm(double jd, struct tm *tm);

_END_EXTERN_C
#endif
