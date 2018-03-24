AUTOMAKE_OPTIONS=foreign subdir-objects
lib_LTLIBRARIES=libsbl.la
include_HEADERS=include/slib.h
libsbl_la_CPPFLAGS=-Iinclude
libsbl_la_SOURCES=src/average.c src/calc.c src/clearstack.c \
src/colorprintf.c src/destorystack.c src/error.c src/eular.c \
src/fnmatch.c src/fsize.c src/gcf.c src/getch.c src/getlen.c \
src/getopt.c src/history.c src/initstack.c src/iofile.c \
src/ispn.c src/isrp.c src/itoa.c src/lcm.c src/mret.c \
src/mtscat.c src/pop.c src/prtpn.c src/push.c src/randomnum.c \
src/regex.c src/sleepS.c src/splitpathS.c include/slib/fnmatch.h \
include/slib/general.h include/slib/getopt.h include/slib/history.h \
include/slib/itoa.h include/slib/math.h include/slib/regex.h include/slib.h 
distclean-local:
	rm -f src/Makefile

install-data-hook:
	mkdir -p $(includedir)/slib
	$(INSTALL) -m 644 include/slib/*.h $(includedir)/slib/

uninstall-hook:
	rm -rf $(includedir)/slib


