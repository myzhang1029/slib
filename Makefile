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
include objs.mk

err:
	@echo 'Please do make PLATFORM:'
	@echo '	win:windows, MinGW'
	@echo '	unix:UNIX, GNU/Linux, BSD'
	@exit 1


unix:libsbl.so
win:libsbl.dll


libsbl.so:$(OBJ-UNIX)
	$(CC) $(CFLAGS) $(OBJS) -o libsbl.so
	
libsbl.dll:$(OBJ-WIN)
	$(CC) $(CFLAGS) $(OBJS) -o libsbl.dll


.PHONY:clean err
clean:
	$(RM) *.o *.a -r
