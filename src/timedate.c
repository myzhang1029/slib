/*
 *  timedate1.c - functions about time, date and calendars
 *
 *  Copyright (C) 2018-2019 Zhang Maiyun
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
#include <time.h>

#include "slib/timedate.h"

/* convert time in hours to hours, minutes and seconds */
OPT void slib_h2hms(double in_hours, double *out_hours, double *out_minutes,
                    double *out_seconds)
{
    double hfrac;
    *out_hours = (long)in_hours;
    hfrac = in_hours - *out_hours; /* the decimal part is out_hours */
    hfrac *= 60;                   /* now the unit is minutes */
    *out_minutes = (long)hfrac;
    *out_seconds = (hfrac - *out_minutes) * 60;
}

/* convert time in hours, minutes and seconds to hours */
OPT double slib_hms2h(double hours, double minutes, double seconds)
{
    return hours + minutes / 60 + seconds / 3600;
}

/* convert date to day count since Jan 1st */
OPT int slib_d2dn(int year, int month, int day)
{
    int n;
    if (isleap(year)) /* a leap year */
        n = 29;
    else
        n = 28;
    switch (month) /* you know what? I typed this */
    {
        case 1:
            return day;
        case 2:
            return 31 + day;
        case 3:
            return 31 + n + day;
        case 4:
            return 31 + n + 31 + day;
        case 5:
            return 31 + n + 31 + 30 + day;
        case 6:
            return 31 + n + 31 + 30 + 31 + day;
        case 7:
            return 31 + n + 31 + 30 + 31 + 30 + day;
        case 8:
            return 31 + n + 31 + 30 + 31 + 30 + 31 + day;
        case 9:
            return 31 + n + 31 + 30 + 31 + 30 + 31 + 31 + day;
        case 10:
            return 31 + n + 31 + 30 + 31 + 30 + 31 + 31 + 30 + day;
        case 11:
            return 31 + n + 31 + 30 + 31 + 30 + 31 + 31 + 30 + 31 + day;
        case 12:
            return 31 + n + 31 + 30 + 31 + 30 + 31 + 31 + 30 + 31 + 30 + day;
        default: /* what?? */
            return -1;
    }
}

/* get the time difference(in hours) between UTC and true local time
   (i.e. the sun is exactly south, north or overhead at 12:00)
   longitude in degrees */
OPT double slib_true_time_diff(double longitude)
{
    if (longitude > 0) /* east */
    {
        while (longitude >= 360)
            longitude -= 360; /* make sure |longitude| < 360deg */
        if (longitude > 180)
            longitude -= 360; /* E2W */
    }
    if (longitude < 0) /* west */
    {
        while (longitude <= -360)
            longitude += 360; /* make sure |longitude| < 360deg */
        if (longitude < -180)
            longitude += 360; /* W2E */
    }
    return longitude / 15.0;
}

OPT double slib_local_time(double longitude, double hours, double timezone)
{
    return hours - timezone + slib_true_time_diff(longitude);
}
