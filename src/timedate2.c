/*
 *  timedate2.c - functions about time, date and calendars under CC-BY-SA 3.0
 *
 *  The algorithms are from the Wikipedia page
 * https://en.wikipedia.org/wiki/Julian_day
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * This work is licensed under the Creative Commons Attribution-ShareAlike 3.0
 * Unported License. To view a copy of this license, visit
 * http://creativecommons.org/licenses/by-sa/3.0/ or send a letter to Creative
 * Commons, PO Box 1866, Mountain View, CA 94042, USA.
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
#include <time.h>

#include "slib/timedate.h"

/* convert tm structure to Julian Date, note that you should always use a
 * UTC time [1] */
OPT double slib_tm2jd(struct tm *tm)
{
    int y = tm->tm_year + 1900, m = tm->tm_mon + 1, d = tm->tm_mday;
    double jdn = (1461 * (y + 4800 + (m - 14) / 12)) / 4 +
                 (367 * (m - 2 - 12 * ((m - 14) / 12))) / 12 -
                 (3 * ((y + 4900 + (m - 14) / 12) / 100)) / 4 + d - 32075;
    if (y < -4713 || (y == -4713 && m < 11) ||
        (y == -4713 && m == 11 &&
         d <= 23)) /* The algorithm is invalid here TODO */
        return -1;
    /* note the result of slib_hms2h might be negative */
    return jdn + (tm->tm_hour - 12.0 /* midnight2noon */) / 24.0 +
           tm->tm_min / 1440.0 + tm->tm_sec / 86400.0;
}

/* convert Julian Date back to tm structure [1] */
OPT void slib_jd2tm(double jd, struct tm *tm)
{
    long jdn = (long)jd;
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
