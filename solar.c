/* for all lats and longs: north and east are positive and in degrees */
#include <math.h>

#define S_PI acos(-1.0)
/* trigonometry for degree */
#define dsin(deg) sin(slib_deg2rad(deg))
#define dcos(deg) cos(slib_deg2rad(deg))
#define dtan(deg) tan(slib_deg2rad(deg))
#define dasin(arg) slib_rad2deg(asin(arg))
#define dacos(arg) slib_rad2deg(acos(arg))
#define datan(arg) slib_rad2deg(atan(arg))
/* leap year */
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
/* convert hour angle to hour difference */
double slib_hour_angle_to_hour_diff(double hour_angle)
{
    return hour_angle / 15.0;
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

/* the sunrise equation
   latitude and sun_declination in degrees
   cos(ωo) = -tan(φ)*tan(δ)
   returns the hour angle before local noon in degrees */
double slib_sunrise_hour_angle(double latitude, double sun_declination)
{
    return dacos(-dtan(latitude) * dtan(sun_declination));
}

/* the sunrise equation with corrections
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

int main()
{
    double h, m, s;
    slib_h2hms(slib_local_time(102.690873, 12, 8), &h, &m, &s);
    printf("%lf:%lf:%lf\n", h, m, s);
    printf("%lf\n", slib_sun_decl_by_date(slib_d2dn(2018, 8, 30)));
    printf("%lf\n", slib_hour_angle_to_hour_diff(slib_corr_sunrise_hour_angle(
                        25.057672,
                        slib_sun_decl_by_date(slib_d2dn(2018, 8, 30)), 1904)));
    return 0;
}
