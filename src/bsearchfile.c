/*
 *  bsearchfile.c - File searching and sorting by lines
 *
 *  Copyright (C) 2018-2020 Zhang Maiyun
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "slib/fileopt.h"

/* Similar to POSIX getdelim, but returns like fgets while not including the
 * trailing DELIM */
static char *gets_delim(char *line, size_t n, int delim, FILE *file)
{
    int ch;
    char *saveptr = line;
    for (; n > 0; --n)
    {
        if ((ch = fgetc(file)) == delim || feof(file))
        {
            *line = 0;
            return saveptr;
        }
        *line++ = ch;
    }
    *--line = 0;
    return saveptr;
}

/* count repeats in file, returns the ftell() position of delim before the line,
 * except for the first one which returns 0, free() result please */
OPT long *slib_count_repeats(FILE *file, long *pcount, int delim)
{
    int ch;
    long count = 0;
    /* list of the position of the char after delim */
    long *line_starts = (long *)malloc(sizeof(long) * 32);
    long *reallocmem;
    long have_size = 32;
    if (line_starts == NULL)
    {
        *pcount = 0;
        perror("slib_count_fl: malloc failed");
        return NULL;
    }
    if (file == NULL) /* EINVAL */
    {
        *pcount = 0;
        free(line_starts);
        return NULL;
    }
    rewind(file);
    line_starts[0] = 0; /* the first line */
    while ((ch = fgetc(file)) != EOF)
    {
        if (ch == delim)
        {
            if (count + 1 >= have_size)
            {
                reallocmem = (long *)realloc(line_starts,
                                             sizeof(long) * (have_size *= 2));
                if (reallocmem != NULL)
                    line_starts = reallocmem;
                else
                {
                    free(line_starts);
                    *pcount = 0;
                    perror("slib_count_fl: realloc failed");
                    return NULL;
                }
            }
            line_starts[++count] = ftell(
                file); /* first run: line_starts[1] since line_starts[0] is 0 */
        }
    }
    *pcount = count;
    /* resize to minimal, throw away the last one since no line is there */
    /* don't think this will fail, but still handle it */
    reallocmem = (long *)realloc(line_starts, sizeof(long) * count);
    if (reallocmem == NULL && count != 0)
        free(line_starts);
    return reallocmem;
    /* count - 1 is the maximum index of line_starts */
}

/* count lines in file, returns the ftell() position of '\n' before the line,
 * except for the first line which returns 0, free() result please */
OPT long *slib_count_fl(FILE *file, long *pcount)
{
    return slib_count_repeats(file, pcount, '\n');
}

/* bsearch() for a file, returns the ftell() position of '\n' before the line,
 * except for the first line which returns 0, that is, if you fseek() to the
 * result and fgets() a line, it will be identical to KEY.
 * If a line matching the KEY isn't found, returns -1;
 * If memory operations failed, returns -2.
 */
OPT long slib_fbsearch(const char *key, FILE *fp,
                       int (*compar)(const char *s1, const char *s2))
{
    return slib_fbsearchdelim(key, fp, '\n', compar);
}
OPT long slib_fbsearchdelim(const char *key, FILE *fp, int delim,
                            int (*compar)(const char *s1, const char *s2))
{
    int r;
    /* Here we call a section of data seperated by DELIM a line */
    long low, mid, high, *linelist, tmp;
    char *cmp = (char *)malloc(strlen(key) + 1); /* don't think a line longer
                                             than key will be the same as key */
    if (cmp == NULL)
    {
        perror("slib_fbsearch: malloc failed");
        return -2;
    }
    if ((linelist = slib_count_repeats(fp, &high, delim)) == NULL)
    {
        free(cmp);
        return -2;
    }
    low = 0;
    while (low < high)
    {
        mid = low + ((high - low) >> 1);
        fseek(fp, linelist[mid], SEEK_SET);
        /* Either EOF or an error */
        if (gets_delim(cmp, strlen(key) + 1, delim, fp) == NULL)
        {
            free(cmp);
            free(linelist);
            return -2;
        }
        r = (*compar)(key, cmp);
        /* Learning notes:
         * here:
         * r < 0 => key - cmp < 0 => key < cmp
         * r > 0 => key - cmp > 0 => key > cmp
         *
         * math:
         * y(address): low    r<0   mid   r>0   high
         *             ------------------------------> y = compar(x)
         * x(string):         key   cmp   key
         * since the start of the file has the lowest address,
         * the string that has the highest y goes to the end.
         */
        if (r > 0)
        {
            low = mid + 1;
        }
        else if (r < 0)
        {
            high = mid;
        }
        else /* r == 0 */
        {
            free(cmp);
            tmp = linelist[mid];
            free(linelist);
            return tmp;
        }
    }
    free(cmp);
    free(linelist);
    return -1; /* not found */
}

/* qsort() for a file, FP and FP_OUT should be binary streams, since only then
 * will ftell() positions be meaningful.
 * Uses injection sort with a linked list */
OPT void slib_fqsort(FILE *fp, FILE *fp_out,
                     int (*compar)(const char *s1, const char *s2))
{
    slib_fqsortdelim(fp, fp_out, '\n', compar);
}
OPT void slib_fqsortdelim(FILE *fp, FILE *fp_out, int delim,
                          int (*compar)(const char *s1, const char *s2))
{
    long nline, *linelist;
    long iter;
    char *to_be_sorted, *cmp;
    size_t largest_delta; /* The length of the longest line */

    struct line
    {
        long pos;
        struct line *next;
    } *first = NULL, *cmping = NULL;

    linelist = slib_count_fl(fp, &nline);

    largest_delta = (size_t)fsize(fp) -
                    linelist[nline - 1]; /* The length of the last line */
    /* -1: Tree-planting problem: The spaces is fewer than lines, don't run into
     * unauthorized areas */
    /* skipping the last line since it has been calculated before */
    for (iter = 0; iter < nline - 1; ++iter)
    {
        size_t delta = linelist[iter + 1] - linelist[iter]; /* Positive */
        if (delta > largest_delta)
            largest_delta = delta;
    }
    /* largest_delta here is tested to be correct, but not included in the test
     * suite */

    cmp = malloc(largest_delta); /* The longest one won't include the '\n' */
    to_be_sorted = malloc(largest_delta);

    for (iter = 0; iter < nline; ++iter)
    {
        struct line *cur = malloc(sizeof(struct line));
        cur->pos = linelist[iter];
        cur->next = NULL;
        fseek(fp, cur->pos, SEEK_SET);
        gets_delim(to_be_sorted, largest_delta, delim, fp);
        if (first == NULL)
            first = cur;
        else
        {
            long tmp;
            int r;
            /* Find an appropriate postion */
            do
            {
                if (cmping)
                    cmping = cmping->next; /* Upcoming iters */
                else
                    cmping = first; /* First iter */
                fseek(fp, cmping->pos, SEEK_SET);
                cmp = gets_delim(cmp, largest_delta, delim, fp);
                r = (*compar)(to_be_sorted, cmp);
                if (cmping->next == NULL) /* Already the last one */
                    break;
            } while (r > 0);
            /* else r <= 0, cur <= cmp */
            if (r < 0)
            {
                /* insert cur in front of cmping. see line
                 * 139 */
                /* Insert cur to the appropriate postion. *
                 * Actually, this is not inserting. Instead, the old one is
                 * replaced. Therefore, there's no need to save/write FIRST.
                 * i.e. if the loop exits without running for a second time,
                 * CMPING is still identical to FIRST. in the following code,
                 * both CMPING and FIRST will be replaced by CUR. That way,
                 * FIRST is still the lowest item
                 */
                /* Swap two poses */
                tmp = cur->pos;
                cur->pos = cmping->pos;
                cmping->pos = tmp;
                /* Now cur is cmping and vice versa. */
                /* Give out nexts */
                cur->next = cmping->next;
                cmping->next = cur;
            }
            else /* r > 0 => cmping->next == NULL */
                cmping->next = cur;
            /* Reset loop condition */
            cmping = NULL;
        }
    }
    /* sorting done, now output */
    for (iter = 0; iter < nline; ++iter)
    {
        fseek(fp, first->pos, SEEK_SET);
        gets_delim(cmp, largest_delta, delim, fp);
        fputs(cmp, fp_out);
        fputc(delim, fp_out);
        cmping = first; /* cmping is now a temporary thing */
        first = first->next;
        free(cmping);
    }
    free(cmp);
    free(to_be_sorted);
    free(linelist);
}
