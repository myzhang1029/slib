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

/* count lines in file, returns the ftell() position of the start of each line, free() result please */
long *slib_count_fl (FILE *file, long *pcount) 
{
	int ch;
	long count = 0;
	long *line_starts = malloc(sizeof(int) * 32);/* list of the position of the char after the '\n' */
	size_t have_size = 32;
	if(file == NULL)
	{
		return NULL;
	}
	line_starts[0] = 0;/* the first line */
	while((ch = fgetc(file)) != EOF)
	{
		if (ch == '\n')
		{
			if (count + 2 == have_size)
				line_starts = realloc(line_starts, (have_size += 32));
			line_starts[++count] = ftell(file);/* first run: line_starts[1] */
		}
	}
	*pcount = count;
	line_starts = realloc(line_starts, count - 1);/* resize to minimal, throw away the last one since no line is there */
	return line_starts;/* count - 1 is the maximum index of line_starts */
}

#if 0
/* bsearch() for a file, returns the ftell() position of the start of the line */
int slib_fbsearch(char *key, FILE *fp, int (*compar)(char *s1, char *s2))
{
	long oldlines, totallines, *linelist;
	linelist = slib_count_fl(fp, &totallines);
	while (1)
	{
		oldlines = totallines;
		totallines /= 2;
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
int main(void)
{
	long count, *list = slib_count_fl(stdin, &count);
	printf("%ld\n", count);
	for(long i = 0; i < count; ++i)
		printf("%ld\n", list[i]);
	return 0;
}
