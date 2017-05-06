/*
 *  slib.h - This is the header file of the slib
 *
 *  Copyright (C) 2016, 2017 Zhang Maiyun
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


//#pragma once


#ifndef SBLLIB_VERSION
#define SBLLIB_VERSION 2.3.2

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <math.h>
#include <time.h>
#include <stdarg.h>
#include <assert.h>
#include <ctype.h>


#if PLAT
#include <windows.h>
#else
#include <termios.h>
#include <unistd.h>
#endif

#ifndef _CRT_SECURE_NO_WARNINGS //for MSVC compiling envirment
#define _CRT_SECURE_NO_WARNINGS
#endif
#undef _CRT_NONSTDC_NO_WARINGS

#ifndef NULL //give default definition for NULL
#define NULL (void*)0
#endif

#ifndef __set_errno
#define __set_errno(x) errno=x
#endif

#define STRUE 1 //status
#define SFALSE 0
#define SERROR -1
#define STKELMT 100 //Stack max. element count 
#define BUFFERSIZE 100  //Stack buffer size

#define _INTSZOF(n)   ( (sizeof(n) + sizeof(int) - 1) & ~(sizeof(int) - 1) )//a copy of stdarg.h
#define vstart(ap,v)  ( ap = (vlist)&v + _INTSZOF(v) )
#define varg(ap,t)    ( *(t *)((ap += _INTSZOF(t)) - _INTSZOF(t)) )
#define vend(ap)      ( ap = (vlist)0 )

#if PLAT
#define OPT __declspec(dllexport) //use in declartions
#else
#define OPT
#endif


#define S_INLINE inline

//serr
#define serr (*_serrloc())
#define SERR_LIBCALLFAILED 1
#define SERR_INPUTINVAL 2
#define SERR_STACKERR 3

//seperator of file pathes
#if PLAT
#define pathsep '\\'
#else
#define pathsep '/'
#endif

#define mtreturn(lenth,...) return mkret(lenth,__VA_ARGS__)

//debugger
#define D_STABLE 
#define D_UNSTABLE
#define D_TESTING

#ifndef __cplusplus //a copy of stdbool.h
#define bool	_Bool
#define true	1
#define false	0
#else /* __cplusplus */
#define _Bool	bool
#define bool	bool
#define false	false
#define true	true
#endif /* __cplusplus */

#if PLAT
#define FOREGROUND_WHITE FOREGROUND_RED|FOREGROUND_BLUE|FOREGROUND_GREEN 
#define msgloop \
{ \
	MSG msg; \
	while(GetMessage(&msg,NULL,0,0)) \
	{ \
		TranslateMessage(&msg); \
		DispatchMessage(&msg); \
	} \
} 

#define regwndcls(style,lpfnwndproc,cbextra,cbwndextra,hinstsnce,hicon,hcursor,hbrbackground,lpsenuname,lpszclsname)\
 { \
	WNDCLASS wndcls; \
	wndcls.cbClsExtra=(cbextra); \
	wndcls.cbWndExtra=(cbwndextra); \
	wndcls.hbrBackground=(hbrbackgrpund);\
	wndcls.hCursor=(hcursor); \
	wndcls.hIcon=(hicon); \
	wndcls.hInstance=(hinstance); \
	wndcls.lpfnWndProc=(lpfnwndproc); \
	wndcls.lpszClassName=(lpszclsname); \
	wndcls.lpszMenuName=(lpszmenuname); \
	wndcls.style=(style); \
	RegisterClass(&wndcls); \
}
#endif

#ifdef __cplusplus
extern "C"{
#endif

typedef struct Stack
{
	void *base;
	void *top;
	int stackSize;
	int typeSize;
} sqStack;

typedef struct mtrt
{
	size_t lenth;
	int **val;
}mtret;


enum cpfcolors
{
	red=1,
	green=2,
	yellow=3,
	black=4,
	blue=5,
	purple=6,
};


typedef const unsigned int cui;//type aliases

typedef const char * const ccp;

typedef const unsigned long cul;

typedef char * vlist;

typedef unsigned int usint;

typedef unsigned long uslong;

typedef unsigned char uschar;
	
typedef char * String;

//declation start
OPT int InitStack(sqStack *s,unsigned stackSize,unsigned typeSize);


OPT int  Push(sqStack *s,void *e); 


OPT int  Pop(sqStack *s,void *e); 


OPT int  ClearStack(sqStack *s); 


OPT int  DestroyStack(sqStack *s); 


OPT int  GetLen(sqStack *s); 


OPT int  prterr(ccp fmt,...);//自定义错误处理函数


OPT double  calculate( ccp infix );


OPT long  fsize( FILE * stream );	/*获取文件长度*/


OPT int  mysh( ccp path );	/*自定义shell程序*/


D_UNSTABLE OPT int  fcopy( ccp oldname, ccp newname );      /*文件复制函数*/


OPT int  prtpn( FILE *fp, cul minimum, cul maximum );	/*输出指定范围内的质数*/


OPT int  ispn( cul testingnum );


OPT long  randomnum( cui seed,cul maximum,cul minimum );


OPT int  isrp(cul n1,cul n2);


OPT char *  mtscat(cui amount,...);


D_UNSTABLE OPT int  iofile(FILE  *origin,FILE *dest);


OPT int  prtfile(FILE *stream);


OPT double  average(cui amt,...);


OPT int  gcf(cui n1,cui n2);


OPT int  lcm(cui n1,cui n2);


OPT int  eular(cui n);


D_TESTING OPT int getmname(ccp fullpath,char *mname);


D_TESTING OPT int getmpath(ccp fullpath,char *mpath);


OPT uslong  wsbl_frame(int ch);


OPT int  rsbl_frame(int code);


OPT int *  _serrloc( void );


OPT char* itoaS(int value, char* string, int radix);
	
	
OPT char* ltoaS(long value, char* string, int radix);
	
	
OPT char* ultoaS(unsigned long value, char* string, int radix);


D_TESTING OPT int colorprintf(enum cpfcolors fcolor,ccp format,...);
	

OPT int *getret(mtret ret);


OPT mtret mkret(size_t lenth,...);

#if ! PLAT
OPT int getch(void);
#endif

#ifdef __cplusplus
}
#endif
#endif/*SBLLIB_VERSION*/
/*start getopt*/
/* Declarations for getopt.
   Copyright (C) 1989-2014 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */

#ifndef _GETOPT_H

#ifndef __need_getopt
# define _GETOPT_H 1
#endif

/* If __GNU_LIBRARY__ is not already defined, either we are being used
   standalone, or this is the first header included in the source file.
   If we are being used with glibc, we need to include <features.h>, but
   that does not exist if we are standalone.  So: if __GNU_LIBRARY__ is
   not defined, include <ctype.h>, which will pull in <features.h> for us
   if it's from glibc.  (Why ctype.h?  It's guaranteed to exist and it
   doesn't flood the namespace with stuff the way some other headers do.)  */
#if !defined __GNU_LIBRARY__
# include <ctype.h>
#endif

#ifndef __THROW
# ifndef __GNUC_PREREQ
#  define __GNUC_PREREQ(maj, min) (0)
# endif
# if defined __cplusplus && __GNUC_PREREQ (2,8)
#  define __THROW	throw ()
# else
#  define __THROW
# endif
#endif

#ifdef	__cplusplus
extern "C" {
#endif

/* For communication from `getopt' to the caller.
   When `getopt' finds an option that takes an argument,
   the argument value is returned here.
   Also, when `ordering' is RETURN_IN_ORDER,
   each non-option ARGV-element is returned here.  */

extern char *optarg;

/* Index in ARGV of the next element to be scanned.
   This is used for communication to and from the caller
   and for communication between successive calls to `getopt'.

   On entry to `getopt', zero means this is the first call; initialize.

   When `getopt' returns -1, this is the index of the first of the
   non-option elements that the caller should itself scan.

   Otherwise, `optind' communicates from one call to the next
   how much of ARGV has been scanned so far.  */

extern int optind;

/* Callers store zero here to inhibit the error message `getopt' prints
   for unrecognized options.  */

extern int opterr;

/* Set to an option character which was unrecognized.  */

extern int optopt;

#ifndef __need_getopt
/* Describe the long-named options requested by the application.
   The LONG_OPTIONS argument to getopt_long or getopt_long_only is a vector
   of `struct option' terminated by an element containing a name which is
   zero.

   The field `has_arg' is:
   no_argument		(or 0) if the option does not take an argument,
   required_argument	(or 1) if the option requires an argument,
   optional_argument 	(or 2) if the option takes an optional argument.

   If the field `flag' is not NULL, it points to a variable that is set
   to the value given in the field `val' when the option is found, but
   left unchanged if the option is not found.

   To have a long-named option do something other than set an `int' to
   a compiled-in constant, such as set a value from `optarg', set the
   option's `flag' field to zero and its `val' field to a nonzero
   value (the equivalent single-letter option character, if there is
   one).  For long options that have a zero `flag' field, `getopt'
   returns the contents of the `val' field.  */

struct option
{
  const char *name;
  /* has_arg can't be an enum because some compilers complain about
     type mismatches in all the code that assumes it is an int.  */
  int has_arg;
  int *flag;
  int val;
};

/* Names for the values of the `has_arg' field of `struct option'.  */

# define no_argument		0
# define required_argument	1
# define optional_argument	2
#endif	/* need getopt */


/* Get definitions and prototypes for functions to process the
   arguments in ARGV (ARGC of them, minus the program name) for
   options given in OPTS.

   Return the option character from OPTS just read.  Return -1 when
   there are no more options.  For unrecognized options, or options
   missing arguments, `optopt' is set to the option letter, and '?' is
   returned.

   The OPTS string is a list of characters which are recognized option
   letters, optionally followed by colons, specifying that that letter
   takes an argument, to be placed in `optarg'.

   If a letter in OPTS is followed by two colons, its argument is
   optional.  This behavior is specific to the GNU `getopt'.

   The argument `--' causes premature termination of argument
   scanning, explicitly telling `getopt' that there are no more
   options.

   If OPTS begins with `--', then non-option arguments are treated as
   arguments to the option '\0'.  This behavior is specific to the GNU
   `getopt'.  */

#ifdef __GNU_LIBRARY__
/* Many other libraries have conflicting prototypes for getopt, with
   differences in the consts, in stdlib.h.  To avoid compilation
   errors, only prototype getopt for the GNU C library.  */
extern int getopt (int ___argc, char *const *___argv, const char *__shortopts)
       __THROW;

# if defined __need_getopt && defined __USE_POSIX2 \
  && !defined __USE_POSIX_IMPLICITLY && !defined __USE_GNU
/* The GNU getopt has more functionality than the standard version.  The
   additional functionality can be disable at runtime.  This redirection
   helps to also do this at runtime.  */
#  ifdef __REDIRECT
  extern int __REDIRECT_NTH (getopt, (int ___argc, char *const *___argv,
				      const char *__shortopts),
			     __posix_getopt);
#  else
extern int __posix_getopt (int ___argc, char *const *___argv,
			   const char *__shortopts) __THROW;
#   define getopt __posix_getopt
#  endif
# endif
#else /* not __GNU_LIBRARY__ */
extern int getopt ();
#endif /* __GNU_LIBRARY__ */

#ifndef __need_getopt
extern int getopt_long (int ___argc, char *const *___argv,
			const char *__shortopts,
		        const struct option *__longopts, int *__longind)
       __THROW;
extern int getopt_long_only (int ___argc, char *const *___argv,
			     const char *__shortopts,
		             const struct option *__longopts, int *__longind)
       __THROW;

#endif

#ifdef	__cplusplus
}
#endif

/* Make sure we later can get all the definitions and declarations.  */
#undef __need_getopt

#endif /* getopt.h */
