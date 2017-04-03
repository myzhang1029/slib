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

include Make.cfg
err:;@echo -e 'Please do make PLATFORM:\n\twin:windows, MinGW\n\tunix:UNIX, GNU/Linux, BSD'

unix:slib.so
win:slib.dll

slib.so:
	$(CC) $(CFLAGS-UNIX) $(FILES) -o slib.so
	
slib.dll:
	$(CC) $(CFLAGS-WIN) $(FILES) -o slib.dll

.PHONY:clean unix win
clean:
	$(RM) *.o *.a -r
