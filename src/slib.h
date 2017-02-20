/*
 *  slib.h - This is the header file of the slib
	 you can use on Linux & Windows platform
 *
 *  Copyright (C) 2016, 2017 Zhang Maiyun
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or (at
 *  your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful, but
 *  WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  General Public License for more details.
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

/*
 *WALNING :CHANGE THE DEFINITION 
 *OF "PLAT"(NEAR LINE 28)
 *TO 0 IF YOU ARE USING GNU/LINUX PLATFORM!!!!!!
 */
#pragma once
#ifndef SBLLIB_VERSION
#define SBLLIB_VERSION 15

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <math.h>
#include <time.h>
#include <stdarg.h>
#include <assert.h>
#include <ctype.h>

#define PLAT 1

#if PLAT
#include <windows.h>
#else
#include <termios.h>
#include <unistd.h>
#endif

#ifndef _CRT_SECURE_NO_WARNINGS //for MSVC compiling envirment
#define _CRT_SECURE_NO_WARNINGS
#endif

#ifdef _CRT_NONSTDC_NO_WARINGS
#undef _CRT_NONSTDC_NO_WARINGS
#endif

#ifndef NULL //give default definition for NULL
#define NULL (void*)0
#endif

#ifndef __set_errno
#define __set_errno(x) errno=x
#endif

#define STRUE 1 //status
#define SFALSE 0
#define SERROR -1
#define STKELMT 100 //堆栈中可入栈元素个数
#define BUFFERSIZE 100  //临时缓冲区大小

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
#define serr (*_serrloc())
#define SERR_LIBCALLFAILED 1
#define SERR_INPUTINVAL 2
#define SERR_STACKERR 3
#if PLAT
#define pathsep '\\'
#else
#define pathsep '/'
#endif
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

typedef struct Stack  //定义堆栈：堆栈中只定义栈大小和每次入栈元素大小，栈中一律使用空指针进行操作。这样，我们自己定义的栈就做到了和数据类型无关性。真正实现了栈的通用。
{
	void *base; //指向栈底
	void *top;  //指向栈顶
	int stackSize; //栈的空间总容量大小
	int typeSize; //入栈时，单个元素占用空间大小
} sqStack;

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


D_TESTING OPT int  Push(sqStack *s,void *e); //入栈


D_TESTING OPT int  Pop(sqStack *s,void *e); //出栈


D_TESTING OPT int  ClearStack(sqStack *s); //清空栈内所有元素


D_TESTING OPT int  DestroyStack(sqStack *s); //销毁栈


D_TESTING OPT int  GetLen(sqStack *s); //获取已入栈元素个数


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


OPT int getmname(ccp fullpath,char *mname);


OPT int getmpath(ccp fullpath,char *mpath);


OPT uslong  wsbl_frame(int ch);


OPT int  rsbl_frame(int code);


OPT int *  _serrloc( void );


OPT void *bsearchS (const void *key, const void *base, size_t nmemb, size_t size,
	 int (*compar) (const void *, const void *));
	

OPT char* itoaS(int value, char* string, int radix);
	
	
OPT char* ltoaS(long value, char* string, int radix);
	
	
OPT char* ultoaS(unsigned long value, char* string, int radix);
	
	
#if ! PLAT
OPT int getch(void);
#endif

#ifdef __cplusplus
}
#endif
#endif/*SBLLIB_VERSION*/
