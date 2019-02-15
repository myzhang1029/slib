/* for all lats and longs: north and east are positive and in degrees */
/* References:
 * 1. "Sunrise equation": Wikipedia https://en.wikipedia.org/wiki/Julian_day
 *
 * This work is licensed under the Creative Commons Attribution-ShareAlike 3.0
 * Unported License. To view a copy of this license, visit
 * http://creativecommons.org/licenses/by-sa/3.0/ or send a letter to
 * Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */

#include <math.h>
#include <time.h>

#include "slib/astro.h"

/* calculate current Julian Day from Julian Date [1] */
OPT double slib_julian_day(double julian_date)
{
    return julian_date - 2451545.0 + 0.0008;
}

/* mean solar noon [1] */
OPT double slib_mean_solar_noon(double julian_day, double longitude)
{
    return julian_day - longitude / 360;
}

/* solar mean anomaly [1] */
OPT double slib_solar_mean_anomaly(double mean_solar_noon)
{
    return fmod(357.5291 + 0.98560028 * mean_solar_noon, 360);
}

/* equation of the center [1] */
OPT double slib_equation_of_the_center_value(double solar_mean_anomaly)
{
    return 1.9148 * dsin(solar_mean_anomaly) +
           0.0200 * dsin(2 * solar_mean_anomaly) +
           0.0003 * dsin(3 * solar_mean_anomaly);
}

/* ecliptic longitude [1]
 * eoc: equation of the center value */
OPT double slib_ecliptic_longitude(double solar_mean_anomaly, double eoc_value)
{
    return fmod(solar_mean_anomaly + eoc_value + 180 + 102.9372, 360);
}

/* solar transit [1]
 * returns a julian date */
OPT double slib_solar_transit(double mean_solar_noon, double solar_mean_anomaly,
                              double ecliptic_longitude)
{
    return 2451545.0 + mean_solar_noon + 0.0053 * dsin(solar_mean_anomaly) -
           0.0069 * dsin(2 * ecliptic_longitude);
}

/* declination of the sun [1] */
OPT double slib_sun_decl(double ecliptic_longitude)
{
    return dasin(dsin(ecliptic_longitude) * dsin(23.44));
}

/* the sunrise equation [1]
   latitude and sun_declination in degrees
   cos(ωo) = -tan(φ)*tan(δ)
   returns the hour angle before local noon in degrees */
OPT double slib_sunrise_hour_angle(double latitude, double sun_declination)
{
    return dacos(-dtan(latitude) * dtan(sun_declination));
}

/* the sunrise equation with corrections [1]
   latitude and sun_declination in degrees; elevation in meters
   cos(ωo) = (sin(0.83°-2.076°*sqrt(elevation)/60°) -
   sin(φ)*sin(δ))/(cos(φ)*cos(δ)) */
OPT double slib_corr_sunrise_hour_angle(double latitude, double sun_declination,
                                        double elevation)
{
    return dacos((dsin(0.83 - 2.076 * sqrt(elevation) / 60) -
                  dsin(latitude) * dsin(sun_declination)) /
                 (dcos(latitude) * dcos(sun_declination)));
}
