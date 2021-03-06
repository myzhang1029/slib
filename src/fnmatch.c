/* fnmatch.c - Match filenames against pattern
 * Copyright (C) 1991, 1992, 1993, 1996 Free Software Foundation, Inc.
 * Copyright (C) 2017 Zhang Maiyun.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public License as
 * published by the Free Software Foundation; either version 3 of the
 * License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; see the file COPYING.  If
 * not, see <http://www.gnu.org/licenses/>.
 */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include <ctype.h>

#include "slib/fnmatch.h"

/* Match STRING against the filename pattern PATTERN, returning zero if
   it matches, nonzero if not.  */
OPT int fnmatchGS(const char *pattern, const char *string, int flags)
{
    S_REGISTER const char *p = pattern, *n = string;
    S_REGISTER char c;

    /* Note that this evaluates C many times.  */
#if defined(STDC_HEADERS) || !defined(isascii)
#define FOLD(c) ((flags & FNM_CASEFOLD) && isupper(c) ? tolower(c) : (c))
#else
#define FOLD(c)                                                                \
    ((flags & FNM_CASEFOLD) && (isascii(c) && isupper(c)) ? tolower(c) : (c))
#endif

    while ((c = *p++) != '\0')
    {
        c = FOLD(c);

        switch (c)
        {
            case '?':
                if (*n == '\0')
                    return FNM_NOMATCH;
                else if ((flags & FNM_FILE_NAME) && *n == '/')
                    return FNM_NOMATCH;
                else if ((flags & FNM_PERIOD) && *n == '.' &&
                         (n == string ||
                          ((flags & FNM_FILE_NAME) && n[-1] == '/')))
                    return FNM_NOMATCH;
                break;

            case '\\':
                if (!(flags & FNM_NOESCAPE))
                {
                    c = *p++;
                    if (c == '\0')
                        /* Trailing \ loses.  */
                        return FNM_NOMATCH;
                    c = FOLD(c);
                }
                if (FOLD(*n) != c)
                    return FNM_NOMATCH;
                break;

            case '*':
                if ((flags & FNM_PERIOD) && *n == '.' &&
                    (n == string || ((flags & FNM_FILE_NAME) && n[-1] == '/')))
                    return FNM_NOMATCH;

                for (c = *p++; c == '?' || c == '*'; c = *p++)
                {
                    if ((flags & FNM_FILE_NAME) && *n == '/')
                        /* A slash does not match a wildcard under
                         * FNM_FILE_NAME.  */
                        return FNM_NOMATCH;
                    else if (c == '?')
                    {
                        /* A ? needs to match one character.  */
                        if (*n == '\0')
                            /* There isn't another character; no match.  */
                            return FNM_NOMATCH;
                        else
                            /* One character of the string is consumed in
                               matching this ? wildcard, so *??? won't match if
                               there are less than three characters.  */
                            ++n;
                    }
                }

                if (c == '\0')
                    return 0;

                {
                    char c1 = (!(flags & FNM_NOESCAPE) && c == '\\') ? *p : c;

                    c1 = FOLD(c1);
                    for (--p; *n != '\0'; ++n)
                        if ((c == '[' || FOLD(*n) == c1) &&
                            fnmatchGS(p, n, flags & ~FNM_PERIOD) == 0)
                            return 0;
                    return FNM_NOMATCH;
                }

            case '[':
            {
                /* Nonzero if the sense of the character class is inverted.  */
                S_REGISTER int isnot;

                if (*n == '\0')
                    return FNM_NOMATCH;

                if ((flags & FNM_PERIOD) && *n == '.' &&
                    (n == string || ((flags & FNM_FILE_NAME) && n[-1] == '/')))
                    return FNM_NOMATCH;

                isnot = (*p == '!' || *p == '^');
                if (isnot)
                    ++p;

                c = *p++;
                for (;;)
                {
                    S_REGISTER char cstart = c, cend = c;

                    if (!(flags & FNM_NOESCAPE) && c == '\\')
                    {
                        if (*p == '\0')
                            return FNM_NOMATCH;
                        cstart = cend = *p++;
                    }

                    cstart = cend = FOLD(cstart);

                    if (c == '\0')
                        /* [ (unterminated) loses.  */
                        return FNM_NOMATCH;

                    c = *p++;
                    c = FOLD(c);

                    if ((flags & FNM_FILE_NAME) && c == '/')
                        /* [/] can never match.  */
                        return FNM_NOMATCH;

                    if (c == '-' && *p != ']')
                    {
                        cend = *p++;
                        if (!(flags & FNM_NOESCAPE) && cend == '\\')
                            cend = *p++;
                        if (cend == '\0')
                            return FNM_NOMATCH;
                        cend = FOLD(cend);

                        c = *p++;
                    }

                    if (FOLD(*n) >= cstart && FOLD(*n) <= cend)
                        goto matched;

                    if (c == ']')
                        break;
                }
                if (!isnot)
                    return FNM_NOMATCH;
                break;

            matched:;
                /* Skip the rest of the [...] that already matched.  */
                while (c != ']')
                {
                    if (c == '\0')
                        /* [... (unterminated) loses.  */
                        return FNM_NOMATCH;

                    c = *p++;
                    if (!(flags & FNM_NOESCAPE) && c == '\\')
                    {
                        if (*p == '\0')
                            return FNM_NOMATCH;
                        /* XXX 1003.2d11 is unclear if this is right.  */
                        ++p;
                    }
                }
                if (isnot)
                    return FNM_NOMATCH;
            }
            break;

            default:
                if (c != FOLD(*n))
                    return FNM_NOMATCH;
        }

        ++n;
    }

    if (*n == '\0')
        return 0;

    if ((flags & FNM_LEADING_DIR) && *n == '/')
        /* The FNM_LEADING_DIR flag says that "foo*" matches "foobar/frobozz".
         */
        return 0;

    return FNM_NOMATCH;
}
#undef FOLD
