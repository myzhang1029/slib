 #
 #  The Makefile of the slib
 #
 #  Copyright (C) 2017 Zhang Maiyun
 #
 # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 #
 #  This file is part of the slib.
 #  The slib  is free software; you can redistribute it and/or modify
 #  it under the terms of the GNU Lesser General Public License as published by
 #  the Free Software Foundation; either version 3 of the License, or
 #  (at your option) any later version.
 #
 #  This program is distributed in the hope that it will be useful,
 #  but WITHOUT ANY WARRANTY; without even the implied warranty of
 #  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 #  GNU Lesser General Public License for more details.
 #
 #  You should have received a copy of the GNU Lesser General Public License
 #  along with this program; if not, write to the Free Software
 #  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 #
 #~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

include config.mk

.PHONY: unix win install clean all tags distclean

all:$(BUILD)

unix: libsbl$(EXESUF)
win: libsbl.dll


libsbl$(EXESUF): $(FILES)
	+make -C file unix
	+make -C main unix
	+make -C math unix
	+make -C stack unix
	+make -C string unix
	$(CC) $(SOFLAGS) */*.o -o libsbl$(EXESUF)
	$(AR) rcs ./libsbl.a */*.o

libsbl.dll: $(FILES)
	+make -C file win
	+make -C main win
	+make -C math win
	+make -C stack win
	+make -C string win
	$(CC) $(SOFLAGS) */*.o -o libsbl.dll
	$(AR) rcs ./libsbl.a */*.o

install:
	install -c -d -m 755 $(PREFIX)/lib $(PREFIX)/include
	install -c -p -m 644 include/slib.h $(PREFIX)/include
	install -c -p -m 644 libsbl.a $(PREFIX)/lib
	install -c -p -m 755 libsbl$(EXESUF) $(PREFIX)/lib;

clean:
	-$(RM) libsbl.dll libsbl.so *.o */*.o *.a -f 2>/dev/null

tags:
	ctags -R

distclean:clean
	-$(RM) config.mk

config.mk:
	@echo Please do ./configure
	@echo . .
	@echo \ \|
	@echo \\_/
	@exit 1
