/*
	2016,Zhang Maiyun
	This is the header file of
	SBL softwares
	can use on Linux & Windows platform
	include directly
	edit if need
*/

/***********************
*WALNING :CHANGE THE DEFINITION 
*OF "pathsep"(NEAR LINE 57)
*TO '/' IF YOU ARE USING 
*GNU/LINUX PLATFORM!!!!!!
 ***********************/
 
#ifndef __FTYFUFTFERKOYGAAOP__
#define __FTYFUFTFERKOYGAAOP__
#define SBLLIB_VERSION 9

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <math.h>
#include <time.h>

#ifndef _CRT_SECURE_NO_WARNINGS //for MSVC compiling envirment
#define _CRT_SECURE_NO_WARNINGS
#endif

#ifdef _CRT_NONSTDC_NO_WARINGS
#undef _CRT_NONSTDC_NO_WARINGS
#endif

#ifndef NULL //give default definition for NULL
#define NULL (void*)0
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

#define OPT __declspec(dllexport) //use in declartions
#define S_INLINE inline
#define serr (*_serrloc())
#define SERR_LIBCALLFAILED 1
#define SERR_INPUTINVAL 2
#define SERR_STACKERR 3
#define pathsep '\\'//'/'for Linux

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

typedef const char * ccp;

typedef const unsigned long cul;

typedef char* vlist;

typedef unsigned int usint;

typedef unsigned long uslong;

typedef unsigned char uschar;

//declation start
OPT int  InitStack(sqStack *s,unsigned stackSize,unsigned typeSize);


OPT int  Push(sqStack *s,void *e); //入栈


OPT int  Pop(sqStack *s,void *e); //出栈


OPT int  ClearStack(sqStack *s); //清空栈内所有元素


OPT int  DestroyStack(sqStack *s); //销毁栈


OPT int  GetLen(sqStack *s); //获取已入栈元素个数


OPT int  Calculate(char *arr,void *result); //计算表达式结果：参数一：arr为使用空格分隔的采用后缀表达式表示的要计算的字符串,例：arr={"3 5 + "}。参数二：result存放计算结果。


OPT int  InfixToPostfix(ccp infix,char *postfix); //将中缀表达式转换为后缀表达式。例：infix={"3+5\n"} ,转换后，postfix={"3 5 + "};


OPT int  prterr(ccp fmt,...);//自定义错误处理函数


OPT double  calculator( ccp infix );


OPT long  fsize( FILE * stream );	/*获取文件长度*/


OPT int  mysh( ccp path );	/*自定义shell程序*/


OPT int  fcopy( ccp oldname, ccp newname );      /*文件复制函数*/


OPT int  prtpn( FILE *fp, cul minimum, cul maximum );	/*输出指定范围内的质数*/


OPT int  ispn( cul testingnum );


OPT int  randomnum( cui seed,cui maximum,cui minimum );


OPT char *  myitoa(int num, char *str, int radix);


OPT int  isrp(cul n1,cul n2);


OPT char *  _strstr(ccp str1,ccp str2);


OPT char *  mtscat(cui amount,...);


OPT int  iofile(FILE  *origin,FILE *dest);


OPT int  prtfile(FILE *stream);


OPT int  average(cui amt,...);


OPT int  gcf(cui n1,cui n2);


OPT int  lcm(cui n1,cui n2);


OPT int  eular(cui n);


OPT int getmname(char *fullpath,char *mname);


OPT int getmpath(char *fullpath,char *mpath);


OPT uslong  wsbl_frame(int ch);


OPT int  rsbl_frame(int code);


OPT S_INLINE int  tolwr(int chr);


OPT S_INLINE int  toupr(int chr);


OPT S_INLINE int  isalp(int chr);


OPT S_INLINE int  isaln(int chr);


OPT S_INLINE int  isdgt(int chr);


OPT S_INLINE int  isupr(int chr);


OPT S_INLINE int  islwr(int chr);


OPT S_INLINE int  isctl(int chr);


OPT S_INLINE int  isprt(int chr);


OPT S_INLINE int  isgrh(int chr);


OPT S_INLINE int  ispct(int chr);


OPT S_INLINE int  isspc(int chr);


OPT S_INLINE int  isxdgt(int chr);


OPT S_INLINE int *  _serrloc( void );

#ifdef __cplusplus
}
#endif
#endif/*__FTYFUFTFERKOYGAAOP__*/
