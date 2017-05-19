/*
 *  getopt.c - Getopt for both MS and unix, supports unicode
 *
 *. Copyright (C) 1987-2004 Free Software Foundation, Inc.
 *  Copyright (C) 2011-2015 Ludvik Jerabek
 *  Copyright (C) 2017 Zhang Maiyun
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
#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include "getoptS.h"

#ifdef __cplusplus
	#define _GETOPT_THROW throw()
#else
	#define _GETOPT_THROW
#endif

int optindGS = 1;
int opterrGS = 1;
int optoptGS = '?';
enum ENUM_ORDERING { REQUIRE_ORDER, PERMUTE, RETURN_IN_ORDER };


static struct _getopt_data
{
	int optindGS;
	int opterrGS;
	int optoptGS;
	char *optargGS;
	int __initialized;
	char *__nextchar;
	enum ENUM_ORDERING __ordering;
	int __posixly_correct;
	int __first_nonopt;
	int __last_nonopt;
} getopt_data;
char *optargGS;

static void exchange(char **argv, struct _getopt_data *d)
{
	int bottom = d->__first_nonopt;
	int middle = d->__last_nonopt;
	int top = d->optindGS;
	char *tem;
	while (top > middle && middle > bottom)
	{
		if (top - middle > middle - bottom)
		{
			int len = middle - bottom;
			register int i;
			for (i = 0; i < len; i++)
			{
				tem = argv[bottom + i];
				argv[bottom + i] = argv[top - (middle - bottom) + i];
				argv[top - (middle - bottom) + i] = tem;
			}
			top -= len;
		}
		else
		{
			int len = top - middle;
			register int i;
			for (i = 0; i < len; i++)
			{
				tem = argv[bottom + i];
				argv[bottom + i] = argv[middle + i];
				argv[middle + i] = tem;
			}
			bottom += len;
		}
	}
	d->__first_nonopt += (d->optindGS - d->__last_nonopt);
	d->__last_nonopt = d->optindGS;
}
static const char *_getopt_initialize(const char *optstring, struct _getopt_data *d, int posixly_correct)
{
	d->__first_nonopt = d->__last_nonopt = d->optindGS;
	d->__nextchar = NULL;
	d->__posixly_correct = posixly_correct | !!getenv("POSIXLY_CORRECT");
	if (optstring[0] == '-')
	{
		d->__ordering = RETURN_IN_ORDER;
		++optstring;
	}
	else if (optstring[0] == '+')
	{
		d->__ordering = REQUIRE_ORDER;
		++optstring;
	}
	else if (d->__posixly_correct)
		d->__ordering = REQUIRE_ORDER;
	else
		d->__ordering = PERMUTE;
	return optstring;
}
static int _getopt_internal_r (int argc, char *const *argv, const char *optstring, const struct optionGS *longopts, int *longind, int long_only, struct _getopt_data *d, int posixly_correct)
{
	int print_errors = d->opterrGS;
	if (argc < 1)
		return -1;
	d->optargGS = NULL;
	if (d->optindGS == 0 || !d->__initialized)
	{
		if (d->optindGS == 0)
			d->optindGS = 1;
		optstring = _getopt_initialize (optstring, d, posixly_correct);
		d->__initialized = 1;
	}
	else if (optstring[0] == '-' || optstring[0] == '+')
		optstring++;
	if (optstring[0] == ':')
		print_errors = 0;
	if (d->__nextchar == NULL || *d->__nextchar == '\0')
	{
		if (d->__last_nonopt > d->optindGS)
			d->__last_nonopt = d->optindGS;
		if (d->__first_nonopt > d->optindGS)
			d->__first_nonopt = d->optindGS;
		if (d->__ordering == PERMUTE)
		{
			if (d->__first_nonopt != d->__last_nonopt && d->__last_nonopt != d->optindGS)
				exchange ((char **) argv, d);
			else if (d->__last_nonopt != d->optindGS)
				d->__first_nonopt = d->optindGS;
			while (d->optindGS < argc && (argv[d->optindGS][0] != '-' || argv[d->optindGS][1] == '\0'))
				d->optindGS++;
			d->__last_nonopt = d->optindGS;
		}
		if (d->optindGS != argc && !strcmp(argv[d->optindGS], "--"))
		{
			d->optindGS++;
			if (d->__first_nonopt != d->__last_nonopt && d->__last_nonopt != d->optindGS)
				exchange((char **) argv, d);
			else if (d->__first_nonopt == d->__last_nonopt)
				d->__first_nonopt = d->optindGS;
			d->__last_nonopt = argc;
			d->optindGS = argc;
		}
		if (d->optindGS == argc)
		{
			if (d->__first_nonopt != d->__last_nonopt)
				d->optindGS = d->__first_nonopt;
			return -1;
		}
		if ((argv[d->optindGS][0] != '-' || argv[d->optindGS][1] == '\0'))
		{
			if (d->__ordering == REQUIRE_ORDER)
				return -1;
			d->optargGS = argv[d->optindGS++];
			return 1;
		}
		d->__nextchar = (argv[d->optindGS] + 1 + (longopts != NULL && argv[d->optindGS][1] == '-'));
	}
	if (longopts != NULL && (argv[d->optindGS][1] == '-' || (long_only && (argv[d->optindGS][2] || !strchr(optstring, argv[d->optindGS][1])))))
	{
		char *nameend;
		unsigned int namelen;
		const struct optionGS *p;
		const struct optionGS *pfound = NULL;
		struct option_list
		{
			const struct optionGS *p;
			struct option_list *next;
		} *ambig_list = NULL;
		int exact = 0;
		int indfound = -1;
		int option_index;
		for (nameend = d->__nextchar; *nameend && *nameend != '='; nameend++);
		namelen = (unsigned int)(nameend - d->__nextchar);
		for (p = longopts, option_index = 0; p->name; p++, option_index++)
			if (!strncmp(p->name, d->__nextchar, namelen))
			{
				if (namelen == (unsigned int)strlen(p->name))
				{
					pfound = p;
					indfound = option_index;
					exact = 1;
					break;
				}
				else if (pfound == NULL)
				{
					pfound = p;
					indfound = option_index;
				}
				else if (long_only || pfound->has_arg != p->has_arg || pfound->flag != p->flag || pfound->val != p->val)
				{
					struct option_list *newp = (struct option_list*)alloca(sizeof(*newp));
					newp->p = p;
					newp->next = ambig_list;
					ambig_list = newp;
				}
			}
			if (ambig_list != NULL && !exact)
			{
				if (print_errors)
				{
					struct option_list first;
					first.p = pfound;
					first.next = ambig_list;
					ambig_list = &first;
					fprintf (stderr, "%s: option '%s' is ambiguous; possibilities:", argv[0], argv[d->optindGS]);
					do
					{
						fprintf (stderr, " '--%s'", ambig_list->p->name);
						ambig_list = ambig_list->next;
					}
					while (ambig_list != NULL);
					fputc ('\n', stderr);
				}
				d->__nextchar += strlen(d->__nextchar);
				d->optindGS++;
				d->optoptGS = 0;
				return '?';
			}
			if (pfound != NULL)
			{
				option_index = indfound;
				d->optindGS++;
				if (*nameend)
				{
					if (pfound->has_arg)
						d->optargGS = nameend + 1;
					else
					{
						if (print_errors)
						{
							if (argv[d->optindGS - 1][1] == '-')
							{
								fprintf(stderr, "%s: option '--%s' doesn't allow an argument\n",argv[0], pfound->name);
							}
							else
							{
								fprintf(stderr, "%s: option '%c%s' doesn't allow an argument\n",argv[0], argv[d->optindGS - 1][0],pfound->name);
							}
						}
						d->__nextchar += strlen(d->__nextchar);
						d->optoptGS = pfound->val;
						return '?';
					}
				}
				else if (pfound->has_arg == 1)
				{
					if (d->optindGS < argc)
						d->optargGS = argv[d->optindGS++];
					else
					{
						if (print_errors)
						{
							fprintf(stderr,"%s: option '--%s' requires an argument\n",argv[0], pfound->name);
						}
						d->__nextchar += strlen(d->__nextchar);
						d->optoptGS = pfound->val;
						return optstring[0] == ':' ? ':' : '?';
					}
				}
				d->__nextchar += strlen(d->__nextchar);
				if (longind != NULL)
					*longind = option_index;
				if (pfound->flag)
				{
					*(pfound->flag) = pfound->val;
					return 0;
				}
				return pfound->val;
			}
			if (!long_only || argv[d->optindGS][1] == '-' || strchr(optstring, *d->__nextchar) == NULL)
			{
				if (print_errors)
				{
					if (argv[d->optindGS][1] == '-')
					{
						fprintf(stderr, "%s: unrecognized option '--%s'\n",argv[0], d->__nextchar);
					}
					else
					{
						fprintf(stderr, "%s: unrecognized option '%c%s'\n",argv[0], argv[d->optindGS][0], d->__nextchar);
					}
				}
				d->__nextchar = (char *)"";
				d->optindGS++;
				d->optoptGS = 0;
				return '?';
			}
	}
	{
		char c = *d->__nextchar++;
		char *temp = (char*)strchr(optstring, c);
		if (*d->__nextchar == '\0')
			++d->optindGS;
		if (temp == NULL || c == ':' || c == ';')
		{
			if (print_errors)
			{
				fprintf(stderr, "%s: invalid option -- '%c'\n", argv[0], c);
			}
			d->optoptGS = c;
			return '?';
		}
		if (temp[0] == 'W' && temp[1] == ';')
		{
			char *nameend;
			const struct optionGS *p;
			const struct optionGS *pfound = NULL;
			int exact = 0;
			int ambig = 0;
			int indfound = 0;
			int option_index;
			if (longopts == NULL)
				goto no_longs;
			if (*d->__nextchar != '\0')
			{
				d->optargGS = d->__nextchar;
				d->optindGS++;
			}
			else if (d->optindGS == argc)
			{
				if (print_errors)
				{
					fprintf(stderr,"%s: option requires an argument -- '%c'\n",argv[0], c);
				}
				d->optoptGS = c;
				if (optstring[0] == ':')
					c = ':';
				else
					c = '?';
				return c;
			}
			else
				d->optargGS = argv[d->optindGS++];
			for (d->__nextchar = nameend = d->optargGS; *nameend && *nameend != '='; nameend++);
			for (p = longopts, option_index = 0; p->name; p++, option_index++)
				if (!strncmp(p->name, d->__nextchar, nameend - d->__nextchar))
				{
					if ((unsigned int) (nameend - d->__nextchar) == strlen(p->name))
					{
						pfound = p;
						indfound = option_index;
						exact = 1;
						break;
					}
					else if (pfound == NULL)
					{
						pfound = p;
						indfound = option_index;
					}
					else if (long_only || pfound->has_arg != p->has_arg || pfound->flag != p->flag || pfound->val != p->val)
						ambig = 1;
				}
				if (ambig && !exact)
				{
					if (print_errors)
					{
						fprintf(stderr, "%s: option '-W %s' is ambiguous\n",argv[0], d->optargGS);
					}
					d->__nextchar += strlen(d->__nextchar);
					d->optindGS++;
					return '?';
				}
				if (pfound != NULL)
				{
					option_index = indfound;
					if (*nameend)
					{
						if (pfound->has_arg)
							d->optargGS = nameend + 1;
						else
						{
							if (print_errors)
							{
								fprintf(stderr, "%s: option '-W %s' doesn't allow an argument\n",argv[0], pfound->name);
							}
							d->__nextchar += strlen(d->__nextchar);
							return '?';
						}
					}
					else if (pfound->has_arg == 1)
					{
						if (d->optindGS < argc)
							d->optargGS = argv[d->optindGS++];
						else
						{
							if (print_errors)
							{
								fprintf(stderr, "%s: option '-W %s' requires an argument\n",argv[0], pfound->name);
							}
							d->__nextchar += strlen(d->__nextchar);
							return optstring[0] == ':' ? ':' : '?';
						}
					}
					else
						d->optargGS = NULL;
					d->__nextchar += strlen(d->__nextchar);
					if (longind != NULL)
						*longind = option_index;
					if (pfound->flag)
					{
						*(pfound->flag) = pfound->val;
						return 0;
					}
					return pfound->val;
				}
no_longs:
				d->__nextchar = NULL;
				return 'W';
		}
		if (temp[1] == ':')
		{
			if (temp[2] == ':')
			{
				if (*d->__nextchar != '\0')
				{
					d->optargGS = d->__nextchar;
					d->optindGS++;
				}
				else
					d->optargGS = NULL;
				d->__nextchar = NULL;
			}
			else
			{
				if (*d->__nextchar != '\0')
				{
					d->optargGS = d->__nextchar;
					d->optindGS++;
				}
				else if (d->optindGS == argc)
				{
					if (print_errors)
					{
						fprintf(stderr,"%s: option requires an argument -- '%c'\n",argv[0], c);
					}
					d->optoptGS = c;
					if (optstring[0] == ':')
						c = ':';
					else
						c = '?';
				}
				else
					d->optargGS = argv[d->optindGS++];
				d->__nextchar = NULL;
			}
		}
		return c;
	}
}
int _getopt_internal (int argc, char *const *argv, const char *optstring, const struct optionGS *longopts, int *longind, int long_only, int posixly_correct)
{
	int result;
	getopt_data.optindGS = optindGS;
	getopt_data.opterrGS = opterrGS;
	result = _getopt_internal_r (argc, argv, optstring, longopts,longind, long_only, &getopt_data,posixly_correct);
	optindGS = getopt_data.optindGS;
	optargGS = getopt_data.optargGS;
	optoptGS = getopt_data.optoptGS;
	return result;
}
int getopt (int argc, char *const *argv, const char *optstring) _GETOPT_THROW
{
	return _getopt_internal (argc, argv, optstring, (const struct optionGS *) 0, (int *) 0, 0, 0);
}
int getopt_long (int argc, char *const *argv, const char *options, const struct optionGS *long_options, int *opt_index) _GETOPT_THROW
{
	return _getopt_internal (argc, argv, options, long_options, opt_index, 0, 0);
}
int getopt_long_only (int argc, char *const *argv, const char *options, const struct optionGS *long_options, int *opt_index) _GETOPT_THROW
{
	return _getopt_internal (argc, argv, options, long_options, opt_index, 1, 0);
}
int _getopt_long_r (int argc, char *const *argv, const char *options, const struct optionGS *long_options, int *opt_index, struct _getopt_data *d)
{
	return _getopt_internal_r (argc, argv, options, long_options, opt_index,0, d, 0);
}
int _getopt_long_only_r (int argc, char *const *argv, const char *options, const struct optionGS *long_options, int *opt_index, struct _getopt_data *d)
{
	return _getopt_internal_r (argc, argv, options, long_options, opt_index, 1, d, 0);
}

