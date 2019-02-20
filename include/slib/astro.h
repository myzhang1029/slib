/*
 *  astro.h - Astronomical calculations of the slib
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

#ifndef SLIB_ASTRO_H
#define SLIB_ASTRO_H 1

#include "slib/general.h"

#define S_PI acos(-1.0)

/* trigonometry for degree */
#define dsin(deg) sin(slib_deg2rad(deg))
#define dcos(deg) cos(slib_deg2rad(deg))
#define dtan(deg) tan(slib_deg2rad(deg))
#define dasin(arg) slib_rad2deg(asin(arg))
#define dacos(arg) slib_rad2deg(acos(arg))
#define datan(arg) slib_rad2deg(atan(arg))

_BEGIN_EXTERN_C
OPT double slib_rad2deg(double radians);
OPT double slib_deg2rad(double degrees);
OPT double slib_sun_decl_by_date(int d);
OPT double slib_sf_csha(double latitude, double longitude, double elevation,
                        double *solartrans, struct tm *tm);
OPT void slib_sf_sunrise(double latitude, double longitude, double elevation, double tz,
                         struct tm *utcnow, struct tm *out_sunrise,
                         struct tm *out_sunset);
OPT double slib_julian_day(double julian_date);
OPT double slib_mean_solar_noon(double julian_day, double longitude);
OPT double slib_solar_mean_anomaly(double mean_solar_noon);
OPT double slib_equation_of_the_center_value(double solar_mean_anomaly);
OPT double slib_ecliptic_longitude(double solar_mean_anomaly, double eoc_value);
OPT double slib_solar_transit(double mean_solar_noon, double solar_mean_anomaly,
                              double ecliptic_longitude);
OPT double slib_sun_decl(double ecliptic_longitude);
OPT double slib_sunrise_hour_angle(double latitude, double sun_declination);
OPT double slib_corr_sunrise_hour_angle(double latitude, double sun_declination,
                                        double elevation);

_END_EXTERN_C
#endif
