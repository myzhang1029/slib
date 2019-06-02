#include "tests.h"
#include <math.h>
#include <memory.h>
#include <time.h>

#include <slib/astro.h>

int astro_main()
{
    struct tm tms, sr, ss;
    asrt_equ(slib_rad2deg(S_PI), 180, "rad2deg");
    asrt_equ(slib_deg2rad(180), S_PI, "deg2rad");
    asrt_equ(slib_sun_decl_by_date(23), -19.44156053713015, "sun_decl_by_date");
    /* Only test slib_sf_sunrise since it depends on all others */
    memset(&tms, 0, sizeof(struct tm));
    tms.tm_year = 119;
    tms.tm_mon = 1;
    tms.tm_mday = 15;
    slib_sf_sunrise(25.0, 102.0, 1900, 8, &tms, &sr, &ss);
    asrt_equ(sr.tm_hour, 7, "sunrise_hour");
    asrt_equ(sr.tm_min, 48, "sunrise_min");
    asrt_equ(sr.tm_sec, 51, "sunrise_sec");
    asrt_equ(sr.tm_year, 119, "sunrise_year");
    asrt_equ(sr.tm_mon, 1, "sunrise_mon");
    asrt_equ(sr.tm_mday, 15, "sunrise_mday");
    asrt_equ(sr.tm_yday, 45, "sunrise_yday");
    asrt_equ(sr.tm_wday, 5, "sunrise_wday");
    asrt_equ(ss.tm_hour, 19, "sunrise_hour");
    asrt_equ(ss.tm_min, 6, "sunrise_min");
    asrt_equ(ss.tm_sec, 2, "sunrise_sec");
    asrt_equ(ss.tm_year, 119, "sunrise_year");
    asrt_equ(ss.tm_mon, 1, "sunrise_mon");
    asrt_equ(ss.tm_mday, 15, "sunrise_mday");
    asrt_equ(ss.tm_yday, 45, "sunrise_yday");
    asrt_equ(ss.tm_wday, 5, "sunrise_wday");
    return 0;
}
