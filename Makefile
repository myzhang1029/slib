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

.PHONY:err unix win install clean all tags dist distvlean

err:
	@echo 'Please do make PLATFORM:'
	@echo '	win:windows, MinGW'
	@echo '	unix:UNIX, GNU/Linux, BSD'
	@exit 1


unix:libsbl.so
win:libsbl.dll


libsbl.so:$(FILES)
	make -C file unix
	make -C main unix
	make -C math unix
	make -C stack unix
	make -C string unix
	$(CC) $(CFLAGS) *.a -o libsbl.so
	
libsbl.dll:$(FILES)
	make -C file win
	make -C main win
	make -C math win
	make -C stack win
	make -C string win
	$(CC) $(CFLAGS) *.a -o libsbl.dll

install:
	if [ -f libsbl.so ] ; then cp include/slib.h $(PREFIX)/include & cp libsbl.so $(PREFIX)/lib;\
	elif [ -f libsbl.dll ] ; then cp include/slib.h $(PREFIX)/include & cp libsbl.dll $(PREFIX)/lib; fi
 
clean:
	-$(RM) libsbl.so *.o */*.o *.a -f 2>/dev/null

tags:
	ctags -R

all:err
	cd .
dist:
	mkdir -p ./usr/lib
	cp libsbl.so ./usr/lib
	tar zcvf libsbl-version.tar.gz usr
	rm -rf usr

distclean:
	-rm libsbl-*.tar.gz	
