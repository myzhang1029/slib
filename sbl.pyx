from libc.stdio cimport fopen, fclose, FILE
from libc.stdlib cimport malloc, free
from libc.string cimport strcmp
from libc.time cimport tm
from cython.operator cimport dereference as deref
from time import struct_time
import pkg_resources, sys

__version__ = pkg_resources.require("sbl")[0].version

cdef extern from "time.h":
    cdef struct tm:
        int tm_sec
        int tm_min
        int tm_hour
        int tm_mday
        int tm_mon
        int tm_year
        int tm_wday
        int tm_yday
        int tm_isdst

cdef extern from "slib/astro.h":
    double slib_rad2deg(double);
    double slib_deg2rad(double);
    double slib_sun_decl_by_date(int);
    double slib_sf_csha(double, double, double, double *, tm *);
    void slib_sf_sunrise(double, double, double, double, tm *, tm *, tm *);
    double slib_julian_day(double);
    double slib_mean_solar_noon(double, double);
    double slib_solar_mean_anomaly(double);
    double slib_equation_of_the_center_value(double);
    double slib_ecliptic_longitude(double, double);
    double slib_solar_transit(double, double, double);
    double slib_sun_decl(double);
    double slib_sunrise_hour_angle(double, double);
    double slib_corr_sunrise_hour_angle(double, double, double);

cdef extern from "slib/fileopt.h":
    long fsize(FILE *)
    void splitpathS(const char *, char *, char *, char *, char *)
    long *slib_count_fl(FILE *, long *);
    long slib_fbsearch(char *, FILE *, int (*)(char *, char *));
    void slib_fqsort(FILE *, int (*)(char *, char *));

cdef extern from "slib/general.h":
    cdef int SBLLIB_VERSION
    cdef int SBLLIB_MINOR
    cdef int SBLLIB_PATCHLEVEL

cdef extern from "slib/math.h":
    void slib_prtpn(unsigned long, unsigned long)
    int slib_ispn(unsigned long)
    int slib_isrp(unsigned, unsigned)
    double slib_average(unsigned int, ...)
    unsigned long slib_gcf(unsigned long, unsigned long)
    unsigned long slib_lcm(unsigned long, unsigned long)
    int slib_eular(unsigned)
    unsigned long slib_factorial(unsigned long)
    unsigned long slib_combi(unsigned long, unsigned long)
    unsigned long slib_permu(unsigned long, unsigned long)

cdef extern from "slib/timedate.h":
    void slib_h2hms(double, double *, double *, double *);
    double slib_hms2h(double, double, double);
    int slib_d2dn(int, int, int);
    double slib_true_time_diff(double);
    double slib_local_time(double, double, double);
    double slib_tm2jd(tm *);
    void slib_jd2tm(double, tm *);

ctypedef int (*compar)(const char *, const char *)
        
def check_version():
    c_version = f"{SBLLIB_VERSION}.{SBLLIB_MINOR}.{SBLLIB_PATCHLEVEL}"
    if c_version != __version__:
        print("Version mismatch between C library and Python module", file=sys.stderr)
        return 1
    return 0

cdef (long *, long) _wrap_count_fl(char *file):
    cdef long count
    cdef long *lst
    cdef FILE *fp = fopen(file, "rb")
    lst = slib_count_fl(fp, &count)
    return (lst, count)

cdef _unify_o_f(file):
    return file.encode() if isinstance(file, basestring) else file.name.encode()

cdef (object) ctm2pytm(tm *ctm):
    return struct_time((
        ctm.tm_year,
        ctm.tm_mon + 1,
        ctm.tm_mday,
        ctm.tm_hour,
        ctm.tm_min,
        ctm.tm_sec,
        ctm.tm_wday,
        ctm.tm_yday,
        ctm.tm_isdst))

cdef (void) pytm2ctm(object pytm, tm *ctm):
    ctm.tm_year = pytm.tm_year
    ctm.tm_mon = pytm.tm_mon - 1
    ctm.tm_mday = pytm.tm_mday
    ctm.tm_hour = pytm.tm_hour
    ctm.tm_min = pytm.tm_min
    ctm.tm_sec = pytm.tm_sec
    ctm.tm_wday = pytm.tm_wday
    ctm.tm_yday = pytm.tm_yday
    ctm.tm_isdst = pytm.tm_isdst

def rad2deg(rad):
    return slib_rad2deg(rad)

def deg2rad(deg):
    return slib_deg2rad(deg)

def sun_decl_by_date(dn):
    return slib_sun_decl_by_date(dn)

def sf_csha(lat, lon, elev, pytm):
    cdef tm ctm
    cdef double solartrans
    cdef double hour_angle
    pytm2ctm(pytm, &ctm)
    hour_angle = slib_sf_csha(lat, lon, elev, &solartrans, &ctm)
    return (hour_angle, solartrans)

def sf_sunrise(lat, lon, elev, tz, utcnow):
    cdef tm sunrise, sunset, now
    pytm2ctm(utcnow, &now)
    slib_sf_sunrise(lat, lon, elev, tz, &now, &sunrise, &sunset)
    return (ctm2pytm(&sunrise), ctm2pytm(&sunset))

def julian_day(jdate):
    return slib_julian_day(jdate)

def mean_solar_noon(jday, lon):
    return slib_mean_solar_noon(jday, lon)

def solar_mean_anomaly(mean_snoon):
    return slib_solar_mean_anomaly(mean_snoon)

def equation_of_the_center_value(smean_anomaly):
    return slib_equation_of_the_center_value(smean_anomaly)

def ecliptic_longitude(smean_anomaly, eoc_value):
    return slib_ecliptic_longitude(smean_anomaly, eoc_value)

def solar_transit(mean_snoon, smean_anomaly, ecl_lon):
    return slib_solar_transit(mean_snoon, smean_anomaly, ecl_lon)

def sun_decl(ecl_lon):
    return slib_sun_decl(ecl_lon)

def sunrise_hour_angle(lat, sun_declination):
    return slib_sunrise_hour_angle(lat, sun_declination)

def corr_sunrise_hour_angle(lat, sun_declination, elev):
    return slib_corr_sunrise_hour_angle(lat, sun_declination, elev)

def filesize(file):
    return fsize(fopen(_unify_o_f(file), "rb"))

def splitpath(path):
    cdef char *drive = <char *> malloc(3)
    cdef char *dirname = <char *> malloc(len(path))
    cdef char *basename = <char *> malloc(len(path))
    cdef char *ext = <char *> malloc(len(path))
    cdef bytes odrv, odir, obase, oext
    splitpathS(path.encode(), drive, dirname, basename, ext)
    odrv = drive
    odir = dirname
    obase = basename
    oext = ext
    free(drive)
    free(dirname)
    free(basename)
    free(ext)
    return (odrv.decode(), odir.decode(), obase.decode(), oext.decode())

def count_fl(file):
    pylst = []
    clst, count = _wrap_count_fl(_unify_o_f(file))
    for i in range(0, count):
        pylst.append(clst[i])
    free(clst)
    return (pylst, count)

def fbsearch(key, file):
    cdef FILE *fp = fopen(_unify_o_f(file), "rb")
    return slib_fbsearch(key.encode(), fp, <compar>strcmp)

def fqsort(file):
    cdef FILE *fp = fopen(_unify_o_f(file), "rb")
    return slib_fqsort(fp, <compar>strcmp)

def prtpn(min, max):
    return slib_prtpn(min, max)

def ispn(n):
    return True if slib_ispn(n) == 1 else False

def isrp(n1, n2):
    return True if slib_isrp(n1, n2) == 1 else False

def gcf(n1, n2):
    return slib_gcf(n1, n1)

def lcm(n1, n2):
    return slib_lcm(n1, n1)

def eular(n):
    return slib_eular(n)

def factorial(n):
    return slib_factorial(n)

def combi(n, r):
    return slib_combi(n, r)

def permu(n, r):
    return slib_permu(n, r)

def h2hms(hour):
    cdef double h, m, s
    slib_h2hms(hour, &h, &m, &s)
    return (h, m, s)

def hms2h(h, m, s):
    return slib_hms2h(h, m, s)

def d2dn(y, m, d):
    return slib_d2dn(y, m, d)

def true_time_diff(lon):
    return slib_true_time_diff(lon)

def local_time(lon, hours, tz):
    return slib_local_time(lon, hours, tz)

def tm2jd(pytm):
    cdef tm ctm
    pytm2ctm(pytm, &ctm)
    return slib_tm2jd(&ctm)

def jd2tm(jd):
    cdef tm ctm
    slib_jd2tm(jd, &ctm)
    return ctm2pytm(&ctm)
