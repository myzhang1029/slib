/*
	2016,Zhang Maiyun
	This is the header file of
	SBL softwares runtime
	include directly
	edit if need
*/
#ifndef __FTYFUFTFERKOYGAAOP__
#define __FTYFUFTFERKOYGAAOP__
#define SBLLIB_VERSION 7

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <math.h>
#include <time.h>
#include <windows.h>

#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#ifdef _CRT_NONSTDC_NO_WARINGS
#undef _CRT_NONSTDC_NO_WARINGS
#endif

#ifndef NULL
#define NULL (void*)0
#endif

#define STRUE 1
#define SFALSE 0
#define SERROR -1
#define STKELMT 100 //堆栈中可入栈元素个数
#define BUFFERSIZE 100  //临时缓冲区大小

#define _INTSZOF(n)   ( (sizeof(n) + sizeof(int) - 1) & ~(sizeof(int) - 1) )
#define vstart(ap,v)  ( ap = (vlist)&v + _INTSZOF(v) )
#define varg(ap,t)    ( *(t *)((ap += _INTSZOF(t)) - _INTSZOF(t)) )
#define vend(ap)      ( ap = (vlist)0 )

#define OPT 
#define IPT 
#define S_INLINE inline
#define S_CDECL __cdecl
#define serr (*_serrloc())

#define SERR_LIBCALLFAILED 1extern int serr;

typedef struct Book
{
	char bkname[100];
	char bktype[30];
	char bkloc[90];
	char bknum[21];
} BOOK;

typedef struct User
{
	char urname[20];
	char urnum[20];
} USER;

typedef struct Stack  //定义堆栈：堆栈中只定义栈大小和每次入栈元素大小，栈中一律使用空指针进行操作。这样，我们自己定义的栈就做到了和数据类型无关性。真正实现了栈的通用。
{
	void *base; //指向栈底
	void *top;  //指向栈顶
	int stackSize; //栈的空间总容量大小
	int typeSize; //入栈时，单个元素占用空间大小
} sqStack;

typedef const unsigned int cui;

typedef const char * ccp;

typedef char* vlist;

typedef unsigned int usint;

typedef unsigned long uslong;

typedef unsigned char uschar;


typedef register int count_t;

IPT int S_CDECL InitStack(sqStack *s,unsigned stackSize,unsigned typeSize);


IPT int S_CDECL Push(sqStack *s,void *e); //入栈


IPT int S_CDECL Pop(sqStack *s,void *e); //出栈


IPT int S_CDECL ClearStack(sqStack *s); //清空栈内所有元素


IPT int S_CDECL DestroyStack(sqStack *s); //销毁栈


IPT int S_CDECL GetLen(sqStack *s); //获取已入栈元素个数


IPT int S_CDECL Calculate(char *arr,void *result); //计算表达式结果：参数一：arr为使用空格分隔的采用后缀表达式表示的要计算的字符串,例：arr={"3 5 + "}。参数二：result存放计算结果。


IPT int S_CDECL InfixToPostfix(ccp infix,char *postfix); //将中缀表达式转换为后缀表达式。例：infix={"3+5\n"} ,转换后，postfix={"3 5 + "};


IPT int S_CDECL prterr(ccp fmt,...);//自定义错误处理函数


IPT double S_CDECL calculator( ccp infix );


IPT long S_CDECL fsize( FILE * stream );	/*获取文件长度*/


IPT int S_CDECL mycmd( ccp path );	/*自定义commander程序*/


IPT int S_CDECL fcopy( ccp oldname, ccp newname );      /*文件复制函数*/


IPT int S_CDECL prtpn( FILE *fp, cui minimum, cui maximum );	/*输出指定范围内的质数*/


IPT int S_CDECL ispn( cui testingnum );


IPT int S_CDECL random( cui seed,cui maximum,cui minimum );


IPT char * S_CDECL myitoa(int num, char *str, int radix);


IPT int S_CDECL isrp(cui n1,cui n2);


IPT char * S_CDECL _strstr(ccp str1,ccp str2);


IPT char * S_CDECL mtscat(cui amount,...);


IPT int S_CDECL iofile(FILE  *origin,FILE *dest);


IPT int S_CDECL prtfile(FILE *stream);


IPT S_INLINE int S_CDECL initmem(void *mem);


IPT int S_CDECL average(cui amt,...);


IPT int S_CDECL gcf(cui n1,cui n2);


IPT int S_CDECL lcm(cui n1,cui n2);


IPT int S_CDECL eular(cui n);


IPT uslong S_CDECL wsbl_frame(int ch);


IPT int S_CDECL rsbl_frame(int code);


IPT S_INLINE int S_CDECL tolwr(int chr);


IPT S_INLINE int S_CDECL toupr(int chr);


IPT S_INLINE int S_CDECL isalp(int chr);


IPT S_INLINE int S_CDECL isaln(int chr);


IPT S_INLINE int S_CDECL isdgt(int chr);


IPT S_INLINE int S_CDECL isupr(int chr);


IPT S_INLINE int S_CDECL islwr(int chr);


IPT S_INLINE int S_CDECL isctl(int chr);


IPT S_INLINE int S_CDECL isprt(int chr);


IPT S_INLINE int S_CDECL isgrh(int chr);


IPT S_INLINE int S_CDECL ispct(int chr);


IPT S_INLINE int S_CDECL isspc(int chr);


IPT S_INLINE int S_CDECL isxdgt(int chr);


IPT S_INLINE int S_CDECL gtc (FILE* __F);


IPT S_INLINE int S_CDECL ptc (int __c, FILE* __F);


IPT S_INLINE int S_CDECL gtch (void);


IPT S_INLINE int S_CDECL ptch(int __c);


IPT S_INLINE int * S_CDECL serrloc( void );



#endif/*__FTYFUFTFERKOYGAAOP__*/
