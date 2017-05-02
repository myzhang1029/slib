 #
 #  The Make configure file of the slib
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

CFLAGS-WIN=-O2 -DPLAT=1 -Wall -c -I../include -lm 
CFLAGS-UNIX=-O2 -DPLAT=0 -Wall -c -I../include -lm
CFLAGS=-Os -shared -fPIC

CC=gcc
RM=rm

FILES=file/fcopy.c file/fsize.c file/iofile.c \
      main/colorprintf.c main/error.c main/getch.c \
      main/itoa.c main/mysh.c main/randomnum.c\
      main/sbl.c main/mret.c \
      math/average.c math/calc.c math/eular.c math/gcf.c math/ispn.c\
      math/isrp.c math/lcm.c math/prtpn.c \
      stack/clearstack.c stack/destorystack.c stack/getlen.c \
      stack/initstack.c stack/pop.c stack/push.c \
      string/module.c string/mtscat.c

define mkelem
$(CC) $(CFLAGS) $@ -o $^
endef

