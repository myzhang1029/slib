/*
 *  bsearchfile.c - File searching and sorting by lines
 *
 *  Copyright (C) 2018 Zhang Maiyun
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
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
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "slib/fileopt.h"

/* count lines in file, returns the ftell() position of the start of each line, free() result please */
OPT long *slib_count_fl(FILE *file, long *pcount)
{
    int ch;
    long count = 0;
    /* list of the position of the char after the '\n' */
    long *line_starts = malloc(sizeof(long) * 32);
    long *reallocmem;
    size_t have_size = 32;
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
    line_starts[0] = 0; /* the first line */
    while ((ch = fgetc(file)) != EOF)
    {
        if (ch == '\n')
        {
            if (count + 1 >= have_size)
            {
                reallocmem = realloc(line_starts, sizeof(long) * (have_size *= 2));
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
            line_starts[++count] = ftell(file); /* first run: line_starts[1] since line_starts[0] is 0 */
        }
    }
    *pcount = count;
    /* resize to minimal, throw away the last one since no line is there */
    /* don't think this will fail, but still handle it */
    reallocmem = realloc(line_starts, sizeof(long) * count);
    if (reallocmem == NULL && count != 0)
        free(line_starts);
    return reallocmem;
    /* count - 1 is the maximum index of line_starts */
}

/* bsearch() for a file, returns the ftell() position of the start of the line */
OPT long slib_fbsearch(char *key, FILE *fp, int (*compar)(char *s1, char *s2))
{
    int r;
    long low, mid, high, *linelist, tmp;
    char *cmp = malloc(strlen(key) + 1); /* don't think a line longer than key will be the same */
    if (cmp == NULL)
    {
        perror("slib_fbsearch: malloc failed");
        return -2;
    }
    if ((linelist = slib_count_fl(fp, &high)) == NULL)
    {
        free(cmp);
        return -2;
    }
    --high;
    low = 0;
    while (low < high)
    {
        mid = low + ((high - low) >> 1);
        fseek(fp, linelist[mid], SEEK_SET);
        fgets(cmp, strlen(key) + 1, fp);
        if (cmp[strlen(cmp) - 1] == '\n')
            cmp[strlen(cmp) - 1] = 0; /* strip the \n */
        r = (*compar)(key, cmp);
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

/* qsort() for a file, uses a non-just-in-place bubble sort */
OPT void slib_fqsort(FILE *fp, int (*compar)(char *s1, char *s2)) {}
#include <assert.h>
int main(int i, char **a)
{
    assert(i == 3);
    FILE *fp = fopen(a[1], "r");
    long count, *list = slib_count_fl(fp, &count);
    printf("have %ld lines\n", count);
    for (long j = 0; j < count; ++j)
    {
        fseek(fp, list[j], SEEK_SET);
        printf("line %ld at %ld, first char is %c\n", j + 1, list[j], fgetc(fp));
    }
    free(list);
    printf("found at %ld\n", slib_fbsearch(a[2], fp, &strcmp));
    return 0;
}
