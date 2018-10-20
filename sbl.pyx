from libc.stdio cimport fopen, fclose, FILE
from libc.stdlib cimport malloc, free
from libc.string cimport strcmp

cdef extern from "slib/fileopt.h":
    long fsize(FILE *)
    void splitpathS(const char *, char *, char *, char *, char *)
    long *slib_count_fl(FILE *, long *);
    long slib_fbsearch(char *, FILE *, int (*)(char *, char *));
    void slib_fqsort(FILE *, int (*)(char *, char *));

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

ctypedef int (*compar)(char *, char *)

cdef (long *, long) _wrap_count_fl(char *file):
    cdef long count
    cdef long *lst
    cdef FILE *fp = fopen(file, "rb")
    lst = slib_count_fl(fp, &count)
    return (lst, count)

def _unify_o_f(file):
    return file.encode() if isinstance(file, basestring) else file.name.encode()

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
    reslst = []
    lst, count = _wrap_count_fl(_unify_o_f(file))
    for i in range(0, count):
        reslst.append(lst[i])
    return (reslst, count)

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
