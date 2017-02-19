/*
 *  lib.c - Main library of the slib
 *
 *  Copyright (C) 2017 Zhang Maiyun
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

#include "slib.h"

#if 0
OPT double  calculator( ccp infix ) //整合功能，提供计算
{
	double result;
	char postfix[BUFFERSIZE]; //存放后缀表达式的临时缓冲区
	InfixToPostfix(infix,postfix); //将中缀转换为后缀表达式
	Calculate(postfix,&result); //计算后缀表达式的结果
	return result;
}


/*
将中缀表达式转换为后缀表达式
参数:infix 指向中缀表达式，以回车键即\n结尾。
postfix 指向后缀表达式临时缓冲区，用来存放转换后的结果。
附转换规则：从左到右遍历中缀表达式的每个数字和符号，若是数字则直接保存在postfix数组中；若是符号，则判断其与栈顶符号的优先级，是右括号或者优先级不大于栈顶符号，则栈顶元素依次出栈并输出，直到遇到左括号或者栈空时，才将刚才的那个符号入栈。
*/
OPT int  InfixToPostfix(ccp infix,char *postfix)
{
	int j=0,i=0;
	char c,e;
	sqStack s;
	if(InitStack(&s,STKELMT*sizeof(char),sizeof(char))==SERROR)
	{
		prterr("InfixToPostfix init stack error！");
	}
	c=*(infix+i); //取出中缀表达式中的第一个字符
	i++;
	while('\n'!=c) //遇到换行符，表示转换结束
	{
		while(c>='0'&&c<='9') //先判断一下取出的字符是否是数字，如果是数字的话，则直接存入postfix数组
		{
			postfix[j++]=c;
			c=*(infix+i);
			i++;
			if(c<'0'||c>'9') //如果不是数字，则在后面添加空格，以便区分各个符号
			{
				postfix[j++]=' ';
			}
		}
		if(')'==c) //不是数字，则判断是否为右括号。[括号的优先级最高，所以，如果是右括号的话，就得先进行括号里的各种运算]
		{
			Pop(&s,(void*)&e);
			while('('!=e) //直到遇到左括号为止
			{
				postfix[j++]=e;
				postfix[j++]=' ';
				Pop(&s,(void*)&e);
			}
		}
		else if('+'==c||'-'==c) //如果是加减号,因为他俩的优先级最低了，所以此时先将栈里的所有符号出栈后(除非遇到左括号)，再把此符号入栈
		{
			if(!GetLen(&s)) //如果是空栈，则直接将加减号入栈
			{
				Push(&s,(void*)&c);
			}
			else
			{
				do
				{
					Pop(&s,(void*)&e);
					if('('==e)
					{
						Push(&s,(void*)&e);
					}
					else
					{
						postfix[j++]=e;
						postfix[j++]=' ';
					}
				}
				while(GetLen(&s)&&'('!=e);   //将栈里的所有符号出栈(除非遇到左括号)
				Push(&s,(void*)&c); //最后将新来的加减号再入栈
			}
		}
		else if('*'==c||'/'==c||'^'==c||'('==c) //因为他们的优先级高，所以直接入栈。
		{
			Push(&s,(void*)&c);
		}

		else if('\0'==c)
		{
			continue;
		}

		else if(c=='\n') //判断一下，所有符号是否都已转换完成
		{
			break;
		}
		else //能走到这个else的，都是我不认识的符号了
		{
			serr=2;
			prterr("input error,the character %d cann't recognize!\n",c);
			return SERROR;
		}
		c=*(infix+i); //取出下一个字符进行转换
		i++;
	}
	while(GetLen(&s)) //转换完成后，栈里可能还有没出栈的运算符号
	{
		Pop(&s,(void*)&e);
		postfix[j++]=e;
		postfix[j++]=' ';
	}
	DestroyStack(&s);
	return STRUE;
}


/*
计算后缀表达式的结果
参数：arr使用空格分隔的后缀表达式字符串。例：arr="31 5 + "
result 保存计算完毕后的结果
注：如何利用栈来计算后缀表达式的结果：依次取出后缀表达式中的符号进行比较，如果是数字，则直接入栈；如果是符号，则出栈两次，弹出两个要计算的因数，进行计算，之后再将计算结果入栈。知道后缀表达式中所有符号都已比较完毕。
*/
OPT int  Calculate(char *arr,void *result)
{
	double d,e,f; //d,e 存放两个因数。f存放d,e计算后的结果.
	sqStack s;
	char *op; //存放后缀表达式中的每个因数或运算符
	char *buf=arr;
	if(InitStack(&s,STKELMT*sizeof(double),sizeof(double))==SERROR)
		prterr("Calculate init stack error!");
	while((op=strtok(buf,"\32"/*空格*/))!=NULL) //利用strtok函数分隔字符串
	{
		buf=NULL;
		switch(op[0])
		{
		case '+':
		{
			Pop(&s,&d);
			Pop(&s,&e);
			f=d+e;
			Push(&s,&f);
			break;
		}
		case '-':
		{
			Pop(&s,&d);
			Pop(&s,&e);
			f=e-d;
			Push(&s,&f);
			break;
		}
		case '*':
		{
			Pop(&s,&d);
			Pop(&s,&e);
			f=d*e;
			Push(&s,&f);
			break;
		}
		case '/':
		{
			Pop(&s,&d);
			Pop(&s,&e);
			f=e/d;
			Push(&s,&f);
			break;
		}
		case '^':
		{
			Pop(&s,&d);
			Pop(&s,&e);
			f=pow(e,d);
			Push(&s,&f);
			break;
		}
		default:
		{
			d=atof(op); //不是运算符，就肯定是因数了。所以，用atof函数，将字符串转换为double类型
			Push(&s,&d);
			break;
		}
		}
	}
	Pop(&s,result);
	DestroyStack(&s);
	return STRUE;
}


/*
初始化栈
参数：stackSize:栈的总容量大小
typeSize:以后要入栈的单个元素的大小
*/
OPT int  InitStack(sqStack *s,unsigned stackSize,unsigned typeSize)
{
	s->base=malloc(stackSize);
	if(!s->base)
	{
		serr=1;
		return SERROR;
	}
	s->top=s->base;
	s->stackSize=stackSize;
	s->typeSize=typeSize;
	return STRUE;
}


/*
压栈
*/
OPT int  Push(sqStack *s,void *e)
{
	if((int)s->top-(int)s->base+s->typeSize>s->stackSize)
	{
		serr=3;
		return SFALSE;
	}
	memcpy(s->top,e,s->typeSize);
	s->top=(void*)((int)s->top+s->typeSize);
	return STRUE;
}


/*
出栈
*/
OPT int  Pop(sqStack *s,void *e)
{
	if(s->top==s->base)
	{
		serr=3;
		return SFALSE;
	}
	s->top=(void*)((int)s->top-(int)s->typeSize);
	memcpy(e,s->top,s->typeSize);
	return STRUE;
}


/*
清栈
*/
OPT int  ClearStack(sqStack *s)
{
	s->top=s->base;
	return STRUE;
}


/*
毁栈
*/
OPT int  DestroyStack(sqStack *s)
{
	free(s->base);
	s->top=s->base=NULL;
	s->stackSize=s->typeSize=0;
	return STRUE;
}


/*
获取已入栈元素个数
*/
OPT int  GetLen(sqStack *s)
{
	return ((int)s->top-(int)s->base)/s->typeSize;
}
#endif


OPT long  randomnum( cui seed,cul maximum,cul minimum )
{
	srand(seed);
	return minimum + rand() % (maximum-minimum);
}


OPT int  mysh( ccp path )
{
	char command[20];
	fflush( stdin );
	printf( "%s(Enter e to quit)>", path );
	fgets( command, 19, stdin );
	if ( strcmp(command,"e\n")==0 )
	{
		return STRUE;
	}
	else
	{
		system( command );
		return SFALSE;
	}
}


OPT char *  mtscat(cui amount,...)
{
	vlist strs;
	char *str;
	int count;
	vstart (strs,amount);
	str=varg(strs,char*);
	for(count=0; count<=amount-1; ++count)
	{
		strcat(str,varg(strs,char*));
	}
	vend(strs);
	return str;
}


OPT int getmname(ccp fullpath,char *mname)
{
	int count,count2=0,fpathl=strlen(fullpath);
	for(count=fpathl;count>=0;--count)
	{
		if(fullpath[count]==pathsep)
		{
			for(++count;count<=fpathl;++count,++count2)
			{
				mname[count2]=fullpath[count];
			}
			return STRUE;
		}
	}
	return SFALSE;
}


OPT int getmpath(ccp fullpath,char *mpath)
{
	int count,count2,fpathl=strlen(fullpath);
	for(count=fpathl;count>=0;--count)
	{
		if(fullpath[count]==pathsep)
		{
			for(count2=0;count2<count;++count2)
			{
				mpath[count2]=fullpath[count2];
			}
			mpath[count2+1]='\0';
			mpath[count2]=pathsep;
			return STRUE;
		}
	}
	return SFALSE;
}


OPT uslong  wsbl_frame(int ch)
{
	switch ( tolower(ch) )
	{
	case ('\n'):
	{
		return SFALSE;
	}
	case ('?'):
	{
		return 0xa2108e1;
	}
	case ('.'):
	{
		return 0x422a732;
	}
	case ('a'):
	{
		return 0x0404491;
	}
	case ('b'):
	{
		return 0x1415454;
	}
	case ('c'):
	{
		return 0x1504015;
	}
	case ('d'):
	{
		return 0x1414454;
	}
	case ('e'):
	{
		return 0x1524895;
	}
	case ('f'):
	{
		return 0x1505010;
	}
	case ('g'):
	{
		return 0x1505096;
	}
	case ('h'):
	{
		return 0x1105011;
	}
	case ('i'):
	{
		return 0x0421084;
	}
	case ('j'):
	{
		return 0x040521c;
	}
	case ('k'):
	{
		return 0x1115051;
	}
	case ('l'):
	{
		return 0x1105411;
	}
	case ('m'):
	{
		return 0x0404404;
	}
	case ('n'):
	{
		return 0x1124410;
	}
	case ('o'):
	{
		return 0x1404415;
	}
	case ('p'):
	{
		return 0x1124410;
	}
	case ('q'):
	{
		return 0x1404415;
	}
	case ('r'):
	{
		return 0x1405055;
	}
	case ('s'):
	{
		return 0x1101011;
	}
	case ('t'):
	{
		return 0x1501004;
	}
	case ('u'):
	{
		return 0x1505404;
	}
	case ('v'):
	{
		return 0x1105415;
	}
	case ('w'):
	{
		return 0x150540a;
	}
	case ('x'):
	{
		return 0x1151011;
	}
	case ('y'):
	{
		return 0x1151084;
	}
	case ('z'):
	{
		return 0x1511115;
	}
	case ('0'):
	{
		return 0x4529441;
	}
	case ('1'):
	{
		return 0x4611df3;
	}
	case ('2'):
	{
		return 0x41111f5;
	}
	case ('3'):
	{
		return 0x2774707;
	}
	case ('4'):
	{
		return 0x8638849;
	}
	case ('5'):
	{
		return 0xe4384e2;
	}
	case ('6'):
	{
		return 0xe4394e4;
	}
	case ('7'):
	{
		return 0xe108406;
	}
	case ('8'):
	{
		return 0x4410878;
	}
	case ('9'):
	{
		return 0x873a080;
	}
	case ('~'):
	{
		return STRUE;
	}
	default:
	{
		return SERROR;
	}
	}
}


OPT int  rsbl_frame(int code)
{
	switch ( code )
	{
	case ('\n'):
	{
		return SFALSE;
	}
	case (0xa2108e1):       /* "?" */
	{
		return 63;
	}
	case (0x422a732):       /* "." */
	{
		return 46;
	}
	case (0x0404491):       /* A */
	{
		return 97;
	}
	case (0x1415454):       /* B */
	{
		return 98;
	}
	case (0x1504015):       /* C */
	{
		return 99;
	}
	case (0x1414454):       /* D */
	{
		return 100;
	}
	case (0x1524895):       /* E */
	{
		return 101;
	}
	case (0x1505010):       /* F */
	{
		return 102;
	}
	case (0x1505096):       /* G */
	{
		return 103;
	}
	case (0x1105011):       /* H */
	{
		return 104;
	}
	case (0x0421084):       /* I */
	{
		return 105;
	}
	case (0x040521c):       /* J */
	{
		return 106;
	}
	case (0x1115051):       /* K */
	{
		return 107;
	}
	case (0x1084215):       /* L */
	{
		return 108;
	}
	case (0x1155551):       /* M */
	{
		return 109;
	}
	case (0x1105411):       /* N */
	{
		return 110;
	}
	case (0x0404404):       /* O */
	{
		return 111;
	}
	case (0x1124410):       /* P */
	{
		return 112;
	}
	case (0x1404415):       /* Q */
	{
		return 113;
	}
	case (0x1405055):       /* R */
	{
		return 114;
	}
	case (0x1101011):       /* S */
	{
		return 115;
	}
	case (0x1501004):       /* T */
	{
		return 116;
	}
	case (0x1505404):       /* U */
	{
		return 117;
	}
	case (0x1105415):       /* V */
	{
		return 118;
	}
	case (0x150540a):       /* W */
	{
		return 119;
	}
	case (0x1151011):       /* X */
	{
		return 120;
	}
	case (0x1151084):       /* Y */
	{
		return 121;
	}
	case (0x1511115):       /* Z */
	{
		return 122;
	}
	case (0x4529441):
	{
		return 48;
	}
	case (0x4611df3):
	{
		return 49;
	}
	case (0x41111f5):
	{
		return 50;
	}
	case (0x2774707):
	{
		return 51;
	}
	case (0x8638849):
	{
		return 52;
	}
	case (0xe4384e2):
	{
		return 53;
	}
	case (0xe4394e4):
	{
		return 54;
	}
	case (0xe108406):
	{
		return 55;
	}
	case (0x4410878):
	{
		return 56;
	}
	case (0x873a080):
	{
		return 57;
	}
	case (0xed):
	{
		return STRUE;
	}
	default:
	{
		return SERROR;
	}
	}
}


char* itoaS(int value, char* string, int radix)
{
  char tmp[33];
  char* tp = tmp;
  int i;
  unsigned v;
  int sign;
  char* sp;

  if (radix > 36 || radix <= 1)
  {
    __set_errno(EDOM);
    return 0;
  }

  sign = (radix == 10 && value < 0);
  if (sign)
    v = -value;
  else
    v = (unsigned)value;
  while (v || tp == tmp)
  {
    i = v % radix;
    v = v / radix;
    if (i < 10)
      *tp++ = i+'0';
    else
      *tp++ = i + 'a' - 10;
  }

  if (string == 0)
    string = (char*)malloc((tp-tmp)+sign+1);
  sp = string;

  if (sign)
    *sp++ = '-';
  while (tp > tmp)
    *sp++ = *--tp;
  *sp = 0;
  return string;
}


char* ltoaS(long value, char* string, int radix)
{
  char tmp[33];
  char* tp = tmp;
  long i;
  unsigned long v;
  int sign;
  char* sp;

  if (radix > 36 || radix <= 1)
  {
     __set_errno(EDOM);
    return 0;
  }

  sign = (radix == 10 && value < 0);
  if (sign)
    v = -value;
  else
    v = (unsigned long)value;
  while (v || tp == tmp)
  {
    i = v % radix;
    v = v / radix;
    if (i < 10)
      *tp++ = i+'0';
    else
      *tp++ = i + 'a' - 10;
  }

  if (string == 0)
    string = (char*)malloc((tp-tmp)+sign+1);
  sp = string;

  if (sign)
    *sp++ = '-';
  while (tp > tmp)
    *sp++ = *--tp;
  *sp = 0;
  return string;
}


char* ultoaS(unsigned long value, char* string, int radix)
{
  char tmp[33];
  char* tp = tmp;
  long i;
  unsigned long v = value;
  char* sp;

  if (radix > 36 || radix <= 1)
  {
    __set_errno(EDOM);
    return 0;
  }

  while (v || tp == tmp)
  {
    i = v % radix;
    v = v / radix;
    if (i < 10)
      *tp++ = i+'0';
    else
      *tp++ = i + 'a' - 10;
  }

  if (string == 0)
    string = (char*)malloc((tp-tmp)+1);
  sp = string;

  while (tp > tmp)
    *sp++ = *--tp;
  *sp = 0;
  return string;
}


#if ! PLAT
OPT int getch(void) 
{
        int c=0;
        struct termios org_opts, new_opts;
        int res=0;

        res=tcgetattr(STDIN_FILENO, &org_opts);
        assert(res==0);
    
        memcpy(&new_opts, &org_opts, sizeof(new_opts));
        new_opts.c_lflag &= ~(ICANON | ECHO | ECHOE | ECHOK | ECHONL | ECHOPRT | ECHOKE | ICRNL);
        tcsetattr(STDIN_FILENO, TCSANOW, &new_opts);
        c=getchar();

        res=tcsetattr(STDIN_FILENO, TCSANOW, &org_opts);assert(res==0);
        return c;
}
#endif
