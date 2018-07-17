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

#include "slib/fileopt.h"
#include <stdio.h>
#include <stdlib.h>

static long slib_count_fl(FILE *fp, long **line_starts)
{
	int the_char;
	int have_size = 32;
	long count = -1; /* count starts at line 0 */
	*line_starts = malloc(sizeof(long) * 32); /* initial size */
	while ((the_char = fgetc(fp)) != EOF)
	{
		if (the_char == '\n')
		{
			++count;
			if (count == have_size)
				*line_starts = realloc(*line_starts, (have_size*=2));
			(*line_starts)[count] = ftell(fp) + 1;
		}
	}
	(*line_starts)[count+1] = EOF;/* EOF-terminate */
	return count;
}
#if 0
/* bsearch() for a file, returns the ftell() position of the start of the line */
int slib_fbsearch(char *key, FILE *fp, int (*compar)(char *s1, char *s2))
{
	int oldlines;
	while (1)
	{
		oldlines = lines;
		lines /= 2;
		if (oldfs == filesize)
		{
			/* already at position 0 */
			fclose(fp);
			free(pathname);
			return 0;
		}
		fseek(fp, base + filesize, SEEK_SET);
		if (fgets(line, 36, fp) == NULL)
		{
			if (ferror(fp))
				perror("is_dep_met: fgets");
			fclose(fp);
			free(pathname);
			return 0;
		}
		/* good, we found it */
		if ((cmpdiff = goodstrcmp(line, name)) == 0)
		{
			fclose(fp);
			free(pathname);
			return 1;
		}
		else if (cmpdiff < 0)
			continue;
		else /* cmpdiff > 0 */
			base = filesize;
	}
}

/* qsort() for a file, uses a non-just-in-place bubble sort */
void slib_fqsort(FILE *fp, int (*compar)(char *s1, char *s2)) {}
#endif
int main (int i, char **a)
{
	volatile int check = 1/(i-1);
	long *l;
	FILE *fp = fopen(a[1], "r");
	printf("%ld\n", slib_count_fl(fp, &l));
	for(int j = 0;l[j] != EOF; ++j)
	{
		printf("%ld\n", l[j]);
	}
	free(l);
	return 0;
}
