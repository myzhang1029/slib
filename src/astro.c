/*
 *  astro.c - astronomical functions in the slib
 *
 *  Copyright (C) 2018 - 2019 Zhang Maiyun
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
#include <math.h>
#define __STDC_WANT_LIB_EXT1__ 1
#include <time.h>

#include "slib/astro.h"
#include "slib/timedate.h"

/* radian and degree conversion */
OPT double slib_rad2deg(double radians) { return radians * 180 / S_PI; }

OPT double slib_deg2rad(double degrees) { return degrees * S_PI / 180; }

/* d is days passed since Jan 1st of the year
   returns the sun declination of the day in degrees */
OPT double slib_sun_decl_by_date(int d)
{
    return -dasin(0.39779 *
                  dcos(0.98565 * (d + 10) + 1.914 * dsin(0.98565 * (d - 2))));
}

/* single function version. Stands for Single Function Corrected Sunrise Hour
 * Angle. Always accepts UTC tm and returns a UTC time and UTC solartrans */
OPT double slib_sf_csha(double latitude, double longitude, double elevation,
                        double *solartrans, struct tm *tm)
{
    double jd = round(slib_tm2jd(tm));
    double jdy = slib_julian_day(jd);
    double msn = slib_mean_solar_noon(jdy, longitude);
    double sma = slib_solar_mean_anomaly(msn);
    double eoc = slib_equation_of_the_center_value(sma);
    double el = slib_ecliptic_longitude(sma, eoc);
    double sundec = slib_sun_decl(el);
    *solartrans = slib_solar_transit(msn, sma, el);
    return slib_corr_sunrise_hour_angle(latitude, sundec, elevation);
}

/* Full calculation for most uses.
 * Arguments:
 * latitude, longitude
 * elevation: in metres
 * utcnow: the UTC time for now, only tm_year, tm_mon and tm_mday matters(as
 * long as tm_hour, tm_min, tm_sec are in their range ) which tell me what day
 * to calculate for out_sunrise, out_sunset: Pointers to pre-allocated struct
 * tm. The result time zone is the time zone of the machine doing the
 * calculation since we don't know which time zone the destination is using */
OPT void slib_sf_sunrise(double latitude, double longitude, double elevation,
                         struct tm *utcnow, struct tm *out_sunrise,
                         struct tm *out_sunset)
{
    time_t localtm = mktime(utcnow); /* mktime assumes localtime */
    time_t gmtm;
#if defined(__STDC_LIB_EXT1__) || defined(_MSC_VER)
    struct tm buf;
    gmtm = mktime(gmtime_s(&localtm, &buf));
#elif defined(__unix__)
    struct tm buf;
    gmtm = mktime(gmtime_r(&localtm, &buf));
#else
    gmtm = mktime(gmtime(&localtm));
#endif
    /* get timezone from gmtime and localtime */
    double tz, sha, st, sunrise, sunset;
    tz = difftime(localtm, gmtm) / 3600;
    sha = slib_sf_csha(latitude, longitude, elevation, &st, utcnow);
    sunrise = st - sha / 360;
    sunrise += tz / 24;
    slib_jd2tm(sunrise, out_sunrise);
    sunset = st + sha / 360;
    sunset += tz / 24;
    slib_jd2tm(sunset, out_sunset);
}
