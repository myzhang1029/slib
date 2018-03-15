/* history.c -- Fully implemented standalone libhistory. */
/* histexpand.c -- history expansion. */

/* Copyright (C) 1989-2015 Free Software Foundation, Inc.
   Copyright (c) 2017 Zhang Maiyun

   This file contains the GNU History Library (History), a set of
   routines for managing the text of previously typed lines.

   History is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   History is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with History.  If not, see <http://www.gnu.org/licenses/>.
*/

#define READLINE_LIBRARY

#if defined(HAVE_CONFIG_H)
#include <config.h>
#endif

#undef malloc
#undef realloc

#include <stdio.h>

#include <stdlib.h>

#if defined(HAVE_UNISTD_H)
#ifndef _MINIX
#include <sys/types.h>
#endif
#include <unistd.h>
#endif

/* rlmbutil.h -- utility functions for multibyte characters. */

#if !defined(_RL_MBUTIL_H_)
#define _RL_MBUTIL_H_

/* stdc.h -- macros to make source compile on both ANSI C and K&R C compilers. */

#if !defined(_RL_STDC_H_)
#define _RL_STDC_H_

/* Adapted from BSD /usr/include/sys/cdefs.h. */

/* A function can be defined using prototypes and compile on both ANSI C
   and traditional C compilers with something like this:
	extern char *func PARAMS((char *, char *, int)); */

#if !defined(PARAMS)
#if defined(__STDC__) || defined(__GNUC__) || defined(__cplusplus)
#define PARAMS(protos) protos
#else
#define PARAMS(protos) ()
#endif
#endif

#ifndef __attribute__
#if __GNUC__ < 2 || (__GNUC__ == 2 && __GNUC_MINOR__ < 8)
#define __attribute__(x)
#endif
#endif

/* Moved from config.h.in because readline.h:rl_message depends on these
   defines. */
#if defined(__STDC__) && defined(HAVE_STDARG_H)
#define PREFER_STDARG
#define USE_VARARGS
#else
#if defined(HAVE_VARARGS_H)
#define PREFER_VARARGS
#define USE_VARARGS
#endif
#endif

#endif /* !_RL_STDC_H_ */
/* End rlstdc.h */

/************************************************/
/* check multibyte capability for I18N code     */
/************************************************/

/* For platforms which support the ISO C amendement 1 functionality we
   support user defined character classes.  */
/* Solaris 2.5 has a bug: <wchar.h> must be included before <wctype.h>.  */
#if defined(HAVE_WCTYPE_H) && defined(HAVE_WCHAR_H) && defined(HAVE_LOCALE_H)
#include <wchar.h>
#include <wctype.h>
#if defined(HAVE_ISWCTYPE) && defined(HAVE_ISWLOWER) && defined(HAVE_ISWUPPER) && defined(HAVE_MBSRTOWCS) &&           \
    defined(HAVE_MBRTOWC) && defined(HAVE_MBRLEN) && defined(HAVE_TOWLOWER) && defined(HAVE_TOWUPPER) &&               \
    defined(HAVE_WCHAR_T) && defined(HAVE_WCWIDTH)
/* system is supposed to support XPG5 */
#define HANDLE_MULTIBYTE 1
#endif
#endif

/* If we don't want multibyte chars even on a system that supports them, let
   the configuring user turn multibyte support off. */
#if defined(NO_MULTIBYTE_SUPPORT)
#undef HANDLE_MULTIBYTE
#endif

/* Some systems, like BeOS, have multibyte encodings but lack mbstate_t.  */
#if HANDLE_MULTIBYTE && !defined(HAVE_MBSTATE_T)
#define wcsrtombs(dest, src, len, ps) (wcsrtombs)(dest, src, len, 0)
#define mbsrtowcs(dest, src, len, ps) (mbsrtowcs)(dest, src, len, 0)
#define wcrtomb(s, wc, ps) (wcrtomb)(s, wc, 0)
#define mbrtowc(pwc, s, n, ps) (mbrtowc)(pwc, s, n, 0)
#define mbrlen(s, n, ps) (mbrlen)(s, n, 0)
#define mbstate_t int
#endif

/* Make sure MB_LEN_MAX is at least 16 on systems that claim to be able to
   handle multibyte chars (some systems define MB_LEN_MAX as 1) */
#ifdef HANDLE_MULTIBYTE
#include <limits.h>
#if defined(MB_LEN_MAX) && (MB_LEN_MAX < 16)
#undef MB_LEN_MAX
#endif
#if !defined(MB_LEN_MAX)
#define MB_LEN_MAX 16
#endif
#endif

/************************************************/
/* end of multibyte capability checks for I18N  */
/************************************************/

/*
 * Flags for _rl_find_prev_mbchar and _rl_find_next_mbchar:
 *
 * MB_FIND_ANY		find any multibyte character
 * MB_FIND_NONZERO	find a non-zero-width multibyte character
 */

#define MB_FIND_ANY 0x00
#define MB_FIND_NONZERO 0x01

extern int _rl_find_prev_mbchar PARAMS((char *, int, int));
extern int _rl_find_next_mbchar PARAMS((char *, int, int, int));

#ifdef HANDLE_MULTIBYTE

extern int _rl_compare_chars PARAMS((char *, int, mbstate_t *, char *, int, mbstate_t *));
extern int _rl_get_char_len PARAMS((char *, mbstate_t *));
extern int _rl_adjust_point PARAMS((char *, int, mbstate_t *));

extern int _rl_read_mbchar PARAMS((char *, int));
extern int _rl_read_mbstring PARAMS((int, char *, int));

extern int _rl_is_mbchar_matched PARAMS((char *, int, int, char *, int));

extern wchar_t _rl_char_value PARAMS((char *, int));
extern int _rl_walphabetic PARAMS((wchar_t));

#define _rl_to_wupper(wc) (iswlower(wc) ? towupper(wc) : (wc))
#define _rl_to_wlower(wc) (iswupper(wc) ? towlower(wc) : (wc))

#define MB_NEXTCHAR(b, s, c, f)                                                                                        \
	((MB_CUR_MAX > 1 && rl_byte_oriented == 0) ? _rl_find_next_mbchar((b), (s), (c), (f)) : ((s) + (c)))
#define MB_PREVCHAR(b, s, f) ((MB_CUR_MAX > 1 && rl_byte_oriented == 0) ? _rl_find_prev_mbchar((b), (s), (f)) : ((s)-1))

#define MB_INVALIDCH(x) ((x) == (size_t)-1 || (x) == (size_t)-2)
#define MB_NULLWCH(x) ((x) == 0)

/* Try and shortcut the printable ascii characters to cut down the number of
   calls to a libc wcwidth() */
static inline int _rl_wcwidth(wc) wchar_t wc;
{
	switch (wc)
	{
		case ' ':
		case '!':
		case '"':
		case '#':
		case '%':
		case '&':
		case '\'':
		case '(':
		case ')':
		case '*':
		case '+':
		case ',':
		case '-':
		case '.':
		case '/':
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
		case ':':
		case ';':
		case '<':
		case '=':
		case '>':
		case '?':
		case 'A':
		case 'B':
		case 'C':
		case 'D':
		case 'E':
		case 'F':
		case 'G':
		case 'H':
		case 'I':
		case 'J':
		case 'K':
		case 'L':
		case 'M':
		case 'N':
		case 'O':
		case 'P':
		case 'Q':
		case 'R':
		case 'S':
		case 'T':
		case 'U':
		case 'V':
		case 'W':
		case 'X':
		case 'Y':
		case 'Z':
		case '[':
		case '\\':
		case ']':
		case '^':
		case '_':
		case 'a':
		case 'b':
		case 'c':
		case 'd':
		case 'e':
		case 'f':
		case 'g':
		case 'h':
		case 'i':
		case 'j':
		case 'k':
		case 'l':
		case 'm':
		case 'n':
		case 'o':
		case 'p':
		case 'q':
		case 'r':
		case 's':
		case 't':
		case 'u':
		case 'v':
		case 'w':
		case 'x':
		case 'y':
		case 'z':
		case '{':
		case '|':
		case '}':
		case '~':
			return 1;
		default:
			return wcwidth(wc);
	}
}

/* Unicode combining characters range from U+0300 to U+036F */
#define UNICODE_COMBINING_CHAR(x) ((x) >= 768 && (x) <= 879)

#if defined(WCWIDTH_BROKEN)
#define WCWIDTH(wc) ((_rl_utf8locale && UNICODE_COMBINING_CHAR(wc)) ? 0 : _rl_wcwidth(wc))
#else
#define WCWIDTH(wc) _rl_wcwidth(wc)
#endif

#if defined(WCWIDTH_BROKEN)
#define IS_COMBINING_CHAR(x) (WCWIDTH(x) == 0 && iswcntrl(x) == 0)
#else
#define IS_COMBINING_CHAR(x) (WCWIDTH(x) == 0)
#endif

#else /* !HANDLE_MULTIBYTE */

#undef MB_LEN_MAX
#undef MB_CUR_MAX

#define MB_LEN_MAX 1
#define MB_CUR_MAX 1

#define _rl_find_prev_mbchar(b, i, f) (((i) == 0) ? (i) : ((i)-1))
#define _rl_find_next_mbchar(b, i1, i2, f) ((i1) + (i2))

#define _rl_char_value(buf, ind) ((buf)[(ind)])

#define _rl_walphabetic(c) (rl_alphabetic(c))

#define _rl_to_wupper(c) (_rl_to_upper(c))
#define _rl_to_wlower(c) (_rl_to_lower(c))

#define MB_NEXTCHAR(b, s, c, f) ((s) + (c))
#define MB_PREVCHAR(b, s, f) ((s)-1)

#define MB_INVALIDCH(x) (0)
#define MB_NULLWCH(x) (0)

#endif /* !HANDLE_MULTIBYTE */

extern int rl_byte_oriented;

#endif /* _RL_MBUTIL_H_ */
/* End rlmbutil.h */

#include "slib/history.h"

/* chardefs.h -- Character definitions for readline. */

#ifndef _CHARDEFS_H_
#define _CHARDEFS_H_

#include <ctype.h>

#if defined(HAVE_CONFIG_H)
#if defined(HAVE_STRING_H)
#if !defined(STDC_HEADERS) && defined(HAVE_MEMORY_H)
#include <memory.h>
#endif
#include <string.h>
#endif /* HAVE_STRING_H */
#if defined(HAVE_STRINGS_H)
#include <strings.h>
#endif /* HAVE_STRINGS_H */
#else
#include <string.h>
#endif /* !HAVE_CONFIG_H */

#ifndef whitespace
#define whitespace(c) (((c) == ' ') || ((c) == '\t'))
#endif

#ifdef CTRL
#undef CTRL
#endif
#ifdef UNCTRL
#undef UNCTRL
#endif

/* Some character stuff. */
#define control_character_threshold 0x020 /* Smaller than this is control. */
#define control_character_mask 0x1f       /* 0x20 - 1 */
#define meta_character_threshold 0x07f    /* Larger than this is Meta. */
#define control_character_bit 0x40	/* 0x000000, must be off. */
#define meta_character_bit 0x080	  /* x0000000, must be on. */
#define largest_char 255		  /* Largest character value. */

#define CTRL_CHAR(c) ((c) < control_character_threshold && (((c)&0x80) == 0))
#define META_CHAR(c) ((c) > meta_character_threshold && (c) <= largest_char)

#define CTRL(c) ((c)&control_character_mask)
#define META(c) ((c) | meta_character_bit)

#define UNMETA(c) ((c) & (~meta_character_bit))
#define UNCTRL(c) _rl_to_upper(((c) | control_character_bit))

#if defined STDC_HEADERS || (!defined(isascii) && !defined(HAVE_ISASCII))
#define IN_CTYPE_DOMAIN(c) 1
#else
#define IN_CTYPE_DOMAIN(c) isascii(c)
#endif

#if !defined(isxdigit) && !defined(HAVE_ISXDIGIT) && !defined(__cplusplus)
#define isxdigit(c) (isdigit((unsigned char)(c)) || ((c) >= 'a' && (c) <= 'f') || ((c) >= 'A' && (c) <= 'F'))
#endif

#if defined(CTYPE_NON_ASCII)
#define NON_NEGATIVE(c) 1
#else
#define NON_NEGATIVE(c) ((unsigned char)(c) == (c))
#endif

/* Some systems define these; we want our definitions. */
#undef ISPRINT

/* Beware:  these only work with single-byte ASCII characters. */

#define ISALNUM(c) (IN_CTYPE_DOMAIN(c) && isalnum((unsigned char)c))
#define ISALPHA(c) (IN_CTYPE_DOMAIN(c) && isalpha((unsigned char)c))
#define ISDIGIT(c) (IN_CTYPE_DOMAIN(c) && isdigit((unsigned char)c))
#define ISLOWER(c) (IN_CTYPE_DOMAIN(c) && islower((unsigned char)c))
#define ISPRINT(c) (IN_CTYPE_DOMAIN(c) && isprint((unsigned char)c))
#define ISUPPER(c) (IN_CTYPE_DOMAIN(c) && isupper((unsigned char)c))
#define ISXDIGIT(c) (IN_CTYPE_DOMAIN(c) && isxdigit((unsigned char)c))

#define _rl_lowercase_p(c) (NON_NEGATIVE(c) && ISLOWER(c))
#define _rl_uppercase_p(c) (NON_NEGATIVE(c) && ISUPPER(c))
#define _rl_digit_p(c) ((c) >= '0' && (c) <= '9')

#define _rl_pure_alphabetic(c) (NON_NEGATIVE(c) && ISALPHA(c))
#define ALPHABETIC(c) (NON_NEGATIVE(c) && ISALNUM(c))

#ifndef _rl_to_upper
#define _rl_to_upper(c) (_rl_lowercase_p(c) ? toupper((unsigned char)c) : (c))
#define _rl_to_lower(c) (_rl_uppercase_p(c) ? tolower((unsigned char)c) : (c))
#endif

#ifndef _rl_digit_value
#define _rl_digit_value(x) ((x) - '0')
#endif

#ifndef _rl_isident
#define _rl_isident(c) (ISALNUM(c) || (c) == '_')
#endif

#ifndef ISOCTAL
#define ISOCTAL(c) ((c) >= '0' && (c) <= '7')
#endif
#define OCTVALUE(c) ((c) - '0')

#define HEXVALUE(c)                                                                                                    \
	(((c) >= 'a' && (c) <= 'f') ? (c) - 'a' + 10 : (c) >= 'A' && (c) <= 'F' ? (c) - 'A' + 10 : (c) - '0')

#ifndef NEWLINE
#define NEWLINE '\n'
#endif

#ifndef RETURN
#define RETURN CTRL('M')
#endif

#ifndef RUBOUT
#define RUBOUT 0x7f
#endif

#ifndef TAB
#define TAB '\t'
#endif

#ifdef ABORT_CHAR
#undef ABORT_CHAR
#endif
#define ABORT_CHAR CTRL('G')

#ifdef PAGE
#undef PAGE
#endif
#define PAGE CTRL('L')

#ifdef SPACE
#undef SPACE
#endif
#define SPACE ' '

#ifdef ESC
#undef ESC
#endif
#define ESC CTRL('[')

#endif /* _CHARDEFS_H_ */
/* End chardefs.h */

#define HISTORY_WORD_DELIMITERS " \t\n;&()|<>"
#define HISTORY_QUOTE_CHARACTERS "\"'`"
#define HISTORY_EVENT_DELIMITERS "^$*%-"

#define slashify_in_quotes "\\`\"$"

typedef int _hist_search_func_t PARAMS((const char *, int));

static char error_pointer;

static char *subst_lhs;
static char *subst_rhs;
static int subst_lhs_len;
static int subst_rhs_len;

/* Characters that delimit history event specifications and separate event
   specifications from word designators.  Static for now */
static char *history_event_delimiter_chars = HISTORY_EVENT_DELIMITERS;

static char *get_history_word_specifier PARAMS((char *, char *, int *));
static int history_tokenize_word PARAMS((const char *, int));
static char **history_tokenize_internal PARAMS((const char *, int, int *));
static char *history_substring PARAMS((const char *, int, int));
static void freewords PARAMS((char **, int));
static char *history_find_word PARAMS((char *, int));

static char *quote_breaks PARAMS((char *));

/* Variables exported by this file. */
/* The character that represents the start of a history expansion
   request.  This is usually `!'. */
char history_expansion_char = '!';

/* The character that invokes word substitution if found at the start of
   a line.  This is usually `^'. */
char history_subst_char = '^';

/* During tokenization, if this character is seen as the first character
   of a word, then it, and all subsequent characters upto a newline are
   ignored.  For a Bourne shell, this should be '#'.  Bash special cases
   the interactive comment character to not be a comment delimiter. */
char history_comment_char = '\0';

/* The list of characters which inhibit the expansion of text if found
   immediately following history_expansion_char. */
char *history_no_expand_chars = " \t\n\r=";

/* If set to a non-zero value, single quotes inhibit history expansion.
   The default is 0. */
int history_quotes_inhibit_expansion = 0;

/* Used to split words by history_tokenize_internal. */
char *history_word_delimiters = HISTORY_WORD_DELIMITERS;

/* If set, this points to a function that is called to verify that a
   particular history expansion should be performed. */
rl_linebuf_func_t *history_inhibit_expansion_function;

/* **************************************************************** */
/*								    */
/*			History Expansion			    */
/*								    */
/* **************************************************************** */

/* Hairy history expansion on text, not tokens.  This is of general
   use, and thus belongs in this library. */

/* The last string searched for by a !?string? search. */
static char *search_string;
/* The last string matched by a !?string? search. */
static char *search_match;

/* Return the event specified at TEXT + OFFSET modifying OFFSET to
   point to after the event specifier.  Just a pointer to the history
   line is returned; NULL is returned in the event of a bad specifier.
   You pass STRING with *INDEX equal to the history_expansion_char that
   begins this specification.
   DELIMITING_QUOTE is a character that is allowed to end the string
   specification for what to search for in addition to the normal
   characters `:', ` ', `\t', `\n', and sometimes `?'.
   So you might call this function like:
   line = get_history_event ("!echo:p", &index, 0);  */
char *get_history_event(string, caller_index, delimiting_quote) const char *string;
int *caller_index;
int delimiting_quote;
{
	register int i;
	register char c;
	HIST_ENTRY *entry;
	int which, sign, local_index, substring_okay;
	_hist_search_func_t *search_func;
	char *temp;

	/* The event can be specified in a number of ways.

	   !!   the previous command
	   !n   command line N
	   !-n  current command-line minus N
	   !str the most recent command starting with STR
	   !?str[?]
	  the most recent command containing STR

	   All values N are determined via HISTORY_BASE. */

	i = *caller_index;

	if (string[i] != history_expansion_char)
		return ((char *)NULL);

	/* Move on to the specification. */
	i++;

	sign = 1;
	substring_okay = 0;

#define RETURN_ENTRY(e, w) return ((e = history_get(w)) ? e->line : (char *)NULL)

	/* Handle !! case. */
	if (string[i] == history_expansion_char)
	{
		i++;
		which = history_base + (history_length - 1);
		*caller_index = i;
		RETURN_ENTRY(entry, which);
	}

	/* Hack case of numeric line specification. */
	if (string[i] == '-')
	{
		sign = -1;
		i++;
	}

	if (_rl_digit_p(string[i]))
	{
		/* Get the extent of the digits and compute the value. */
		for (which = 0; _rl_digit_p(string[i]); i++)
			which = (which * 10) + _rl_digit_value(string[i]);

		*caller_index = i;

		if (sign < 0)
			which = (history_length + history_base) - which;

		RETURN_ENTRY(entry, which);
	}

	/* This must be something to search for.  If the spec begins with
	   a '?', then the string may be anywhere on the line.  Otherwise,
	   the string must be found at the start of a line. */
	if (string[i] == '?')
	{
		substring_okay++;
		i++;
	}

	/* Only a closing `?' or a newline delimit a substring search string. */
	for (local_index = i; (c = string[i]); i++)
	{
#if defined(HANDLE_MULTIBYTE)
		if (MB_CUR_MAX > 1 && rl_byte_oriented == 0)
		{
			int v;
			mbstate_t ps;

			memset(&ps, 0, sizeof(mbstate_t));
			/* These produce warnings because we're passing a const string to a
			   function that takes a non-const string. */
			_rl_adjust_point((char *)string, i, &ps);
			if ((v = _rl_get_char_len((char *)string + i, &ps)) > 1)
			{
				i += v - 1;
				continue;
			}
		}

#endif /* HANDLE_MULTIBYTE */
		if ((!substring_okay &&
		     (whitespace(c) || c == ':' ||
		      (history_event_delimiter_chars && member(c, history_event_delimiter_chars)) ||
		      (history_search_delimiter_chars && member(c, history_search_delimiter_chars)) ||
		      string[i] == delimiting_quote)) ||
		    string[i] == '\n' || (substring_okay && string[i] == '?'))
			break;
	}

	which = i - local_index;
	temp = (char *)xmalloc(1 + which);
	if (which)
		strncpy(temp, string + local_index, which);
	temp[which] = '\0';

	if (substring_okay && string[i] == '?')
		i++;

	*caller_index = i;

#define FAIL_SEARCH()                                                                                                  \
	do                                                                                                             \
	{                                                                                                              \
		history_offset = history_length;                                                                       \
		xfree(temp);                                                                                           \
		return (char *)NULL;                                                                                   \
	} while (0)

	/* If there is no search string, try to use the previous search string,
	   if one exists.  If not, fail immediately. */
	if (*temp == '\0' && substring_okay)
	{
		if (search_string)
		{
			xfree(temp);
			temp = savestring(search_string);
		}
		else
			FAIL_SEARCH();
	}

	search_func = substring_okay ? history_search : history_search_prefix;
	while (1)
	{
		local_index = (*search_func)(temp, -1);

		if (local_index < 0)
			FAIL_SEARCH();

		if (local_index == 0 || substring_okay)
		{
			entry = current_history();
			if (entry == 0)
				FAIL_SEARCH();
			history_offset = history_length;

			/* If this was a substring search, then remember the
			   string that we matched for word substitution. */
			if (substring_okay)
			{
				FREE(search_string);
				search_string = temp;

				FREE(search_match);
				search_match = history_find_word(entry->line, local_index);
			}
			else
				xfree(temp);

			return (entry->line);
		}

		if (history_offset)
			history_offset--;
		else
			FAIL_SEARCH();
	}
#undef FAIL_SEARCH
#undef RETURN_ENTRY
}

/* Function for extracting single-quoted strings.  Used for inhibiting
   history expansion within single quotes. */

/* Extract the contents of STRING as if it is enclosed in single quotes.
   SINDEX, when passed in, is the offset of the character immediately
   following the opening single quote; on exit, SINDEX is left pointing
   to the closing single quote.  FLAGS currently used to allow backslash
   to escape a single quote (e.g., for bash $'...'). */
static void hist_string_extract_single_quoted(string, sindex, flags) char *string;
int *sindex, flags;
{
	register int i;

	for (i = *sindex; string[i] && string[i] != '\''; i++)
	{
		if ((flags & 1) && string[i] == '\\' && string[i + 1])
			i++;
	}

	*sindex = i;
}

static char *quote_breaks(s) char *s;
{
	register char *p, *r;
	char *ret;
	int len = 3;

	for (p = s; p && *p; p++, len++)
	{
		if (*p == '\'')
			len += 3;
		else if (whitespace(*p) || *p == '\n')
			len += 2;
	}

	r = ret = (char *)xmalloc(len);
	*r++ = '\'';
	for (p = s; p && *p;)
	{
		if (*p == '\'')
		{
			*r++ = '\'';
			*r++ = '\\';
			*r++ = '\'';
			*r++ = '\'';
			p++;
		}
		else if (whitespace(*p) || *p == '\n')
		{
			*r++ = '\'';
			*r++ = *p++;
			*r++ = '\'';
		}
		else
			*r++ = *p++;
	}
	*r++ = '\'';
	*r = '\0';
	return ret;
}

static char *hist_error(s, start, current, errtype) char *s;
int start, current, errtype;
{
	char *temp;
	const char *emsg;
	int ll, elen;

	ll = current - start;

	switch (errtype)
	{
		case EVENT_NOT_FOUND:
			emsg = "event not found";
			elen = 15;
			break;
		case BAD_WORD_SPEC:
			emsg = "bad word specifier";
			elen = 18;
			break;
		case SUBST_FAILED:
			emsg = "substitution failed";
			elen = 19;
			break;
		case BAD_MODIFIER:
			emsg = "unrecognized history modifier";
			elen = 29;
			break;
		case NO_PREV_SUBST:
			emsg = "no previous substitution";
			elen = 24;
			break;
		default:
			emsg = "unknown expansion error";
			elen = 23;
			break;
	}

	temp = (char *)xmalloc(ll + elen + 3);
	strncpy(temp, s + start, ll);
	temp[ll] = ':';
	temp[ll + 1] = ' ';
	strcpy(temp + ll + 2, emsg);
	return (temp);
}

/* Get a history substitution string from STR starting at *IPTR
   and return it.  The length is returned in LENPTR.

   A backslash can quote the delimiter.  If the string is the
   empty string, the previous pattern is used.  If there is
   no previous pattern for the lhs, the last history search
   string is used.

   If IS_RHS is 1, we ignore empty strings and set the pattern
   to "" anyway.  subst_lhs is not changed if the lhs is empty;
   subst_rhs is allowed to be set to the empty string. */

static char *get_subst_pattern(str, iptr, delimiter, is_rhs, lenptr) char *str;
int *iptr, delimiter, is_rhs, *lenptr;
{
	register int si, i, j, k;
	char *s;
#if defined(HANDLE_MULTIBYTE)
	mbstate_t ps;
#endif

	s = (char *)NULL;
	i = *iptr;

#if defined(HANDLE_MULTIBYTE)
	memset(&ps, 0, sizeof(mbstate_t));
	_rl_adjust_point(str, i, &ps);
#endif

	for (si = i; str[si] && str[si] != delimiter; si++)
#if defined(HANDLE_MULTIBYTE)
		if (MB_CUR_MAX > 1 && rl_byte_oriented == 0)
		{
			int v;
			if ((v = _rl_get_char_len(str + si, &ps)) > 1)
				si += v - 1;
			else if (str[si] == '\\' && str[si + 1] == delimiter)
				si++;
		}
		else
#endif /* HANDLE_MULTIBYTE */
		    if (str[si] == '\\' && str[si + 1] == delimiter)
			si++;

	if (si > i || is_rhs)
	{
		s = (char *)xmalloc(si - i + 1);
		for (j = 0, k = i; k < si; j++, k++)
		{
			/* Remove a backslash quoting the search string delimiter. */
			if (str[k] == '\\' && str[k + 1] == delimiter)
				k++;
			s[j] = str[k];
		}
		s[j] = '\0';
		if (lenptr)
			*lenptr = j;
	}

	i = si;
	if (str[i])
		i++;
	*iptr = i;

	return s;
}

static void postproc_subst_rhs()
{
	char *new;
	int i, j, new_size;

	new = (char *)xmalloc(new_size = subst_rhs_len + subst_lhs_len);
	for (i = j = 0; i < subst_rhs_len; i++)
	{
		if (subst_rhs[i] == '&')
		{
			if (j + subst_lhs_len >= new_size)
				new = (char *)xrealloc(new, (new_size = new_size * 2 + subst_lhs_len));
			strcpy(new + j, subst_lhs);
			j += subst_lhs_len;
		}
		else
		{
			/* a single backslash protects the `&' from lhs interpolation */
			if (subst_rhs[i] == '\\' && subst_rhs[i + 1] == '&')
				i++;
			if (j >= new_size)
				new = (char *)xrealloc(new, new_size *= 2);
			new[j++] = subst_rhs[i];
		}
	}
	new[j] = '\0';
	xfree(subst_rhs);
	subst_rhs = new;
	subst_rhs_len = j;
}

/* Does shell-like quoting using single quotes. */
static char *sh_single_quote(string) char *string;
{
	register int c;
	char *result, *r, *s;

	result = (char *)xmalloc(3 + (4 * strlen(string)));
	r = result;
	*r++ = '\'';

	for (s = string; s && (c = *s); s++)
	{
		*r++ = c;

		if (c == '\'')
		{
			*r++ = '\\'; /* insert escaped single quote */
			*r++ = '\'';
			*r++ = '\''; /* start new quoted string */
		}
	}

	*r++ = '\'';
	*r = '\0';

	return (result);
}

/* Expand the bulk of a history specifier starting at STRING[START].
   Returns 0 if everything is OK, -1 if an error occurred, and 1
   if the `p' modifier was supplied and the caller should just print
   the returned string.  Returns the new index into string in
   *END_INDEX_PTR, and the expanded specifier in *RET_STRING. */
static int history_expand_internal(string, start, qc, end_index_ptr, ret_string, current_line) char *string;
int start, qc, *end_index_ptr;
char **ret_string;
char *current_line; /* for !# */
{
	int i, n, starting_index;
	int substitute_globally, subst_bywords, want_quotes, print_only;
	char *event, *temp, *result, *tstr, *t, c, *word_spec;
	int result_len;
#if defined(HANDLE_MULTIBYTE)
	mbstate_t ps;

	memset(&ps, 0, sizeof(mbstate_t));
#endif

	result = (char *)xmalloc(result_len = 128);

	i = start;

	/* If it is followed by something that starts a word specifier,
	   then !! is implied as the event specifier. */

	if (member(string[i + 1], ":$*%^"))
	{
		char fake_s[3];
		int fake_i = 0;
		i++;
		fake_s[0] = fake_s[1] = history_expansion_char;
		fake_s[2] = '\0';
		event = get_history_event(fake_s, &fake_i, 0);
	}
	else if (string[i + 1] == '#')
	{
		i += 2;
		event = current_line;
	}
	else
		event = get_history_event(string, &i, qc);

	if (event == 0)
	{
		*ret_string = hist_error(string, start, i, EVENT_NOT_FOUND);
		xfree(result);
		return (-1);
	}

	/* If a word specifier is found, then do what that requires. */
	starting_index = i;
	word_spec = get_history_word_specifier(string, event, &i);

	/* There is no such thing as a `malformed word specifier'.  However,
	   it is possible for a specifier that has no match.  In that case,
	   we complain. */
	if (word_spec == (char *)&error_pointer)
	{
		*ret_string = hist_error(string, starting_index, i, BAD_WORD_SPEC);
		xfree(result);
		return (-1);
	}

	/* If no word specifier, than the thing of interest was the event. */
	temp = word_spec ? savestring(word_spec) : savestring(event);
	FREE(word_spec);

	/* Perhaps there are other modifiers involved.  Do what they say. */
	want_quotes = substitute_globally = subst_bywords = print_only = 0;
	starting_index = i;

	while (string[i] == ':')
	{
		c = string[i + 1];

		if (c == 'g' || c == 'a')
		{
			substitute_globally = 1;
			i++;
			c = string[i + 1];
		}
		else if (c == 'G')
		{
			subst_bywords = 1;
			i++;
			c = string[i + 1];
		}

		switch (c)
		{
			default:
				*ret_string = hist_error(string, i + 1, i + 2, BAD_MODIFIER);
				xfree(result);
				xfree(temp);
				return -1;

			case 'q':
				want_quotes = 'q';
				break;

			case 'x':
				want_quotes = 'x';
				break;

			/* :p means make this the last executed line.  So we
			   return an error state after adding this line to the
			   history. */
			case 'p':
				print_only++;
				break;

			/* :t discards all but the last part of the pathname. */
			case 't':
				tstr = strrchr(temp, '/');
				if (tstr)
				{
					tstr++;
					t = savestring(tstr);
					xfree(temp);
					temp = t;
				}
				break;

			/* :h discards the last part of a pathname. */
			case 'h':
				tstr = strrchr(temp, '/');
				if (tstr)
					*tstr = '\0';
				break;

			/* :r discards the suffix. */
			case 'r':
				tstr = strrchr(temp, '.');
				if (tstr)
					*tstr = '\0';
				break;

			/* :e discards everything but the suffix. */
			case 'e':
				tstr = strrchr(temp, '.');
				if (tstr)
				{
					t = savestring(tstr);
					xfree(temp);
					temp = t;
				}
				break;

				/* :s/this/that substitutes `that' for the first
				   occurrence of `this'.  :gs/this/that substitutes `that'
				   for each occurrence of `this'.  :& repeats the last
				   substitution.  :g& repeats the last substitution
				   globally. */

			case '&':
			case 's':
			{
				char *new_event;
				int delimiter, failed, si, l_temp, ws, we;

				if (c == 's')
				{
					if (i + 2 < (int)strlen(string))
					{
#if defined(HANDLE_MULTIBYTE)
						if (MB_CUR_MAX > 1 && rl_byte_oriented == 0)
						{
							_rl_adjust_point(string, i + 2, &ps);
							if (_rl_get_char_len(string + i + 2, &ps) > 1)
								delimiter = 0;
							else
								delimiter = string[i + 2];
						}
						else
#endif /* HANDLE_MULTIBYTE */
							delimiter = string[i + 2];
					}
					else
						break; /* no search delimiter */

					i += 3;

					t = get_subst_pattern(string, &i, delimiter, 0, &subst_lhs_len);
					/* An empty substitution lhs with no previous substitution
					   uses the last search string as the lhs. */
					if (t)
					{
						FREE(subst_lhs);
						subst_lhs = t;
					}
					else if (!subst_lhs)
					{
						if (search_string && *search_string)
						{
							subst_lhs = savestring(search_string);
							subst_lhs_len = strlen(subst_lhs);
						}
						else
						{
							subst_lhs = (char *)NULL;
							subst_lhs_len = 0;
						}
					}

					FREE(subst_rhs);
					subst_rhs = get_subst_pattern(string, &i, delimiter, 1, &subst_rhs_len);

					/* If `&' appears in the rhs, it's supposed to be replaced
					   with the lhs. */
					if (member('&', subst_rhs))
						postproc_subst_rhs();
				}
				else
					i += 2;

				/* If there is no lhs, the substitution can't succeed. */
				if (subst_lhs_len == 0)
				{
					*ret_string = hist_error(string, starting_index, i, NO_PREV_SUBST);
					xfree(result);
					xfree(temp);
					return -1;
				}

				l_temp = strlen(temp);
				/* Ignore impossible cases. */
				if (subst_lhs_len > l_temp)
				{
					*ret_string = hist_error(string, starting_index, i, SUBST_FAILED);
					xfree(result);
					xfree(temp);
					return (-1);
				}

				/* Find the first occurrence of THIS in TEMP. */
				/* Substitute SUBST_RHS for SUBST_LHS in TEMP.  There are three
				   cases to consider:

				 1.  substitute_globally == subst_bywords == 0
				 2.  substitute_globally == 1 && subst_bywords == 0
				 3.  substitute_globally == 0 && subst_bywords == 1

				   In the first case, we substitute for the first occurrence only.
				   In the second case, we substitute for every occurrence.
				   In the third case, we tokenize into words and substitute the
				   first occurrence of each word. */

				si = we = 0;
				for (failed = 1; (si + subst_lhs_len) <= l_temp; si++)
				{
					/* First skip whitespace and find word boundaries if
					   we're past the end of the word boundary we found
					   the last time. */
					if (subst_bywords && si > we)
					{
						for (; temp[si] && whitespace(temp[si]); si++)
							;
						ws = si;
						we = history_tokenize_word(temp, si);
					}

					if (STREQN(temp + si, subst_lhs, subst_lhs_len))
					{
						int len = subst_rhs_len - subst_lhs_len + l_temp;
						new_event = (char *)xmalloc(1 + len);
						strncpy(new_event, temp, si);
						strncpy(new_event + si, subst_rhs, subst_rhs_len);
						strncpy(new_event + si + subst_rhs_len, temp + si + subst_lhs_len,
							l_temp - (si + subst_lhs_len));
						new_event[len] = '\0';
						xfree(temp);
						temp = new_event;

						failed = 0;

						if (substitute_globally)
						{
							/* Reported to fix a bug that causes it to skip every
							   other match when matching a single character.  Was
							   si += subst_rhs_len previously. */
							si += subst_rhs_len - 1;
							l_temp = strlen(temp);
							substitute_globally++;
							continue;
						}
						else if (subst_bywords)
						{
							si = we;
							l_temp = strlen(temp);
							continue;
						}
						else
							break;
					}
				}

				if (substitute_globally > 1)
				{
					substitute_globally = 0;
					continue; /* don't want to increment i */
				}

				if (failed == 0)
					continue; /* don't want to increment i */

				*ret_string = hist_error(string, starting_index, i, SUBST_FAILED);
				xfree(result);
				xfree(temp);
				return (-1);
			}
		}
		i += 2;
	}
	/* Done with modifiers. */
	/* Believe it or not, we have to back the pointer up by one. */
	--i;

	if (want_quotes)
	{
		char *x;

		if (want_quotes == 'q')
			x = sh_single_quote(temp);
		else if (want_quotes == 'x')
			x = quote_breaks(temp);
		else
			x = savestring(temp);

		xfree(temp);
		temp = x;
	}

	n = strlen(temp);
	if (n >= result_len)
		result = (char *)xrealloc(result, n + 2);
	strcpy(result, temp);
	xfree(temp);

	*end_index_ptr = i;
	*ret_string = result;
	return (print_only);
}

	/* Expand the string STRING, placing the result into OUTPUT, a pointer
	   to a string.  Returns:

	  -1) If there was an error in expansion.
	   0) If no expansions took place (or, if the only change in
	      the text was the de-slashifying of the history expansion
	      character)
	   1) If expansions did take place
	   2) If the `p' modifier was given and the caller should print the result

	  If an error occurred in expansion, then OUTPUT contains a descriptive
	  error message. */

#define ADD_STRING(s)                                                                                                  \
	do                                                                                                             \
	{                                                                                                              \
		int sl = strlen(s);                                                                                    \
		j += sl;                                                                                               \
		if (j >= result_len)                                                                                   \
		{                                                                                                      \
			while (j >= result_len)                                                                        \
				result_len += 128;                                                                     \
			result = (char *)xrealloc(result, result_len);                                                 \
		}                                                                                                      \
		strcpy(result + j - sl, s);                                                                            \
	} while (0)

#define ADD_CHAR(c)                                                                                                    \
	do                                                                                                             \
	{                                                                                                              \
		if (j >= result_len - 1)                                                                               \
			result = (char *)xrealloc(result, result_len += 64);                                           \
		result[j++] = c;                                                                                       \
		result[j] = '\0';                                                                                      \
	} while (0)

int history_expand(hstring, output) char *hstring;
char **output;
{
	register int j;
	int i, r, l, passc, cc, modified, eindex, only_printing, dquote, squote, flag;
	char *string;

	/* The output string, and its length. */
	int result_len;
	char *result;

#if defined(HANDLE_MULTIBYTE)
	char mb[MB_LEN_MAX];
	mbstate_t ps;
#endif

	/* Used when adding the string. */
	char *temp;

	if (output == 0)
		return 0;

	/* Setting the history expansion character to 0 inhibits all
	   history expansion. */
	if (history_expansion_char == 0)
	{
		*output = savestring(hstring);
		return (0);
	}

	/* Prepare the buffer for printing error messages. */
	result = (char *)xmalloc(result_len = 256);
	result[0] = '\0';

	only_printing = modified = 0;
	l = strlen(hstring);

	/* Grovel the string.  Only backslash and single quotes can quote the
	   history escape character.  We also handle arg specifiers. */

	/* Before we grovel forever, see if the history_expansion_char appears
	   anywhere within the text. */

	/* The quick substitution character is a history expansion all right.  That
	   is to say, "^this^that^" is equivalent to "!!:s^this^that^", and in fact,
	   that is the substitution that we do. */
	if (hstring[0] == history_subst_char)
	{
		string = (char *)xmalloc(l + 5);

		string[0] = string[1] = history_expansion_char;
		string[2] = ':';
		string[3] = 's';
		strcpy(string + 4, hstring);
		l += 4;
	}
	else
	{
#if defined(HANDLE_MULTIBYTE)
		memset(&ps, 0, sizeof(mbstate_t));
#endif

		string = hstring;
		/* If not quick substitution, still maybe have to do expansion. */

		/* `!' followed by one of the characters in history_no_expand_chars
		is NOT an expansion. */
		for (i = dquote = squote = 0; string[i]; i++)
		{
#if defined(HANDLE_MULTIBYTE)
			if (MB_CUR_MAX > 1 && rl_byte_oriented == 0)
			{
				int v;
				v = _rl_get_char_len(string + i, &ps);
				if (v > 1)
				{
					i += v - 1;
					continue;
				}
			}
#endif /* HANDLE_MULTIBYTE */

			cc = string[i + 1];
			/* The history_comment_char, if set, appearing at the beginning
			   of a word signifies that the rest of the line should not have
			   history expansion performed on it.
			   Skip the rest of the line and break out of the loop. */
			if (history_comment_char && string[i] == history_comment_char && dquote == 0 &&
			    (i == 0 || member(string[i - 1], history_word_delimiters)))
			{
				while (string[i])
					i++;
				break;
			}
			else if (string[i] == history_expansion_char)
			{
				if (cc == 0 || member(cc, history_no_expand_chars))
					continue;
				/* DQUOTE won't be set unless history_quotes_inhibit_expansion
				is set.  The idea here is to treat double-quoted strings the
				 same as the word outside double quotes; in effect making the
				 double quote part of history_no_expand_chars when DQUOTE is
				 set. */
				else if (dquote && cc == '"')
					continue;
				/* If the calling application has set
				history_inhibit_expansion_function to a function that checks
				 for special cases that should not be history expanded,
				 call the function and skip the expansion if it returns a
				 non-zero value. */
				else if (history_inhibit_expansion_function &&
					 (*history_inhibit_expansion_function)(string, i))
					continue;
				else
					break;
			}
			/* Shell-like quoting: allow backslashes to quote double quotes
			   inside a double-quoted string. */
			else if (dquote && string[i] == '\\' && cc == '"')
				i++;
			/* More shell-like quoting:  if we're paying attention to single
			   quotes and letting them quote the history expansion character,
			   then we need to pay attention to double quotes, because single
			   quotes are not special inside double-quoted strings. */
			else if (history_quotes_inhibit_expansion && string[i] == '"')
			{
				dquote = 1 - dquote;
			}
			else if (dquote == 0 && history_quotes_inhibit_expansion && string[i] == '\'')
			{
				/* If this is bash, single quotes inhibit history expansion. */
				flag = (i > 0 && string[i - 1] == '$');
				i++;
				hist_string_extract_single_quoted(string, &i, flag);
			}
			else if (history_quotes_inhibit_expansion && string[i] == '\\')
			{
				/* If this is bash, allow backslashes to quote single
				quotes and the history expansion character. */
				if (cc == '\'' || cc == history_expansion_char)
					i++;
			}
		}

		if (string[i] != history_expansion_char)
		{
			xfree(result);
			*output = savestring(string);
			return (0);
		}
	}

	/* Extract and perform the substitution. */
	for (passc = dquote = squote = i = j = 0; i < l; i++)
	{
		int qc, tchar = string[i];

		if (passc)
		{
			passc = 0;
			ADD_CHAR(tchar);
			continue;
		}

#if defined(HANDLE_MULTIBYTE)
		if (MB_CUR_MAX > 1 && rl_byte_oriented == 0)
		{
			int k, c;

			c = tchar;
			memset(mb, 0, sizeof(mb));
			for (k = 0; k < MB_LEN_MAX; k++)
			{
				mb[k] = (char)c;
				memset(&ps, 0, sizeof(mbstate_t));
				if (_rl_get_char_len(mb, &ps) == -2)
					c = string[++i];
				else
					break;
			}
			if (strlen(mb) > 1)
			{
				ADD_STRING(mb);
				continue;
			}
		}
#endif /* HANDLE_MULTIBYTE */

		if (tchar == history_expansion_char)
			tchar = -3;
		else if (tchar == history_comment_char)
			tchar = -2;

		switch (tchar)
		{
			default:
				ADD_CHAR(string[i]);
				break;

			case '\\':
				passc++;
				ADD_CHAR(tchar);
				break;

			case '"':
				dquote = 1 - dquote;
				ADD_CHAR(tchar);
				break;

			case '\'':
			{
				/* If history_quotes_inhibit_expansion is set, single quotes
				   inhibit history expansion, otherwise they are treated like
				   double quotes. */
				if (squote)
				{
					squote = 0;
					ADD_CHAR(tchar);
				}
				else if (dquote == 0 && history_quotes_inhibit_expansion)
				{
					int quote, slen;

					flag = (i > 0 && string[i - 1] == '$');
					quote = i++;
					hist_string_extract_single_quoted(string, &i, flag);

					slen = i - quote + 2;
					temp = (char *)xmalloc(slen);
					strncpy(temp, string + quote, slen);
					temp[slen - 1] = '\0';
					ADD_STRING(temp);
					xfree(temp);
				}
				else if (dquote == 0 && squote == 0 && history_quotes_inhibit_expansion == 0)
				{
					squote = 1;
					ADD_CHAR(string[i]);
				}
				else
					ADD_CHAR(string[i]);
				break;
			}

			case -2: /* history_comment_char */
				if ((dquote == 0 || history_quotes_inhibit_expansion == 0) &&
				    (i == 0 || member(string[i - 1], history_word_delimiters)))
				{
					temp = (char *)xmalloc(l - i + 1);
					strcpy(temp, string + i);
					ADD_STRING(temp);
					xfree(temp);
					i = l;
				}
				else
					ADD_CHAR(string[i]);
				break;

			case -3: /* history_expansion_char */
				cc = string[i + 1];

				/* If the history_expansion_char is followed by one of the
				   characters in history_no_expand_chars, then it is not a
				   candidate for expansion of any kind. */
				if (cc == 0 || member(cc, history_no_expand_chars) || (dquote && cc == '"') ||
				    (history_inhibit_expansion_function &&
				     (*history_inhibit_expansion_function)(string, i)))
				{
					ADD_CHAR(string[i]);
					break;
				}

#if defined(NO_BANG_HASH_MODIFIERS)
				/* There is something that is listed as a `word specifier' in csh
				   documentation which means `the expanded text to this point'.
				   That is not a word specifier, it is an event specifier.  If we
				   don't want to allow modifiers with `!#', just stick the current
				   output line in again. */
				if (cc == '#')
				{
					if (result)
					{
						temp = (char *)xmalloc(1 + strlen(result));
						strcpy(temp, result);
						ADD_STRING(temp);
						xfree(temp);
					}
					i++;
					break;
				}
#endif
				qc = squote ? '\'' : (dquote ? '"' : 0);
				r = history_expand_internal(string, i, qc, &eindex, &temp, result);
				if (r < 0)
				{
					*output = temp;
					xfree(result);
					if (string != hstring)
						xfree(string);
					return -1;
				}
				else
				{
					if (temp)
					{
						modified++;
						if (*temp)
							ADD_STRING(temp);
						xfree(temp);
					}
					only_printing += r == 1;
					i = eindex;
				}
				break;
		}
	}

	*output = result;
	if (string != hstring)
		xfree(string);

	if (only_printing)
	{
#if 0
		add_history (result);
#endif
		return (2);
	}

	return (modified != 0);
}

/* Return a consed string which is the word specified in SPEC, and found
   in FROM.  NULL is returned if there is no spec.  The address of
   ERROR_POINTER is returned if the word specified cannot be found.
   CALLER_INDEX is the offset in SPEC to start looking; it is updated
   to point to just after the last character parsed. */
static char *get_history_word_specifier(spec, from, caller_index) char *spec, *from;
int *caller_index;
{
	register int i = *caller_index;
	int first, last;
	int expecting_word_spec = 0;
	char *result;

	/* The range of words to return doesn't exist yet. */
	first = last = 0;
	result = (char *)NULL;

	/* If we found a colon, then this *must* be a word specification.  If
	   it isn't, then it is an error. */
	if (spec[i] == ':')
	{
		i++;
		expecting_word_spec++;
	}

	/* Handle special cases first. */

	/* `%' is the word last searched for. */
	if (spec[i] == '%')
	{
		*caller_index = i + 1;
		return (search_match ? savestring(search_match) : savestring(""));
	}

	/* `*' matches all of the arguments, but not the command. */
	if (spec[i] == '*')
	{
		*caller_index = i + 1;
		result = history_arg_extract(1, '$', from);
		return (result ? result : savestring(""));
	}

	/* `$' is last arg. */
	if (spec[i] == '$')
	{
		*caller_index = i + 1;
		return (history_arg_extract('$', '$', from));
	}

	/* Try to get FIRST and LAST figured out. */

	if (spec[i] == '-')
		first = 0;
	else if (spec[i] == '^')
	{
		first = 1;
		i++;
	}
	else if (_rl_digit_p(spec[i]) && expecting_word_spec)
	{
		for (first = 0; _rl_digit_p(spec[i]); i++)
			first = (first * 10) + _rl_digit_value(spec[i]);
	}
	else
		return ((char *)NULL); /* no valid `first' for word specifier */

	if (spec[i] == '^' || spec[i] == '*')
	{
		last = (spec[i] == '^') ? 1 : '$'; /* x* abbreviates x-$ */
		i++;
	}
	else if (spec[i] != '-')
		last = first;
	else
	{
		i++;

		if (_rl_digit_p(spec[i]))
		{
			for (last = 0; _rl_digit_p(spec[i]); i++)
				last = (last * 10) + _rl_digit_value(spec[i]);
		}
		else if (spec[i] == '$')
		{
			i++;
			last = '$';
		}
#if 0
		else if (!spec[i] || spec[i] == ':')
			/* check against `:' because there could be a modifier separator */
#else
		else
		/* csh seems to allow anything to terminate the word spec here,
		   leaving it as an abbreviation. */
#endif
		last = -1; /* x- abbreviates x-$ omitting word `$' */
	}

	*caller_index = i;

	if (last >= first || last == '$' || last < 0)
		result = history_arg_extract(first, last, from);

	return (result ? result : (char *)&error_pointer);
}

/* Extract the args specified, starting at FIRST, and ending at LAST.
   The args are taken from STRING.  If either FIRST or LAST is < 0,
   then make that arg count from the right (subtract from the number of
   tokens, so that FIRST = -1 means the next to last token on the line).
   If LAST is `$' the last arg from STRING is used. */
char *history_arg_extract(first, last, string) int first, last;
const char *string;
{
	register int i, len;
	char *result;
	int size, offset;
	char **list;

	/* XXX - think about making history_tokenize return a struct array,
	   each struct in array being a string and a length to avoid the
	   calls to strlen below. */
	if ((list = history_tokenize(string)) == NULL)
		return ((char *)NULL);

	for (len = 0; list[len]; len++)
		;

	if (last < 0)
		last = len + last - 1;

	if (first < 0)
		first = len + first - 1;

	if (last == '$')
		last = len - 1;

	if (first == '$')
		first = len - 1;

	last++;

	if (first >= len || last > len || first < 0 || last < 0 || first > last)
		result = ((char *)NULL);
	else
	{
		for (size = 0, i = first; i < last; i++)
			size += strlen(list[i]) + 1;
		result = (char *)xmalloc(size + 1);
		result[0] = '\0';

		for (i = first, offset = 0; i < last; i++)
		{
			strcpy(result + offset, list[i]);
			offset += strlen(list[i]);
			if (i + 1 < last)
			{
				result[offset++] = ' ';
				result[offset] = 0;
			}
		}
	}

	for (i = 0; i < len; i++)
		xfree(list[i]);
	xfree(list);

	return (result);
}

static int history_tokenize_word(string, ind) const char *string;
int ind;
{
	register int i, j;
	int delimiter, nestdelim, delimopen;

	i = ind;
	delimiter = nestdelim = 0;

	if (member(string[i], "()\n"))
	{
		i++;
		return i;
	}

	if (ISDIGIT(string[i]))
	{
		j = i;
		while (string[j] && ISDIGIT(string[j]))
			j++;
		if (string[j] == 0)
			return (j);
		if (string[j] == '<' || string[j] == '>')
			i = j; /* digit sequence is a file descriptor */
		else
		{
			i = j;
			goto get_word; /* digit sequence is part of a word */
		}
	}

	if (member(string[i], "<>;&|$"))
	{
		int peek = string[i + 1];

		if (peek == string[i] && peek != '$')
		{
			if (peek == '<' && string[i + 2] == '-')
				i++;
			else if (peek == '<' && string[i + 2] == '<')
				i++;
			i += 2;
			return i;
		}
		else if (peek == '&' && (string[i] == '>' || string[i] == '<'))
		{
			j = i + 2;
			while (string[j] && ISDIGIT(string[j])) /* file descriptor */
				j++;
			if (string[j] == '-') /* <&[digits]-, >&[digits]- */
				j++;
			return j;
		}
		else if ((peek == '>' && string[i] == '&') || (peek == '|' && string[i] == '>'))
		{
			i += 2;
			return i;
		}
		/* XXX - separated out for later -- bash-4.2 */
		else if ((peek == '(' && (string[i] == '>' || string[i] == '<')) || /* ) */
			 (peek == '(' && string[i] == '$'))			    /*)*/
		{
			i += 2;
			delimopen = '(';
			delimiter = ')';
			nestdelim = 1;
			goto get_word;
		}
#if 0
		else if (peek == '\'' && string[i] == '$')
		{
			i += 2;	/* XXX */
			return i;
		}
#endif

		if (string[i] != '$')
		{
			i++;
			return i;
		}
	}

	/* same code also used for $(...)/<(...)/>(...) above */
	if (member(string[i], "!@?+*"))
	{
		int peek = string[i + 1];

		if (peek == '(') /*)*/
		{
			/* Shell extended globbing patterns */
			i += 2;
			delimopen = '(';
			delimiter = ')'; /* XXX - not perfect */
			nestdelim = 1;
		}
	}

get_word:
	/* Get word from string + i; */

	if (delimiter == 0 && member(string[i], HISTORY_QUOTE_CHARACTERS))
		delimiter = string[i++];

	for (; string[i]; i++)
	{
		if (string[i] == '\\' && string[i + 1] == '\n')
		{
			i++;
			continue;
		}

		if (string[i] == '\\' && delimiter != '\'' &&
		    (delimiter != '"' || member(string[i], slashify_in_quotes)))
		{
			i++;
			continue;
		}

		/* delimiter must be set and set to something other than a quote if
		nestdelim is set, so these tests are safe. */
		if (nestdelim && string[i] == delimopen)
		{
			nestdelim++;
			continue;
		}
		if (nestdelim && string[i] == delimiter)
		{
			nestdelim--;
			if (nestdelim == 0)
				delimiter = 0;
			continue;
		}

		if (delimiter && string[i] == delimiter)
		{
			delimiter = 0;
			continue;
		}

		if (delimiter == 0 && (member(string[i], history_word_delimiters)))
			break;

		if (delimiter == 0 && member(string[i], HISTORY_QUOTE_CHARACTERS))
			delimiter = string[i];
	}

	return i;
}

static char *history_substring(string, start, end) const char *string;
int start, end;
{
	register int len;
	register char *result;

	len = end - start;
	result = (char *)xmalloc(len + 1);
	strncpy(result, string + start, len);
	result[len] = '\0';
	return result;
}

/* Parse STRING into tokens and return an array of strings.  If WIND is
   not -1 and INDP is not null, we also want the word surrounding index
   WIND.  The position in the returned array of strings is returned in
   *INDP. */
static char **history_tokenize_internal(string, wind, indp) const char *string;
int wind, *indp;
{
	char **result;
	register int i, start, result_index, size;

	/* If we're searching for a string that's not part of a word (e.g., " "),
	   make sure we set *INDP to a reasonable value. */
	if (indp && wind != -1)
		*indp = -1;

	/* Get a token, and stuff it into RESULT.  The tokens are split
	   exactly where the shell would split them. */
	for (i = result_index = size = 0, result = (char **)NULL; string[i];)
	{
		/* Skip leading whitespace. */
		for (; string[i] && whitespace(string[i]); i++)
			;
		if (string[i] == 0 || string[i] == history_comment_char)
			return (result);

		start = i;

		i = history_tokenize_word(string, start);

		/* If we have a non-whitespace delimiter character (which would not be
		skipped by the loop above), use it and any adjacent delimiters to
		 make a separate field.  Any adjacent white space will be skipped the
		 next time through the loop. */
		if (i == start && history_word_delimiters)
		{
			i++;
			while (string[i] && member(string[i], history_word_delimiters))
				i++;
		}

		/* If we are looking for the word in which the character at a
		particular index falls, remember it. */
		if (indp && wind != -1 && wind >= start && wind < i)
			*indp = result_index;

		if (result_index + 2 >= size)
			result = (char **)xrealloc(result, ((size += 10) * sizeof(char *)));

		result[result_index++] = history_substring(string, start, i);
		result[result_index] = (char *)NULL;
	}

	return (result);
}

/* Return an array of tokens, much as the shell might.  The tokens are
   parsed out of STRING. */
char **history_tokenize(string) const char *string;
{
	return (history_tokenize_internal(string, -1, (int *)NULL));
}

/* Free members of WORDS from START to an empty string */
static void freewords(words, start) char **words;
int start;
{
	register int i;

	for (i = start; words[i]; i++)
		xfree(words[i]);
}

/* Find and return the word which contains the character at index IND
   in the history line LINE.  Used to save the word matched by the
   last history !?string? search. */
static char *history_find_word(line, ind) char *line;
int ind;
{
	char **words, *s;
	int i, wind;

	words = history_tokenize_internal(line, ind, &wind);
	if (wind == -1 || words == 0)
	{
		if (words)
			freewords(words, 0);
		FREE(words);
		return ((char *)NULL);
	}
	s = words[wind];
	for (i = 0; i < wind; i++)
		xfree(words[i]);
	freewords(words, wind + 1);
	xfree(words);
	return s;
}
	/* histfile.c - functions to manipulate the history file. */

#if defined(__TANDEM)
#include <floss.h>
#endif

#ifndef HAVE_CHOWN
#define chown(x, y, z) 0
#endif

#if defined(HAVE_LIMITS_H)
#include <limits.h>
#endif

#if !defined(_MINIX) && defined(HAVE_SYS_FILE_H)
#include <sys/file.h>
#endif

	/* posixstat.h -- Posix stat(2) definitions for systems that
	   don't have them. */

#if !defined(_POSIXSTAT_H_)
#define _POSIXSTAT_H_

#include <sys/stat.h>

#if defined(STAT_MACROS_BROKEN)
#undef S_ISBLK
#undef S_ISCHR
#undef S_ISDIR
#undef S_ISFIFO
#undef S_ISREG
#undef S_ISLNK
#endif /* STAT_MACROS_BROKEN */

/* These are guaranteed to work only on isc386 */
#if !defined(S_IFDIR) && !defined(S_ISDIR)
#define S_IFDIR 0040000
#endif /* !S_IFDIR && !S_ISDIR */
#if !defined(S_IFMT)
#define S_IFMT 0170000
#endif /* !S_IFMT */

	/* Posix 1003.1 5.6.1.1 <sys/stat.h> file types */

	/* Some Posix-wannabe systems define _S_IF* macros instead of S_IF*, but
	   do not provide the S_IS* macros that Posix requires. */

#if defined(_S_IFMT) && !defined(S_IFMT)
#define S_IFMT _S_IFMT
#endif
#if defined(_S_IFIFO) && !defined(S_IFIFO)
#define S_IFIFO _S_IFIFO
#endif
#if defined(_S_IFCHR) && !defined(S_IFCHR)
#define S_IFCHR _S_IFCHR
#endif
#if defined(_S_IFDIR) && !defined(S_IFDIR)
#define S_IFDIR _S_IFDIR
#endif
#if defined(_S_IFBLK) && !defined(S_IFBLK)
#define S_IFBLK _S_IFBLK
#endif
#if defined(_S_IFREG) && !defined(S_IFREG)
#define S_IFREG _S_IFREG
#endif
#if defined(_S_IFLNK) && !defined(S_IFLNK)
#define S_IFLNK _S_IFLNK
#endif
#if defined(_S_IFSOCK) && !defined(S_IFSOCK)
#define S_IFSOCK _S_IFSOCK
#endif

	/* Test for each symbol individually and define the ones necessary (some
	   systems claiming Posix compatibility define some but not all). */

#if defined(S_IFBLK) && !defined(S_ISBLK)
#define S_ISBLK(m) (((m)&S_IFMT) == S_IFBLK) /* block device */
#endif

#if defined(S_IFCHR) && !defined(S_ISCHR)
#define S_ISCHR(m) (((m)&S_IFMT) == S_IFCHR) /* character device */
#endif

#if defined(S_IFDIR) && !defined(S_ISDIR)
#define S_ISDIR(m) (((m)&S_IFMT) == S_IFDIR) /* directory */
#endif

#if defined(S_IFREG) && !defined(S_ISREG)
#define S_ISREG(m) (((m)&S_IFMT) == S_IFREG) /* file */
#endif

#if defined(S_IFIFO) && !defined(S_ISFIFO)
#define S_ISFIFO(m) (((m)&S_IFMT) == S_IFIFO) /* fifo - named pipe */
#endif

#if defined(S_IFLNK) && !defined(S_ISLNK)
#define S_ISLNK(m) (((m)&S_IFMT) == S_IFLNK) /* symbolic link */
#endif

#if defined(S_IFSOCK) && !defined(S_ISSOCK)
#define S_ISSOCK(m) (((m)&S_IFMT) == S_IFSOCK) /* socket */
#endif

	/*
	 * POSIX 1003.1 5.6.1.2 <sys/stat.h> File Modes
	 */

#if !defined(S_IRWXU)
#if !defined(S_IREAD)
#define S_IREAD 00400
#define S_IWRITE 00200
#define S_IEXEC 00100
#endif /* S_IREAD */

#if !defined(S_IRUSR)
#define S_IRUSR S_IREAD  /* read, owner */
#define S_IWUSR S_IWRITE /* write, owner */
#define S_IXUSR S_IEXEC  /* execute, owner */

#define S_IRGRP (S_IREAD >> 3)  /* read, group */
#define S_IWGRP (S_IWRITE >> 3) /* write, group */
#define S_IXGRP (S_IEXEC >> 3)  /* execute, group */

#define S_IROTH (S_IREAD >> 6)  /* read, other */
#define S_IWOTH (S_IWRITE >> 6) /* write, other */
#define S_IXOTH (S_IEXEC >> 6)  /* execute, other */
#endif				/* !S_IRUSR */

#define S_IRWXU (S_IRUSR | S_IWUSR | S_IXUSR)
#define S_IRWXG (S_IRGRP | S_IWGRP | S_IXGRP)
#define S_IRWXO (S_IROTH | S_IWOTH | S_IXOTH)
#endif /* !S_IRWXU */

/* These are non-standard, but are used in builtins.c$symbolic_umask() */
#define S_IRUGO (S_IRUSR | S_IRGRP | S_IROTH)
#define S_IWUGO (S_IWUSR | S_IWGRP | S_IWOTH)
#define S_IXUGO (S_IXUSR | S_IXGRP | S_IXOTH)

#endif /* _POSIXSTAT_H_ */
	/* End posixstat.h */

#include <fcntl.h>

#include <ctype.h>

#if defined(__EMX__)
#undef HAVE_MMAP
#endif

#if defined(HAVE_MMAP) && defined(HAVE_FTRUNCATE)
#define HISTORY_USE_MMAP 1
#endif

#ifdef HISTORY_USE_MMAP
#include <sys/mman.h>

#ifdef MAP_FILE
#define MAP_RFLAGS (MAP_FILE | MAP_PRIVATE)
#define MAP_WFLAGS (MAP_FILE | MAP_SHARED)
#else
#define MAP_RFLAGS MAP_PRIVATE
#define MAP_WFLAGS MAP_SHARED
#endif

#ifndef MAP_FAILED
#define MAP_FAILED ((void *)-1)
#endif

#endif /* HISTORY_USE_MMAP */

/* If we're compiling for __EMX__ (OS/2) or __CYGWIN__ (cygwin32 environment
   on win 95/98/nt), we want to open files with O_BINARY mode so that there
   is no \n -> \r\n conversion performed.  On other systems, we don't want to
   mess around with O_BINARY at all, so we ensure that it's defined to 0. */
#if defined(__EMX__) || defined(__CYGWIN__)
#ifndef O_BINARY
#define O_BINARY 0
#endif
#else /* !__EMX__ && !__CYGWIN__ */
#undef O_BINARY
#define O_BINARY 0
#endif /* !__EMX__ && !__CYGWIN__ */

#include <errno.h>
#if !defined(errno)
extern int errno;
#endif /* !errno */

#if !defined(PATH_MAX)
#define PATH_MAX 1024 /* default */
#endif

extern void _hs_append_history_line PARAMS((int, const char *));

/* history file version; currently unused */
int history_file_version = 1;

/* If non-zero, we write timestamps to the history file in history_do_write() */
int history_write_timestamps = 0;

/* If non-zero, we assume that a history file that starts with a timestamp
   uses timestamp-delimited entries and can include multi-line history
   entries. Used by read_history_range */
int history_multiline_entries = 0;

/* Immediately after a call to read_history() or read_history_range(), this
   will return the number of lines just read from the history file in that
   call. */
int history_lines_read_from_file = 0;

/* Immediately after a call to write_history() or history_do_write(), this
   will return the number of lines just written to the history file in that
   call.  This also works with history_truncate_file. */
int history_lines_written_to_file = 0;

/* Does S look like the beginning of a history timestamp entry?  Placeholder
   for more extensive tests. */
#define HIST_TIMESTAMP_START(s) (*(s) == history_comment_char && isdigit((unsigned char)(s)[1]))

static char *history_backupfile PARAMS((const char *));
static char *history_tempfile PARAMS((const char *));
static int histfile_backup PARAMS((const char *, const char *));
static int histfile_restore PARAMS((const char *, const char *));

static char *sh_get_env_value(varname) const char *varname;
{
	return ((char *)getenv(varname));
}

/* Return the string that should be used in the place of this
   filename.  This only matters when you don't specify the
   filename to read_history (), or write_history (). */
static char *history_filename(filename) const char *filename;
{
	char *return_val;
	const char *home;
	int home_len;

	return_val = filename ? savestring(filename) : (char *)NULL;

	if (return_val)
		return (return_val);

	home = sh_get_env_value("HOME");
#if defined(_WIN32)
	if (home == 0)
		home = sh_get_env_value("APPDATA");
#endif

	if (home == 0)
		return (NULL);
	else
		home_len = strlen(home);

	return_val = (char *)xmalloc(2 + home_len + 8); /* strlen(".history") == 8 */
	strcpy(return_val, home);
	return_val[home_len] = '/';
#if defined(__MSDOS__)
	strcpy(return_val + home_len + 1, "_history");
#else
	strcpy(return_val + home_len + 1, ".history");
#endif

	return (return_val);
}

static char *history_backupfile(filename) const char *filename;
{
	const char *fn;
	char *ret, linkbuf[PATH_MAX + 1];
	size_t len;
	ssize_t n;
	struct stat fs;

	fn = filename;
#if defined(HAVE_READLINK)
	/* Follow symlink to avoid backing up symlink itself; call will fail if
	   not a symlink */
	if ((n = readlink(filename, linkbuf, sizeof(linkbuf) - 1)) > 0)
	{
		linkbuf[n] = '\0';
		fn = linkbuf;
	}
#endif

	len = strlen(fn);
	ret = xmalloc(len + 2);
	strcpy(ret, fn);
	ret[len] = '-';
	ret[len + 1] = '\0';
	return ret;
}

static char *history_tempfile(filename) const char *filename;
{
	const char *fn;
	char *ret, linkbuf[PATH_MAX + 1];
	size_t len;
	ssize_t n;
	struct stat fs;
	int pid;

	fn = filename;
#if defined(HAVE_READLINK)
	/* Follow symlink so tempfile created in the same directory as any symlinked
	   history file; call will fail if not a symlink */
	if ((n = readlink(filename, linkbuf, sizeof(linkbuf) - 1)) > 0)
	{
		linkbuf[n] = '\0';
		fn = linkbuf;
	}
#endif

	len = strlen(fn);
	ret = xmalloc(len + 11);
	strcpy(ret, fn);

	pid = (int)getpid();

	/* filename-PID.tmp */
	ret[len] = '-';
	ret[len + 1] = (pid / 10000 % 10) + '0';
	ret[len + 2] = (pid / 1000 % 10) + '0';
	ret[len + 3] = (pid / 100 % 10) + '0';
	ret[len + 4] = (pid / 10 % 10) + '0';
	ret[len + 5] = (pid % 10) + '0';
	strcpy(ret + len + 6, ".tmp");

	return ret;
}

/* Add the contents of FILENAME to the history list, a line at a time.
   If FILENAME is NULL, then read from ~/.history.  Returns 0 if
   successful, or errno if not. */
int read_history(filename) const char *filename;
{
	return (read_history_range(filename, 0, -1));
}

/* Read a range of lines from FILENAME, adding them to the history list.
   Start reading at the FROM'th line and end at the TO'th.  If FROM
   is zero, start at the beginning.  If TO is less than FROM, read
   until the end of the file.  If FILENAME is NULL, then read from
   ~/.history.  Returns 0 if successful, or errno if not. */
int read_history_range(filename, from, to) const char *filename;
int from, to;
{
	register char *line_start, *line_end, *p;
	char *input, *buffer, *bufend, *last_ts;
	int file, current_line, chars_read, has_timestamps, reset_comment_char;
	struct stat finfo;
	size_t file_size;
#if defined(EFBIG)
	int overflow_errno = EFBIG;
#elif defined(EOVERFLOW)
	int overflow_errno = EOVERFLOW;
#else
	int overflow_errno = EIO;
#endif

	history_lines_read_from_file = 0;

	buffer = last_ts = (char *)NULL;
	input = history_filename(filename);
	file = input ? open(input, O_RDONLY | O_BINARY, 0666) : -1;

	if ((file < 0) || (fstat(file, &finfo) == -1))
		goto error_and_exit;

	file_size = (size_t)finfo.st_size;

	/* check for overflow on very large files */
	if (file_size != finfo.st_size || file_size + 1 < file_size)
	{
		errno = overflow_errno;
		goto error_and_exit;
	}

#ifdef HISTORY_USE_MMAP
	/* We map read/write and private so we can change newlines to NULs without
	   affecting the underlying object. */
	buffer = (char *)mmap(0, file_size, PROT_READ | PROT_WRITE, MAP_RFLAGS, file, 0);
	if ((void *)buffer == MAP_FAILED)
	{
		errno = overflow_errno;
		goto error_and_exit;
	}
	chars_read = file_size;
#else
	buffer = (char *)malloc(file_size + 1);
	if (buffer == 0)
	{
		errno = overflow_errno;
		goto error_and_exit;
	}

	chars_read = read(file, buffer, file_size);
#endif
	if (chars_read < 0)
	{
	error_and_exit:
		if (errno != 0)
			chars_read = errno;
		else
			chars_read = EIO;
		if (file >= 0)
			close(file);

		FREE(input);
#ifndef HISTORY_USE_MMAP
		FREE(buffer);
#endif

		return (chars_read);
	}

	close(file);

	/* Set TO to larger than end of file if negative. */
	if (to < 0)
		to = chars_read;

	/* Start at beginning of file, work to end. */
	bufend = buffer + chars_read;
	current_line = 0;

	/* Heuristic: the history comment character rarely changes, so assume we
	   have timestamps if the buffer starts with `#[:digit:]' and temporarily
	   set history_comment_char so timestamp parsing works right */
	reset_comment_char = 0;
	if (history_comment_char == '\0' && buffer[0] == '#' && isdigit((unsigned char)buffer[1]))
	{
		history_comment_char = '#';
		reset_comment_char = 1;
	}

	has_timestamps = HIST_TIMESTAMP_START(buffer);
	history_multiline_entries += has_timestamps && history_write_timestamps;

	/* Skip lines until we are at FROM. */
	for (line_start = line_end = buffer; line_end < bufend && current_line < from; line_end++)
		if (*line_end == '\n')
		{
			p = line_end + 1;
			/* If we see something we think is a timestamp, continue with this
			line.  We should check more extensively here... */
			if (HIST_TIMESTAMP_START(p) == 0)
				current_line++;
			line_start = p;
		}

	/* If there are lines left to gobble, then gobble them now. */
	for (line_end = line_start; line_end < bufend; line_end++)
		if (*line_end == '\n')
		{
			/* Change to allow Windows-like \r\n end of line delimiter. */
			if (line_end > line_start && line_end[-1] == '\r')
				line_end[-1] = '\0';
			else
				*line_end = '\0';

			if (*line_start)
			{
				if (HIST_TIMESTAMP_START(line_start) == 0)
				{
					if (last_ts == NULL && history_multiline_entries)
						_hs_append_history_line(history_length - 1, line_start);
					else
						add_history(line_start);
					if (last_ts)
					{
						add_history_time(last_ts);
						last_ts = NULL;
					}
				}
				else
				{
					last_ts = line_start;
					current_line--;
				}
			}

			current_line++;

			if (current_line >= to)
				break;

			line_start = line_end + 1;
		}

	history_lines_read_from_file = current_line;
	if (reset_comment_char)
		history_comment_char = '\0';

	FREE(input);
#ifndef HISTORY_USE_MMAP
	FREE(buffer);
#else
	munmap(buffer, file_size);
#endif

	return (0);
}

/* Save FILENAME to BACK, handling case where FILENAME is a symlink
   (e.g., ~/.bash_history -> .histfiles/.bash_history.$HOSTNAME) */
static int histfile_backup(filename, back) const char *filename;
const char *back;
{
#if defined(HAVE_READLINK)
	char linkbuf[PATH_MAX + 1];
	ssize_t n;

	/* Follow to target of symlink to avoid renaming symlink itself */
	if ((n = readlink(filename, linkbuf, sizeof(linkbuf) - 1)) > 0)
	{
		linkbuf[n] = '\0';
		return (rename(linkbuf, back));
	}
#endif
	return (rename(filename, back));
}

/* Restore ORIG from BACKUP handling case where ORIG is a symlink
   (e.g., ~/.bash_history -> .histfiles/.bash_history.$HOSTNAME) */
static int histfile_restore(backup, orig) const char *backup;
const char *orig;
{
#if defined(HAVE_READLINK)
	char linkbuf[PATH_MAX + 1];
	ssize_t n;

	/* Follow to target of symlink to avoid renaming symlink itself */
	if ((n = readlink(orig, linkbuf, sizeof(linkbuf) - 1)) > 0)
	{
		linkbuf[n] = '\0';
		return (rename(backup, linkbuf));
	}
#endif
	return (rename(backup, orig));
}

/* Truncate the history file FNAME, leaving only LINES trailing lines.
   If FNAME is NULL, then use ~/.history.  Writes a new file and renames
   it to the original name.  Returns 0 on success, errno on failure. */
int history_truncate_file(fname, lines) const char *fname;
int lines;
{
	char *buffer, *filename, *tempname, *bp, *bp1; /* bp1 == bp+1 */
	int file, chars_read, rv, orig_lines, exists, r;
	struct stat finfo;
	size_t file_size;

	history_lines_written_to_file = 0;

	buffer = (char *)NULL;
	filename = history_filename(fname);
	tempname = 0;
	file = filename ? open(filename, O_RDONLY | O_BINARY, 0666) : -1;
	rv = exists = 0;

	/* Don't try to truncate non-regular files. */
	if (file == -1 || fstat(file, &finfo) == -1)
	{
		rv = errno;
		if (file != -1)
			close(file);
		goto truncate_exit;
	}
	exists = 1;

	if (S_ISREG(finfo.st_mode) == 0)
	{
		close(file);
#ifdef EFTYPE
		rv = EFTYPE;
#else
		rv = EINVAL;
#endif
		goto truncate_exit;
	}

	file_size = (size_t)finfo.st_size;

	/* check for overflow on very large files */
	if (file_size != finfo.st_size || file_size + 1 < file_size)
	{
		close(file);
#if defined(EFBIG)
		rv = errno = EFBIG;
#elif defined(EOVERFLOW)
		rv = errno = EOVERFLOW;
#else
		rv = errno = EINVAL;
#endif
		goto truncate_exit;
	}

	buffer = (char *)malloc(file_size + 1);
	if (buffer == 0)
	{
		rv = errno;
		close(file);
		goto truncate_exit;
	}

	chars_read = read(file, buffer, file_size);
	close(file);

	if (chars_read <= 0)
	{
		rv = (chars_read < 0) ? errno : 0;
		goto truncate_exit;
	}

	orig_lines = lines;
	/* Count backwards from the end of buffer until we have passed
	   LINES lines.  bp1 is set funny initially.  But since bp[1] can't
	   be a comment character (since it's off the end) and *bp can't be
	   both a newline and the history comment character, it should be OK. */
	for (bp1 = bp = buffer + chars_read - 1; lines && bp > buffer; bp--)
	{
		if (*bp == '\n' && HIST_TIMESTAMP_START(bp1) == 0)
			lines--;
		bp1 = bp;
	}

	/* If this is the first line, then the file contains exactly the
	   number of lines we want to truncate to, so we don't need to do
	   anything.  It's the first line if we don't find a newline between
	   the current value of i and 0.  Otherwise, write from the start of
	   this line until the end of the buffer. */
	for (; bp > buffer; bp--)
	{
		if (*bp == '\n' && HIST_TIMESTAMP_START(bp1) == 0)
		{
			bp++;
			break;
		}
		bp1 = bp;
	}

	/* Write only if there are more lines in the file than we want to
	   truncate to. */
	if (bp <= buffer)
	{
		rv = 0;
		/* No-op if LINES == 0 at this point */
		history_lines_written_to_file = orig_lines - lines;
		goto truncate_exit;
	}

	tempname = history_tempfile(filename);

	if ((file = open(tempname, O_WRONLY | O_CREAT | O_TRUNC | O_BINARY, 0600)) != -1)
	{
		if (write(file, bp, chars_read - (bp - buffer)) < 0)
			rv = errno;

		if (close(file) < 0 && rv == 0)
			rv = errno;
	}
	else
		rv = errno;

truncate_exit:
	FREE(buffer);

	history_lines_written_to_file = orig_lines - lines;

	if (rv == 0 && filename && tempname)
		rv = histfile_restore(tempname, filename);

	if (rv != 0)
	{
		if (tempname)
			unlink(tempname);
		history_lines_written_to_file = 0;
	}

	/* Make sure the new filename is owned by the same user as the old.  If one
	   user is running this, it's a no-op.  If the shell is running after sudo
	   with a shared history file, we don't want to leave the history file
	   owned by root. */
	if (rv == 0 && exists)
		r = chown(filename, finfo.st_uid, finfo.st_gid);

	xfree(filename);
	FREE(tempname);

	return rv;
}

/* Workhorse function for writing history.  Writes the last NELEMENT entries
   from the history list to FILENAME.  OVERWRITE is non-zero if you
   wish to replace FILENAME with the entries. */
static int history_do_write(filename, nelements, overwrite) const char *filename;
int nelements, overwrite;
{
	register int i;
	char *output, *tempname, *histname;
	int file, mode, rv, exists;
	struct stat finfo;
#ifdef HISTORY_USE_MMAP
	size_t cursize;

	history_lines_written_to_file = 0;

	mode = overwrite ? O_RDWR | O_CREAT | O_TRUNC | O_BINARY : O_RDWR | O_APPEND | O_BINARY;
#else
	mode = overwrite ? O_WRONLY | O_CREAT | O_TRUNC | O_BINARY : O_WRONLY | O_APPEND | O_BINARY;
#endif
	histname = history_filename(filename);
	exists = histname ? (stat(histname, &finfo) == 0) : 0;

	tempname = (overwrite && exists && S_ISREG(finfo.st_mode)) ? history_tempfile(histname) : 0;
	output = tempname ? tempname : histname;

	file = output ? open(output, mode, 0600) : -1;
	rv = 0;

	if (file == -1)
	{
		rv = errno;
		FREE(histname);
		FREE(tempname);
		return (rv);
	}

#ifdef HISTORY_USE_MMAP
	cursize = overwrite ? 0 : lseek(file, 0, SEEK_END);
#endif

	if (nelements > history_length)
		nelements = history_length;

	/* Build a buffer of all the lines to write, and write them in one syscall.
	   Suggested by Peter Ho (peter@robosts.oxford.ac.uk). */
	{
		HIST_ENTRY **the_history; /* local */
		register int j;
		int buffer_size;
		char *buffer;

		the_history = history_list();
		/* Calculate the total number of bytes to write. */
		for (buffer_size = 0, i = history_length - nelements; i < history_length; i++)
#if 0
			buffer_size += 2 + HISTENT_BYTES (the_history[i]);
#else
		{
			if (history_write_timestamps && the_history[i]->timestamp && the_history[i]->timestamp[0])
				buffer_size += strlen(the_history[i]->timestamp) + 1;
			buffer_size += strlen(the_history[i]->line) + 1;
		}
#endif

		/* Allocate the buffer, and fill it. */
#ifdef HISTORY_USE_MMAP
			if (ftruncate(file, buffer_size + cursize) == -1)
				goto mmap_error;
		buffer = (char *)mmap(0, buffer_size, PROT_READ | PROT_WRITE, MAP_WFLAGS, file, cursize);
		if ((void *)buffer == MAP_FAILED)
		{
		mmap_error:
			rv = errno;
			close(file);
			if (tempname)
				unlink(tempname);
			FREE(histname);
			FREE(tempname);
			return rv;
		}
#else
		buffer = (char *)malloc(buffer_size);
		if (buffer == 0)
		{
			rv = errno;
			close(file);
			if (tempname)
				unlink(tempname);
			FREE(histname);
			FREE(tempname);
			return rv;
		}
#endif

		for (j = 0, i = history_length - nelements; i < history_length; i++)
		{
			if (history_write_timestamps && the_history[i]->timestamp && the_history[i]->timestamp[0])
			{
				strcpy(buffer + j, the_history[i]->timestamp);
				j += strlen(the_history[i]->timestamp);
				buffer[j++] = '\n';
			}
			strcpy(buffer + j, the_history[i]->line);
			j += strlen(the_history[i]->line);
			buffer[j++] = '\n';
		}

#ifdef HISTORY_USE_MMAP
		if (msync(buffer, buffer_size, MS_ASYNC) != 0 || munmap(buffer, buffer_size) != 0)
			rv = errno;
#else
		if (write(file, buffer, buffer_size) < 0)
			rv = errno;
		xfree(buffer);
#endif
	}

	history_lines_written_to_file = nelements;

	if (close(file) < 0 && rv == 0)
		rv = errno;

	if (rv == 0 && histname && tempname)
		rv = histfile_restore(tempname, histname);

	if (rv != 0)
	{
		if (tempname)
			unlink(tempname);
		history_lines_written_to_file = 0;
	}

	/* Make sure the new filename is owned by the same user as the old.  If one
	   user is running this, it's a no-op.  If the shell is running after sudo
	   with a shared history file, we don't want to leave the history file
	   owned by root. */
	if (rv == 0 && exists)
		mode = chown(histname, finfo.st_uid, finfo.st_gid);

	FREE(histname);
	FREE(tempname);

	return (rv);
}

/* Append NELEMENT entries to FILENAME.  The entries appended are from
   the end of the list minus NELEMENTs up to the end of the list. */
int append_history(nelements, filename) int nelements;
const char *filename;
{
	return (history_do_write(filename, nelements, HISTORY_APPEND));
}

/* Overwrite FILENAME with the current history.  If FILENAME is NULL,
   then write the history list to ~/.history.  Values returned
   are as in read_history ().*/
int write_history(filename) const char *filename;
{
	return (history_do_write(filename, history_length, HISTORY_OVERWRITE));
}
/* histsearch.c -- searching the history list. */

/* The list of alternate characters that can delimit a history search
   string. */
char *history_search_delimiter_chars = (char *)NULL;

static int history_search_internal PARAMS((const char *, int, int));

/* Search the history for STRING, starting at history_offset.
   If DIRECTION < 0, then the search is through previous entries, else
   through subsequent.  If ANCHORED is non-zero, the string must
   appear at the beginning of a history line, otherwise, the string
   may appear anywhere in the line.  If the string is found, then
   current_history () is the history entry, and the value of this
   function is the offset in the line of that history entry that the
   string was found in.  Otherwise, nothing is changed, and a -1 is
   returned. */

static int history_search_internal(string, direction, anchored) const char *string;
int direction, anchored;
{
	register int i, reverse;
	register char *line;
	register int line_index;
	int string_len;
	HIST_ENTRY **the_history; /* local */

	i = history_offset;
	reverse = (direction < 0);

	/* Take care of trivial cases first. */
	if (string == 0 || *string == '\0')
		return (-1);

	if (!history_length || ((i >= history_length) && !reverse))
		return (-1);

	if (reverse && (i >= history_length))
		i = history_length - 1;

#define NEXT_LINE()                                                                                                    \
	do                                                                                                             \
	{                                                                                                              \
		if (reverse)                                                                                           \
			i--;                                                                                           \
		else                                                                                                   \
			i++;                                                                                           \
	} while (0)

	the_history = history_list();
	string_len = strlen(string);
	while (1)
	{
		/* Search each line in the history list for STRING. */

		/* At limit for direction? */
		if ((reverse && i < 0) || (!reverse && i == history_length))
			return (-1);

		line = the_history[i]->line;
		line_index = strlen(line);

		/* If STRING is longer than line, no match. */
		if (string_len > line_index)
		{
			NEXT_LINE();
			continue;
		}

		/* Handle anchored searches first. */
		if (anchored == ANCHORED_SEARCH)
		{
			if (STREQN(string, line, string_len))
			{
				history_offset = i;
				return (0);
			}

			NEXT_LINE();
			continue;
		}

		/* Do substring search. */
		if (reverse)
		{
			line_index -= string_len;

			while (line_index >= 0)
			{
				if (STREQN(string, line + line_index, string_len))
				{
					history_offset = i;
					return (line_index);
				}
				line_index--;
			}
		}
		else
		{
			register int limit;

			limit = line_index - string_len + 1;
			line_index = 0;

			while (line_index < limit)
			{
				if (STREQN(string, line + line_index, string_len))
				{
					history_offset = i;
					return (line_index);
				}
				line_index++;
			}
		}
		NEXT_LINE();
	}
}

/* Do a non-anchored search for STRING through the history in DIRECTION. */
int history_search(string, direction) const char *string;
int direction;
{
	return (history_search_internal(string, direction, NON_ANCHORED_SEARCH));
}

/* Do an anchored search for string through the history in DIRECTION. */
int history_search_prefix(string, direction) const char *string;
int direction;
{
	return (history_search_internal(string, direction, ANCHORED_SEARCH));
}

/* Search for STRING in the history list.  DIR is < 0 for searching
   backwards.  POS is an absolute index into the history list at
   which point to begin searching. */
int history_search_pos(string, dir, pos) const char *string;
int dir, pos;
{
	int ret, old;

	old = where_history();
	history_set_pos(pos);
	if (history_search(string, dir) == -1)
	{
		history_set_pos(old);
		return (-1);
	}
	ret = where_history();
	history_set_pos(old);
	return ret;
}
/* history.c -- standalone history library */

/* How big to make the_history when we first allocate it. */
#define DEFAULT_HISTORY_INITIAL_SIZE 502

/* The number of slots to increase the_history by. */
#define DEFAULT_HISTORY_GROW_SIZE 50

static char *hist_inittime PARAMS((void));
char history_comment_char;
/* **************************************************************** */
/*								    */
/*			History Functions			    */
/*								    */
/* **************************************************************** */

/* An array of HIST_ENTRY.  This is where we store the history. */
static HIST_ENTRY **the_history = (HIST_ENTRY **)NULL;

/* Non-zero means that we have enforced a limit on the amount of
   history that we save. */
static int history_stifled;

/* The current number of slots allocated to the input_history. */
static int history_size;

/* If HISTORY_STIFLED is non-zero, then this is the maximum number of
   entries to remember. */
int history_max_entries;
int max_input_history; /* backwards compatibility */

/* The current location of the interactive history pointer.  Just makes
   life easier for outside callers. */
int history_offset;

/* The number of strings currently stored in the history list. */
int history_length;

/* The logical `base' of the history array.  It defaults to 1. */
int history_base = 1;

/* Return the current HISTORY_STATE of the history. */
HISTORY_STATE *history_get_history_state()
{
	HISTORY_STATE *state;

	state = (HISTORY_STATE *)xmalloc(sizeof(HISTORY_STATE));
	state->entries = the_history;
	state->offset = history_offset;
	state->length = history_length;
	state->size = history_size;
	state->flags = 0;
	if (history_stifled)
		state->flags |= HS_STIFLED;

	return (state);
}

/* Set the state of the current history array to STATE. */
void history_set_history_state(state) HISTORY_STATE *state;
{
	the_history = state->entries;
	history_offset = state->offset;
	history_length = state->length;
	history_size = state->size;
	if (state->flags & HS_STIFLED)
		history_stifled = 1;
}

/* Begin a session in which the history functions might be used.  This
   initializes interactive variables. */
void using_history() { history_offset = history_length; }

/* Return the number of bytes that the primary history entries are using.
   This just adds up the lengths of the_history->lines and the associated
   timestamps. */
int history_total_bytes()
{
	register int i, result;

	for (i = result = 0; the_history && the_history[i]; i++)
		result += HISTENT_BYTES(the_history[i]);

	return (result);
}

/* Returns the magic number which says what history element we are
   looking at now.  In this implementation, it returns history_offset. */
int where_history() { return (history_offset); }

/* Make the current history item be the one at POS, an absolute index.
   Returns zero if POS is out of range, else non-zero. */
int history_set_pos(pos) int pos;
{
	if (pos > history_length || pos < 0 || !the_history)
		return (0);
	history_offset = pos;
	return (1);
}

/* Return the current history array.  The caller has to be careful, since this
   is the actual array of data, and could be bashed or made corrupt easily.
   The array is terminated with a NULL pointer. */
HIST_ENTRY **history_list() { return (the_history); }

/* Return the history entry at the current position, as determined by
   history_offset.  If there is no entry there, return a NULL pointer. */
HIST_ENTRY *current_history()
{
	return ((history_offset == history_length) || the_history == 0) ? (HIST_ENTRY *)NULL
									: the_history[history_offset];
}

/* Back up history_offset to the previous history entry, and return
   a pointer to that entry.  If there is no previous entry then return
   a NULL pointer. */
HIST_ENTRY *previous_history() { return history_offset ? the_history[--history_offset] : (HIST_ENTRY *)NULL; }

/* Move history_offset forward to the next history entry, and return
   a pointer to that entry.  If there is no next entry then return a
   NULL pointer. */
HIST_ENTRY *next_history()
{
	return (history_offset == history_length) ? (HIST_ENTRY *)NULL : the_history[++history_offset];
}

/* Return the history entry which is logically at OFFSET in the history array.
   OFFSET is relative to history_base. */
HIST_ENTRY *history_get(offset) int offset;
{
	int local_index;

	local_index = offset - history_base;
	return (local_index >= history_length || local_index < 0 || the_history == 0) ? (HIST_ENTRY *)NULL
										      : the_history[local_index];
}

HIST_ENTRY *alloc_history_entry(string, ts) char *string;
char *ts;
{
	HIST_ENTRY *temp;

	temp = (HIST_ENTRY *)xmalloc(sizeof(HIST_ENTRY));

	temp->line = string ? savestring(string) : string;
	temp->data = (char *)NULL;
	temp->timestamp = ts;

	return temp;
}

time_t history_get_time(hist) HIST_ENTRY *hist;
{
	char *ts;
	time_t t;

	if (hist == 0 || hist->timestamp == 0)
		return 0;
	ts = hist->timestamp;
	if (ts[0] != history_comment_char)
		return 0;
	errno = 0;
	t = (time_t)strtol(ts + 1, (char **)NULL, 10); /* XXX - should use strtol() here */
	if (errno == ERANGE)
		return (time_t)0;
	return t;
}

static char *hist_inittime()
{
	time_t t;
	char ts[64], *ret;

	t = (time_t)time((time_t *)0);
#if defined(HAVE_VSNPRINTF) /* assume snprintf if vsnprintf exists */
	snprintf(ts, sizeof(ts) - 1, "X%lu", (unsigned long)t);
#else
	sprintf(ts, "X%lu", (unsigned long)t);
#endif
	ret = savestring(ts);
	ret[0] = history_comment_char;

	return ret;
}

/* Place STRING at the end of the history list.  The data field
   is  set to NULL. */
void add_history(string) const char *string;
{
	HIST_ENTRY *temp;

	if (history_stifled && (history_length == history_max_entries))
	{
		register int i;

		/* If the history is stifled, and history_length is zero,
		and it equals history_max_entries, we don't save items. */
		if (history_length == 0)
			return;

		/* If there is something in the slot, then remove it. */
		if (the_history[0])
			(void)free_history_entry(the_history[0]);

			/* Copy the rest of the entries, moving down one slot.  Copy includes
			trailing NULL.  */
#if 0
		for (i = 0; i < history_length; i++)
			the_history[i] = the_history[i + 1];
#else
		memmove(the_history, the_history + 1, history_length * sizeof(HIST_ENTRY *));
#endif

		history_base++;
	}
	else
	{
		if (history_size == 0)
		{
			if (history_stifled && history_max_entries > 0)
				history_size = history_max_entries + 2;
			else
				history_size = DEFAULT_HISTORY_INITIAL_SIZE;
			the_history = (HIST_ENTRY **)xmalloc(history_size * sizeof(HIST_ENTRY *));
			history_length = 1;
		}
		else
		{
			if (history_length == (history_size - 1))
			{
				history_size += DEFAULT_HISTORY_GROW_SIZE;
				the_history = (HIST_ENTRY **)xrealloc(the_history, history_size * sizeof(HIST_ENTRY *));
			}
			history_length++;
		}
	}

	temp = alloc_history_entry((char *)string, hist_inittime());

	the_history[history_length] = (HIST_ENTRY *)NULL;
	the_history[history_length - 1] = temp;
}

/* Change the time stamp of the most recent history entry to STRING. */
void add_history_time(string) const char *string;
{
	HIST_ENTRY *hs;

	if (string == 0 || history_length < 1)
		return;
	hs = the_history[history_length - 1];
	FREE(hs->timestamp);
	hs->timestamp = savestring(string);
}

/* Free HIST and return the data so the calling application can free it
   if necessary and desired. */
histdata_t free_history_entry(hist) HIST_ENTRY *hist;
{
	histdata_t x;

	if (hist == 0)
		return ((histdata_t)0);
	FREE(hist->line);
	FREE(hist->timestamp);
	x = hist->data;
	xfree(hist);
	return (x);
}

HIST_ENTRY *copy_history_entry(hist) HIST_ENTRY *hist;
{
	HIST_ENTRY *ret;
	char *ts;

	if (hist == 0)
		return hist;

	ret = alloc_history_entry(hist->line, (char *)NULL);

	ts = hist->timestamp ? savestring(hist->timestamp) : hist->timestamp;
	ret->timestamp = ts;

	ret->data = hist->data;

	return ret;
}

/* Make the history entry at WHICH have LINE and DATA.  This returns
   the old entry so you can dispose of the data.  In the case of an
   invalid WHICH, a NULL pointer is returned. */
HIST_ENTRY *replace_history_entry(which, line, data) int which;
const char *line;
histdata_t data;
{
	HIST_ENTRY *temp, *old_value;

	if (which < 0 || which >= history_length)
		return ((HIST_ENTRY *)NULL);

	temp = (HIST_ENTRY *)xmalloc(sizeof(HIST_ENTRY));
	old_value = the_history[which];

	temp->line = savestring(line);
	temp->data = data;
	temp->timestamp = savestring(old_value->timestamp);
	the_history[which] = temp;

	return (old_value);
}

/* Append LINE to the history line at offset WHICH, adding a newline to the
   end of the current line first.  This can be used to construct multi-line
   history entries while reading lines from the history file. */
void _hs_append_history_line(which, line) int which;
const char *line;
{
	HIST_ENTRY *hent;
	size_t newlen, curlen;
	char *newline;

	hent = the_history[which];
	curlen = strlen(hent->line);
	newlen = curlen + strlen(line) + 2;
	newline = realloc(hent->line, newlen);
	if (newline)
	{
		hent->line = newline;
		hent->line[curlen++] = '\n';
		strcpy(hent->line + curlen, line);
	}
}

/* Replace the DATA in the specified history entries, replacing OLD with
   NEW.  WHICH says which one(s) to replace:  WHICH == -1 means to replace
   all of the history entries where entry->data == OLD; WHICH == -2 means
   to replace the `newest' history entry where entry->data == OLD; and
   WHICH >= 0 means to replace that particular history entry's data, as
   long as it matches OLD. */
void _hs_replace_history_data(which, old, new) int which;
histdata_t *old, *new;
{
	HIST_ENTRY *entry;
	register int i, last;

	if (which < -2 || which >= history_length || history_length == 0 || the_history == 0)
		return;

	if (which >= 0)
	{
		entry = the_history[which];
		if (entry && entry->data == old)
			entry->data = new;
		return;
	}

	last = -1;
	for (i = 0; i < history_length; i++)
	{
		entry = the_history[i];
		if (entry == 0)
			continue;
		if (entry->data == old)
		{
			last = i;
			if (which == -1)
				entry->data = new;
		}
	}
	if (which == -2 && last >= 0)
	{
		entry = the_history[last];
		entry->data = new; /* XXX - we don't check entry->old */
	}
}

/* Remove history element WHICH from the history.  The removed
   element is returned to you so you can free the line, data,
   and containing structure. */
HIST_ENTRY *remove_history(which) int which;
{
	HIST_ENTRY *return_value;
	register int i;

	if (which < 0 || which >= history_length || history_length == 0 || the_history == 0)
		return ((HIST_ENTRY *)NULL);

	return_value = the_history[which];

	for (i = which; i < history_length; i++)
		the_history[i] = the_history[i + 1];

	history_length--;

	return (return_value);
}

/* Stifle the history list, remembering only MAX number of lines. */
void stifle_history(max) int max;
{
	register int i, j;

	if (max < 0)
		max = 0;

	if (history_length > max)
	{
		/* This loses because we cannot free the data. */
		for (i = 0, j = history_length - max; i < j; i++)
			free_history_entry(the_history[i]);

		history_base = i;
		for (j = 0, i = history_length - max; j < max; i++, j++)
			the_history[j] = the_history[i];
		the_history[j] = (HIST_ENTRY *)NULL;
		history_length = j;
	}

	history_stifled = 1;
	max_input_history = history_max_entries = max;
}

/* Stop stifling the history.  This returns the previous maximum
   number of history entries.  The value is positive if the history
   was stifled, negative if it wasn't. */
int unstifle_history()
{
	if (history_stifled)
	{
		history_stifled = 0;
		return (history_max_entries);
	}
	else
		return (-history_max_entries);
}

int history_is_stifled() { return (history_stifled); }

void clear_history()
{
	register int i;

	/* This loses because we cannot free the data. */
	for (i = 0; i < history_length; i++)
	{
		free_history_entry(the_history[i]);
		the_history[i] = (HIST_ENTRY *)NULL;
	}

	history_offset = history_length = 0;
}
/* xmalloc.c -- safe versions of malloc, realloc and free*/

/* **************************************************************** */
/*								    */
/*		   Memory Allocation and Deallocation.		    */
/*								    */
/* **************************************************************** */

static void memory_error_and_abort(fname) char *fname;
{
	fprintf(stderr, "%s: out of virtual memory\n", fname);
	exit(2);
}

/* Return a pointer to free()able block of memory large enough
   to hold BYTES number of bytes.  If the memory cannot be allocated,
   print an error message and abort. */
PTR_T
xmalloc(bytes) size_t bytes;
{
	PTR_T temp;

	temp = malloc(bytes);
	if (temp == 0)
		memory_error_and_abort("xmalloc");
	return (temp);
}

PTR_T
xrealloc(pointer, bytes) PTR_T pointer;
size_t bytes;
{
	PTR_T temp;

	temp = pointer ? realloc(pointer, bytes) : malloc(bytes);

	if (temp == 0)
		memory_error_and_abort("xrealloc");
	return (temp);
}

/* **************************************************************** */
/*								    */
/*		   Memory Deallocation.				    */
/*								    */
/* **************************************************************** */

/* Use this as the function to call when adding unwind protects so we
   don't need to know what free() returns. */
void xfree(string) PTR_T string;
{
	if (string)
		free(string);
}
