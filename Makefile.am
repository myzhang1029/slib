AUTOMAKE_OPTIONS = foreign
ACLOCAL_AMFLAGS = -I m4
lib_LTLIBRARIES = libsbl.la
libsbl_la_INCLUDES = include/slib/astro.h include/slib/error.h \
					 include/slib/fileopt.h include/slib/fnmatch.h \
					 include/slib/general.h include/slib/getopt.h \
					 include/slib/itoa.h include/slib/math.h \
					 include/slib/overflow.h include/slib/stack.h \
					 include/slib/timedate.h include/slib.h
libsbl_la_SOURCES =  src/astro.c src/astro2.c src/bsearchfile.c \
					 src/colorprintf.c src/eular.c src/fnmatch.c \
					 src/fsize.c src/gcf.c src/getch.c src/getopt.c \
					 src/ispn.c src/isrp.c src/itoa.c src/lcm.c src/mret.c \
					 src/permcomb.c src/pnlst.c src/prtpn.c src/sleepS.c \
					 src/splitpathS.c src/stack.c src/timedate.c src/timedate2.c
libsbl_la_CFLAGS = -I$(top_srcdir)/include
libsbl_la_LDFLAGS = -version-info @version_info@

