/*
 *  getch.c - getch function of the slib
 *
 *  Copyright (C) 2017 Zhang Maiyun
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 *  This file is part of slib.
 *  slib  is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation; either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
#include "slib.h"

#if ! PLAT
OPT int getch(void) 
{
        int c=0;
        struct termios org_opts, new_opts;
        int res=0;

        res=tcgetattr(STDIN_FILENO, &org_opts);
        assert(res==0);
    
        memcpy(&new_opts, &org_opts, sizeof(new_opts));
        new_opts.c_lflag &= ~(ICANON | ECHO | ECHOE | ECHOK | ECHONL | ECHOPRT | ECHOKE | ICRNL);
        tcsetattr(STDIN_FILENO, TCSANOW, &new_opts);
        c=getchar();

        res=tcsetattr(STDIN_FILENO, TCSANOW, &org_opts);assert(res==0);
        return c;
}
#endif

