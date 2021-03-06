/*
 *  getch.c - getch function of the slib
 *
 *  Copyright (C) 2017 Zhang Maiyun
 *
 *  This file is part of the slib.
 *  The slib is free software; you can redistribute it and/or modify
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
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "slib.h"

#if !defined(_WIN32) && defined(HAVE_FCNTL_H) && defined(HAVE_TERMIOS_H) &&    \
    defined(HAVE_UNISTD_H)
#include <assert.h>
#include <fcntl.h>
#include <memory.h>
#include <termios.h>
#include <unistd.h>

OPT int getch(void)
{
    int c = 0;
    struct termios org_opts, new_opts;
    int res = 0;

    res = tcgetattr(STDIN_FILENO, &org_opts);
    assert(res == 0);

    memcpy(&new_opts, &org_opts, sizeof(new_opts));
    new_opts.c_lflag &=
        ~(ICANON | ECHO | ECHOE | ECHOK | ECHONL | ECHOPRT | ECHOKE | ICRNL);
    tcsetattr(STDIN_FILENO, TCSANOW, &new_opts);
    c = getchar();
    res = tcsetattr(STDIN_FILENO, TCSANOW, &org_opts);
    assert(res == 0);
    return c;
}

OPT int kbhit(void)
{
    struct termios oldt, newt;
    int ch;
    int oldf;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);
    if (ch != EOF)
    {
        ungetc(ch, stdin);
        return 1;
    }
    return 0;
}
#else
/* to silence: warning: ISO C requires a translation unit to contain at least
 * one declaration [-Wempty-translation-unit] */
typedef int dummy;
#endif
