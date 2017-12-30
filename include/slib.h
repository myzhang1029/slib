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

#if defined (_MSC_VER)&&_MSC_VER>=100
#pragma once
#endif

#ifndef SBLLIB_VERSION
#define SBLLIB_VERSION 3

#define SBLLIB_MINOR 3
#define SBLLIB_PATCHLEVEL 10

#ifdef HAVE_CONFIG_H
#include "config.h"
#undef malloc
#undef realloc
#endif

#include <stdio.h>
#include <errno.h>

#if !defined(PLAT)
# if defined(_MSC_VER)||defined(__MINGW32__)||defined(_WIN16)||defined(_WIN32)||defined(_WIN64)||defined(__MSDOS__)
#  define PLAT 1
# elif defined(__linux__)||defined(__BSD__)|defined(__APPLE__)||defined(__unix__)
#  define PLAT 0
# else
#  error Please define PLAT, see documentation for more details
# endif
#endif 

#if PLAT
#include <windows.h>
#endif

#ifndef _CRT_SECURE_NO_WARNINGS /*for MSVC compiling envirment*/
#define _CRT_SECURE_NO_WARNINGS
#endif
#undef _CRT_NONSTDC_NO_WARNINGS

#ifndef NULL /*give default definition for NULL*/
#define NULL (void*)0
#endif

#ifndef __set_errno
#define __set_errno(x) errno=x
#endif

#define STRUE 1 /*status*/
#define SFALSE 0
#define SERROR -1
#define STKELMT 100 /*Stack max. element count*/ 
#define BUFFERSIZE 100  /*Stack buffer size*/


#if PLAT
#define OPT extern __declspec(dllexport) /*use in declartions*/
#else
#define OPT extern
#endif

/*BOOL*/
#if (!defined(HAVE_BOOL)||defined(__STDC_VERSION__)||__STDC_VERSION__<199901L||!defined(__GNUC__)||__GNUC__<5)
typedef enum boolS
{
true=1,
false=0
}boolS;
#define bool boolS
#define _Bool boolS
#endif

#define S_INLINE inline

#define mtreturn(lenth,...) return mkret(lenth,__VA_ARGS__)

/*debugger*/
#define D_STABLE 
#define D_UNSTABLE
#define D_TESTING

#ifdef __cplusplus
#define _BEGIN_EXTERN_C extern "C"{
#define _END_EXTERN_C }
#else
#define _BEGIN_EXTERN_C
#define _END_EXTERN_C
#endif

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

_BEGIN_EXTERN_C

/*External variables*/
extern  unsigned retind;

/*Structures, Enums, Unions, typedefs*/
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
	green,
	yellow,
	black,
	blue,
	magenta,
	cyan,
	unchanged
};

typedef const char * const ccp;


typedef char * String;


typedef unsigned count_t;

/*declation start*/
OPT int InitStack(sqStack *s,unsigned stackSize,unsigned typeSize);


OPT int  Push(sqStack *s,void *e); 


OPT int  Pop(sqStack *s,void *e); 


OPT int  ClearStack(sqStack *s); 


OPT int  DestroyStack(sqStack *s); 


OPT int  GetLen(sqStack *s); 


OPT int  prterr(ccp fmt,...);


OPT double  calculate( ccp infix );


OPT long  fsize( FILE * stream );	/*获取文件长度*/


OPT int  mysh( ccp path );	/*自定义shell程序*/


D_UNSTABLE OPT int  fcopy( ccp oldname, ccp newname );      /*文件复制函数*/


OPT void  prtpn( FILE *fp, unsigned long minimum, unsigned long maximum );	/*输出指定范围内的质数*/


OPT int  ispn( unsigned long testingnum );


OPT unsigned long  randomnum( unsigned seed,unsigned long maximum,unsigned long minimum );


OPT int  isrp(unsigned n1,unsigned n2);


OPT char *  mtscat(unsigned amount,...);


D_UNSTABLE OPT int  iofile(FILE  *origin,FILE *dest);


OPT int  prtfile(FILE *stream);


OPT double  average(size_t amt,...);


OPT unsigned long gcf(unsigned long n1,unsigned long n2);


OPT unsigned long lcm(unsigned long n1,unsigned long n2);


OPT int  eular(unsigned n);


OPT void splitpathS(const char *path, char *drive, char *dir, char *fname, char *ext);


OPT unsigned long  wsbl_frame(int ch);


OPT int  rsbl_frame(int code);


OPT char* itoaS(int value, char* string, int radix);
	
	
OPT char* ltoaS(long value, char* string, int radix);
	
	
OPT char* ultoaS(unsigned long value, char* string, int radix);


D_TESTING OPT int colorprintf(enum cpfcolors fcolor,enum cpfcolors bcolor,ccp format,...);
	

OPT int *getret(mtret ret);


OPT mtret mkret(size_t lenth,...);


OPT void sleepS(int seconds);


#if ! PLAT
OPT int getch(void);
OPT int kbhit(void);
#endif

_END_EXTERN_C

#endif/*SBLLIB_VERSION*/
