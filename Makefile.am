AUTOMAKE_OPTIONS=foreign subdir-objects
lib_LTLIBRARIES=libsbl.la
include_HEADERS=include/slib.h
libsbl_la_CPPFLAGS=-Iinclude
libsbl_la_SOURCES=include/slib.h include/slib/history.h src/history.c src/average.c src/calc.c src/clearstack.c src/colorprintf.c src/destorystack.c src/error.c src/eular.c src/fcopy.c src/fsize.c src/gcf.c src/getch.c src/getlen.c src/getopt.c src/initstack.c src/iofile.c src/ispn.c src/isrp.c src/itoa.c src/lcm.c src/mret.c src/mtscat.c src/mysh.c src/pop.c src/prtpn.c src/push.c src/randomnum.c src/sbl.c src/sleepS.c src/splitpathS.c
install-data-hook:
	mkdir -p $(includedir)/slib
	$(INSTALL) -m 644 include/slib/history.h $(includedir)/slib/

uninstall-hook:
	rm $(includedir)/slib/history.h
	rmdir $(includedir)/slib
