/* for all lats and longs: north and east are positive and in degrees */
/* References:
 * 1. "Sunrise equation": Wikipedia
 * 2. "Julian Day": Wikipedia
 * Those are available under CC-BY-SA.
 * Other formulas in this file are my own thoughts.
 *
 * This work is licensed under the Creative Commons Attribution-ShareAlike 3.0
 * Unported License. To view a copy of this license, visit
 * http://creativecommons.org/licenses/by-sa/3.0/ or send a letter to
 * Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
#include <math.h>
#include <time.h>

#define S_PI acos(-1.0)
/* trigonometry for degree */
#define dsin(deg) sin(slib_deg2rad(deg))
#define dcos(deg) cos(slib_deg2rad(deg))
#define dtan(deg) tan(slib_deg2rad(deg))
#define dasin(arg) slib_rad2deg(asin(arg))
#define dacos(arg) slib_rad2deg(acos(arg))
#define datan(arg) slib_rad2deg(atan(arg))
/* leap year: every four years before 1582 or exclude non-four-hundredth if it's
 * a centennial year */
/* leap year here: proleptic */
#define isleap(year) (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0))

/* radian and degree conversion, stable API */
double slib_rad2deg(double radians) { return radians * 180 / S_PI; }

double slib_deg2rad(double degrees) { return degrees * S_PI / 180; }

/* convert time in hours to hours, minutes and seconds, stable API */
void slib_h2hms(double in_hours, double *out_hours, double *out_minutes,
                double *out_seconds)
{
    double hours_fracpart =
        modf(in_hours, out_hours); /* the decimal part is out_hours */
    hours_fracpart *= 60;
    *out_seconds = modf(hours_fracpart, out_minutes);
    *out_seconds *= 60;
}
/* convert time in hours, minutes and seconds to hours, stable API */
double slib_hms2h(double hours, double minutes, double seconds)
{
    return hours + minutes / 60 + seconds / 3600;
}

/* convert date to day count since Jan 1st, stable API*/
int slib_d2dn(int year, int month, int day)
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

/* d is days passed since Jan 1st of the year
   returns the sun declination of the day in degrees, stable API */
double slib_sun_decl_by_date(int d)
{
    return -dasin(0.39779 *
                  dcos(0.98565 * (d + 10) + 1.914 * dsin(0.98565 * (d - 2))));
}

/* get the time difference(in hours) between UTC and true local time
   (i.e. the sun is exactly south, north or overhead at 12:00)
   longitude in degrees */
double slib_true_time_diff(double longitude)
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

double slib_local_time(double longitude, double hours, double timezone)
{
    return hours - timezone + slib_true_time_diff(longitude);
}

/* convert hour angle to hour difference, stable API */
double slib_hour_angle_to_hour_diff(double hour_angle)
{
    return hour_angle / 15.0;
}

/* convert tm structure to Julian Date [2], stable API */
double slib_tm2jd(struct tm tm)
{
    int y = tm.tm_year + 1900, m = tm.tm_mon + 1, d = tm.tm_mday;
    double jdn = (1461 * (y + 4800 + (m - 14) / 12)) / 4 +
                 (367 * (m - 2 - 12 * ((m - 14) / 12))) / 12 -
                 (3 * ((y + 4900 + (m - 14) / 12) / 100)) / 4 + d - 32075;
    if (y < -4713 || y == -4713 && m < 11 ||
        y == -4713 && m == 11 &&
            d <= 23) /* The algorithm is invalid here TODO */
        return -1;
    /* note the result of slib_hms2h might be negative */
    return jdn + (tm.tm_hour - 12.0 /* midnight2noon */) / 24.0 +
           tm.tm_min / 1440.0 + tm.tm_sec / 86400.0;
}

/* convert Julian Date back to tm structure [2], stable for all AD times */
void slib_jd2tm(double jd, struct tm *tm)
{
    int jdn = (int)jd;
    double frac = jd - jdn;
    int day, month, year;
    double hour, min, sec;
    int e, f, g, h, j, m, n, p, r, s, u, v, w, y, B, C;
    y = 4716, j = 1401, m = 2, n = 12, r = 4, p = 1461, v = 3, u = 5, s = 153,
    w = 2, B = 274277, C = -38;
    f = jdn + j + (((4 * jdn + B) / 146097) * 3) / 4 + C;
    e = r * f + v;
    g = e % p / r;
    h = u * g + w;
    day = h % s / u + 1;
    month = (h / s + m) % n + 1;
    year = e / p - y + (n + m - month) / n;
    if (frac >= 0.5)
    {
        ++day;
        frac -= 0.5;
    }
    else
    {
        frac += 0.5;
    }
    slib_h2hms(frac * 24, &hour, &min, &sec);
    tm->tm_sec = sec;
    tm->tm_min = min;
    tm->tm_hour = hour;
    tm->tm_mday = day;
    tm->tm_mon = month - 1;
    tm->tm_year = year - 1900;
    /* must I fill out the whole structure? */
    if (frac < 0.5)
        tm->tm_wday = (jdn + 1) % 7;
    else
        tm->tm_wday = jdn % 7 + 1;
    tm->tm_yday = slib_d2dn(year, month, day);
    tm->tm_isdst = -1;
}

/* calculate current Julian Day from Julian Date [1] */
double slib_julian_day(double julian_date)
{
    return julian_date - 2451545.0 + 0.0008;
}

/* mean solar noon [1] */
double slib_mean_solar_noon(double julian_day, double longitude)
{
    return julian_day - longitude / 360;
}

/* solar mean anomaly [1] */
double slib_solar_mean_anomaly(double mean_solar_noon)
{
    return fmod(357.5291 + 0.98560028 * mean_solar_noon, 360);
}

/* equation of the center [1] */
double slib_equation_of_the_center_value(double solar_mean_anomaly)
{
    return 1.9148 * dsin(solar_mean_anomaly) +
           0.0200 * dsin(2 * solar_mean_anomaly) +
           0.0003 * dsin(3 * solar_mean_anomaly);
}

/* ecliptic longitude [1]
 * eoc: equation of the center value */
double slib_ecliptic_longitude(double solar_mean_anomaly, double eoc_value)
{
    return fmod(solar_mean_anomaly + eoc_value + 180 + 102.9372, 360);
}

/* solar transit [1]
 * returns a julian date */
double slib_solar_transit(double mean_solar_noon, double solar_mean_anomaly,
                          double ecliptic_longitude)
{
    return 2451545.0 + mean_solar_noon + 0.0053 * dsin(solar_mean_anomaly) -
           0.0069 * dsin(2 * ecliptic_longitude);
}

/* declination of the sun [1] */
double slib_sun_decl(double ecliptic_longitude)
{
    return dasin(dsin(ecliptic_longitude) * dsin(23.44));
}

/* the sunrise equation [1]
   latitude and sun_declination in degrees
   cos(ωo) = -tan(φ)*tan(δ)
   returns the hour angle before local noon in degrees */
double slib_sunrise_hour_angle(double latitude, double sun_declination)
{
    return dacos(-dtan(latitude) * dtan(sun_declination));
}

/* the sunrise equation with corrections [1]
   latitude and sun_declination in degrees; elevation in meters
   cos(ωo) = (sin(0.83°-2.076°*sqrt(elevation)/60°) -
   sin(φ)*sin(δ))/(cos(φ)*cos(δ)) */
double slib_corr_sunrise_hour_angle(double latitude, double sun_declination,
                                    double elevation)
{
    return dacos((dsin(0.83 - 2.076 * sqrt(elevation) / 60) -
                  dsin(latitude) * dsin(sun_declination)) /
                 (dcos(latitude) * dcos(sun_declination)));
}

/* single function version */
double slib_sf_csha(double latitude, double longitude, double elevation,
                    double *solartrans, struct tm tm)
{
    double jd = slib_tm2jd(tm);
    double jdy = slib_julian_day(jd);
    double msn = slib_mean_solar_noon(jdy, longitude);
    double sma = slib_solar_mean_anomaly(msn);
    double eoc = slib_equation_of_the_center_value(sma);
    double el = slib_ecliptic_longitude(sma, eoc);
    double sundec = slib_sun_decl(el);
    *solartrans = slib_solar_transit(msn, sma, el);
    return slib_corr_sunrise_hour_angle(latitude, sundec, elevation);
}

#include <stdio.h>
int main()
{
    time_t rawtm;
    struct tm *tm;
    double sunset, sha, st, lat = 25.0, lon = 102.7, elev = 1904, jd;
    time(&rawtm);
    tm = localtime(&rawtm);
    tm->tm_year-=3000;
    jd = slib_tm2jd(*tm);
    slib_jd2tm(jd, tm);
    printf("%4d/%02d/%02d,%02d:%02d:%02d\n%lf\n", tm->tm_year + 1900,
           tm->tm_mon + 1, tm->tm_mday, tm->tm_hour, tm->tm_min, tm->tm_sec,
           jd);
    sha = slib_sf_csha(lat, lon, elev, &st, *tm);
    sunset = st + sha / 360;
    slib_jd2tm(sunset, tm);

    return 0;
}
