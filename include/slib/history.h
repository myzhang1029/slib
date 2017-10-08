/* history.h -- the names of functions that you can call in history. */

/* Copyright (C) 1989-2015 Free Software Foundation, Inc.
   Cpoyright (C) 2017 Zhang Maiyun

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

#ifndef _HISTORY_H_
#define _HISTORY_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <time.h>		/* XXX - for history timestamp code */

/* stdc.h -- macros to make source compile on both ANSI C and K&R C compilers. */

/* Adapted from BSD /usr/include/sys/cdefs.h. */

/* A function can be defined using prototypes and compile on both ANSI C
   and traditional C compilers with something like this:
	extern char *func PARAMS((char *, char *, int)); */
#if !defined (_RL_STDC_H_)
#define _RL_STDC_H_

#if !defined (PARAMS)
#  if defined (__STDC__) || defined (__GNUC__) || defined (__cplusplus)
#    define PARAMS(protos) protos
#  else
#    define PARAMS(protos) ()
#  endif
#endif

#ifndef __attribute__
#  if __GNUC__ < 2 || (__GNUC__ == 2 && __GNUC_MINOR__ < 8)
#    define __attribute__(x)
#  endif
#endif

/* Moved from config.h.in because readline.h:rl_message depends on these
   defines. */
#if defined (__STDC__) && defined (HAVE_STDARG_H)
#  define PREFER_STDARG
#  define USE_VARARGS
#else
#  if defined (HAVE_VARARGS_H)
#    define PREFER_VARARGS
#    define USE_VARARGS
#  endif
#endif
#endif /* !_RL_STDC_H_ */
/* End rlstdc.h */

/* rltypedefs.h -- Type declarations for readline functions. */

#ifndef _RL_TYPEDEFS_H_
#define _RL_TYPEDEFS_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Old-style, attempt to mark as deprecated in some way people will notice. */

#if !defined (_FUNCTION_DEF)
#  define _FUNCTION_DEF

#if defined(__GNUC__) || defined(__clang__)
typedef int Function () __attribute__ ((deprecated));
typedef void VFunction () __attribute__ ((deprecated));
typedef char *CPFunction () __attribute__ ((deprecated));
typedef char **CPPFunction () __attribute__ ((deprecated));
#else
typedef int Function ();
typedef void VFunction ();
typedef char *CPFunction ();
typedef char **CPPFunction ();
#endif

#endif /* _FUNCTION_DEF */

/* New style. */

#if !defined (_RL_FUNCTION_TYPEDEF)
#  define _RL_FUNCTION_TYPEDEF

/* Bindable functions */
typedef int rl_command_func_t PARAMS((int, int));

/* Typedefs for the completion system */
typedef char *rl_compentry_func_t PARAMS((const char *, int));
typedef char **rl_completion_func_t PARAMS((const char *, int, int));

typedef char *rl_quote_func_t PARAMS((char *, int, char *));
typedef char *rl_dequote_func_t PARAMS((char *, int));

typedef int rl_compignore_func_t PARAMS((char **));

typedef void rl_compdisp_func_t PARAMS((char **, int, int));

/* Type for input and pre-read hook functions like rl_event_hook */
typedef int rl_hook_func_t PARAMS((void));

/* Input function type */
typedef int rl_getc_func_t PARAMS((FILE *));

/* Generic function that takes a character buffer (which could be the readline
   line buffer) and an index into it (which could be rl_point) and returns
   an int. */
typedef int rl_linebuf_func_t PARAMS((char *, int));

/* `Generic' function pointer typedefs */
typedef int rl_intfunc_t PARAMS((int));
#define rl_ivoidfunc_t rl_hook_func_t
typedef int rl_icpfunc_t PARAMS((char *));
typedef int rl_icppfunc_t PARAMS((char **));

typedef void rl_voidfunc_t PARAMS((void));
typedef void rl_vintfunc_t PARAMS((int));
typedef void rl_vcpfunc_t PARAMS((char *));
typedef void rl_vcppfunc_t PARAMS((char **));

typedef char *rl_cpvfunc_t PARAMS((void));
typedef char *rl_cpifunc_t PARAMS((int));
typedef char *rl_cpcpfunc_t PARAMS((char  *));
typedef char *rl_cpcppfunc_t PARAMS((char  **));

#endif /* _RL_FUNCTION_TYPEDEF */

#ifdef __cplusplus
}
#endif
#endif /* _RL_TYPEDEFS_H_ */
/* End rltypedefs.h */

#ifdef __STDC__
typedef void *histdata_t;
#else
typedef char *histdata_t;
#endif

/* The structure used to store a history entry. */
typedef struct _hist_entry {
  char *line;
  char *timestamp;		/* char * rather than time_t for read/write */
  histdata_t data;
} HIST_ENTRY;

/* Size of the history-library-managed space in history entry HS. */
#define HISTENT_BYTES(hs)	(strlen ((hs)->line) + strlen ((hs)->timestamp))

/* A structure used to pass the current state of the history stuff around. */
typedef struct _hist_state {
  HIST_ENTRY **entries;		/* Pointer to the entries themselves. */
  int offset;			/* The location pointer within this array. */
  int length;			/* Number of elements within this array. */
  int size;			/* Number of slots allocated to this array. */
  int flags;
} HISTORY_STATE;

/* Flag values for the `flags' member of HISTORY_STATE. */
#define HS_STIFLED	0x01

/* Initialization and state management. */

/* Begin a session in which the history functions might be used.  This
   just initializes the interactive variables. */
extern void using_history PARAMS((void));

/* Return the current HISTORY_STATE of the history. */
extern HISTORY_STATE *history_get_history_state PARAMS((void));

/* Set the state of the current history array to STATE. */
extern void history_set_history_state PARAMS((HISTORY_STATE *));

/* Manage the history list. */

/* Place STRING at the end of the history list.
   The associated data field (if any) is set to NULL. */
extern void add_history PARAMS((const char *));

/* Change the timestamp associated with the most recent history entry to
   STRING. */
extern void add_history_time PARAMS((const char *));

/* A reasonably useless function, only here for completeness.  WHICH
   is the magic number that tells us which element to delete.  The
   elements are numbered from 0. */
extern HIST_ENTRY *remove_history PARAMS((int));

/* Allocate a history entry consisting of STRING and TIMESTAMP and return
   a pointer to it. */
extern HIST_ENTRY *alloc_history_entry PARAMS((char *, char *));

/* Copy the history entry H, but not the (opaque) data pointer */
extern HIST_ENTRY *copy_history_entry PARAMS((HIST_ENTRY *));

/* Free the history entry H and return any application-specific data
   associated with it. */
extern histdata_t free_history_entry PARAMS((HIST_ENTRY *));

/* Make the history entry at WHICH have LINE and DATA.  This returns
   the old entry so you can dispose of the data.  In the case of an
   invalid WHICH, a NULL pointer is returned. */
extern HIST_ENTRY *replace_history_entry PARAMS((int, const char *, histdata_t));

/* Clear the history list and start over. */
extern void clear_history PARAMS((void));

/* Stifle the history list, remembering only MAX number of entries. */
extern void stifle_history PARAMS((int));

/* Stop stifling the history.  This returns the previous amount the
   history was stifled by.  The value is positive if the history was
   stifled, negative if it wasn't. */
extern int unstifle_history PARAMS((void));

/* Return 1 if the history is stifled, 0 if it is not. */
extern int history_is_stifled PARAMS((void));

/* Information about the history list. */

/* Return a NULL terminated array of HIST_ENTRY which is the current input
   history.  Element 0 of this list is the beginning of time.  If there
   is no history, return NULL. */
extern HIST_ENTRY **history_list PARAMS((void));

/* Returns the number which says what history element we are now
   looking at.  */
extern int where_history PARAMS((void));
  
/* Return the history entry at the current position, as determined by
   history_offset.  If there is no entry there, return a NULL pointer. */
extern HIST_ENTRY *current_history PARAMS((void));

/* Return the history entry which is logically at OFFSET in the history
   array.  OFFSET is relative to history_base. */
extern HIST_ENTRY *history_get PARAMS((int));

/* Return the timestamp associated with the HIST_ENTRY * passed as an
   argument */
extern time_t history_get_time PARAMS((HIST_ENTRY *));

/* Return the number of bytes that the primary history entries are using.
   This just adds up the lengths of the_history->lines. */
extern int history_total_bytes PARAMS((void));

/* Moving around the history list. */

/* Set the position in the history list to POS. */
extern int history_set_pos PARAMS((int));

/* Back up history_offset to the previous history entry, and return
   a pointer to that entry.  If there is no previous entry, return
   a NULL pointer. */
extern HIST_ENTRY *previous_history PARAMS((void));

/* Move history_offset forward to the next item in the input_history,
   and return the a pointer to that entry.  If there is no next entry,
   return a NULL pointer. */
extern HIST_ENTRY *next_history PARAMS((void));

/* Searching the history list. */

/* Search the history for STRING, starting at history_offset.
   If DIRECTION < 0, then the search is through previous entries,
   else through subsequent.  If the string is found, then
   current_history () is the history entry, and the value of this function
   is the offset in the line of that history entry that the string was
   found in.  Otherwise, nothing is changed, and a -1 is returned. */
extern int history_search PARAMS((const char *, int));

/* Search the history for STRING, starting at history_offset.
   The search is anchored: matching lines must begin with string.
   DIRECTION is as in history_search(). */
extern int history_search_prefix PARAMS((const char *, int));

/* Search for STRING in the history list, starting at POS, an
   absolute index into the list.  DIR, if negative, says to search
   backwards from POS, else forwards.
   Returns the absolute index of the history element where STRING
   was found, or -1 otherwise. */
extern int history_search_pos PARAMS((const char *, int, int));

/* Managing the history file. */

/* Add the contents of FILENAME to the history list, a line at a time.
   If FILENAME is NULL, then read from ~/.history.  Returns 0 if
   successful, or errno if not. */
extern int read_history PARAMS((const char *));

/* Read a range of lines from FILENAME, adding them to the history list.
   Start reading at the FROM'th line and end at the TO'th.  If FROM
   is zero, start at the beginning.  If TO is less than FROM, read
   until the end of the file.  If FILENAME is NULL, then read from
   ~/.history.  Returns 0 if successful, or errno if not. */
extern int read_history_range PARAMS((const char *, int, int));

/* Write the current history to FILENAME.  If FILENAME is NULL,
   then write the history list to ~/.history.  Values returned
   are as in read_history ().  */
extern int write_history PARAMS((const char *));

/* Append NELEMENT entries to FILENAME.  The entries appended are from
   the end of the list minus NELEMENTs up to the end of the list. */
extern int append_history PARAMS((int, const char *));

/* Truncate the history file, leaving only the last NLINES lines. */
extern int history_truncate_file PARAMS((const char *, int));

/* History expansion. */

/* Expand the string STRING, placing the result into OUTPUT, a pointer
   to a string.  Returns:

   0) If no expansions took place (or, if the only change in
      the text was the de-slashifying of the history expansion
      character)
   1) If expansions did take place
  -1) If there was an error in expansion.
   2) If the returned line should just be printed.

  If an error occurred in expansion, then OUTPUT contains a descriptive
  error message. */
extern int history_expand PARAMS((char *, char **));

/* Extract a string segment consisting of the FIRST through LAST
   arguments present in STRING.  Arguments are broken up as in
   the shell. */
extern char *history_arg_extract PARAMS((int, int, const char *));

/* Return the text of the history event beginning at the current
   offset into STRING.  Pass STRING with *INDEX equal to the
   history_expansion_char that begins this specification.
   DELIMITING_QUOTE is a character that is allowed to end the string
   specification for what to search for in addition to the normal
   characters `:', ` ', `\t', `\n', and sometimes `?'. */
extern char *get_history_event PARAMS((const char *, int *, int));

/* Return an array of tokens, much as the shell might.  The tokens are
   parsed out of STRING. */
extern char **history_tokenize PARAMS((const char *));

/* Exported history variables. */
extern int history_base;
extern int history_length;
extern int history_max_entries;
extern int history_offset;

extern int history_lines_read_from_file;
extern int history_lines_written_to_file;

extern char history_expansion_char;
extern char history_subst_char;
extern char *history_word_delimiters;
extern char history_comment_char;
extern char *history_no_expand_chars;
extern char *history_search_delimiter_chars;
extern int history_quotes_inhibit_expansion;

extern int history_write_timestamps;

/* These two are undocumented; the second is reserved for future use */
extern int history_multiline_entries;
extern int history_file_version;

/* Backwards compatibility */
extern int max_input_history;

/* If set, this function is called to decide whether or not a particular
   history expansion should be treated as a special case for the calling
   application and not expanded. */
extern rl_linebuf_func_t *history_inhibit_expansion_function;

#ifdef __cplusplus
}
#endif

#endif /* !_HISTORY_H_ */

/* histlib.h -- internal definitions for the history library. */

#if !defined (_HISTLIB_H_)
#define _HISTLIB_H_

#if defined (HAVE_STRING_H)
#  include <string.h>
#else
#  include <strings.h>
#endif /* !HAVE_STRING_H */

#if !defined (STREQ)
#define STREQ(a, b)	(((a)[0] == (b)[0]) && (strcmp ((a), (b)) == 0))
#define STREQN(a, b, n) (((n) == 0) ? (1) \
				    : ((a)[0] == (b)[0]) && (strncmp ((a), (b), (n)) == 0))
#endif

#ifndef savestring
#define savestring(x) strcpy (xmalloc (1 + strlen (x)), (x))
#endif

#ifndef whitespace
#define whitespace(c) (((c) == ' ') || ((c) == '\t'))
#endif

#ifndef _rl_digit_p
#define _rl_digit_p(c)  ((c) >= '0' && (c) <= '9')
#endif

#ifndef _rl_digit_value
#define _rl_digit_value(c) ((c) - '0')
#endif

#ifndef member
#  ifndef strchr
extern char *strchr ();
#  endif
#define member(c, s) ((c) ? ((char *)strchr ((s), (c)) != (char *)NULL) : 0)
#endif

#ifndef FREE
#  define FREE(x)	if (x) free (x)
#endif

/* Possible history errors passed to hist_error. */
#define EVENT_NOT_FOUND 0
#define BAD_WORD_SPEC	1
#define SUBST_FAILED	2
#define BAD_MODIFIER	3
#define NO_PREV_SUBST	4

/* Possible definitions for history starting point specification. */
#define ANCHORED_SEARCH 1
#define NON_ANCHORED_SEARCH 0

/* Possible definitions for what style of writing the history file we want. */
#define HISTORY_APPEND 0
#define HISTORY_OVERWRITE 1

#endif /* !_HISTLIB_H_ */
/* End histlib.h */

/* xmalloc.h -- memory allocation that aborts on errors. */

#if !defined (_XMALLOC_H_)
#define _XMALLOC_H_

#ifndef PTR_T

#ifdef __STDC__
#  define PTR_T	void *
#else
#  define PTR_T	char *
#endif

#endif /* !PTR_T */

extern PTR_T xmalloc(size_t);
extern PTR_T xrealloc(void *, size_t);
extern void xfree(void *);

#endif /* _XMALLOC_H_ */
/* End xmalloc.h */
