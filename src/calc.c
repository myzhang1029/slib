/*
 *  calc.c - Calculate and Stack Functions in the Slib library
 *
 *  Copyright (C) 2017 Zhang Maiyun
 *  Thanks a user on CSDN.NET for the code framework.
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 *  This file is part of slib.
 *  slib is free software; you can redistribute it and/or modify
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
#include "slib.h"


static int Calculate(char *arr,void *result); //计算表达式结果：参数一：arr为使用空格分隔的采用后缀表达式表示的要计算的字符串,例：arr={"3 5 + "}。参数二：result存放计算结果。
static int InfixToPostfix(char *infix,char *postfix); //将中缀表达式转换为后缀表达式。例：infix={"3+5\n"} ,转换后，postfix={"3 5 + "};

OPT double calculate(ccp infix)
{
  char postfix[BUFFERSIZE]={'\0'}; 
  InfixToPostfix((char *)infix,postfix); 
  double result;
  Calculate(postfix,&result); 
  return result;
}

/*
将中缀表达式转换为后缀表达式
参数:infix 指向中缀表达式，以回车键即\n结尾。
postfix 指向后缀表达式临时缓冲区，用来存放转换后的结果。
附转换规则：从左到右遍历中缀表达式的每个数字和符号，若是数字则直接保存在postfix数组中；若是符号，则判断其与栈顶符号的优先级，是右括号或者优先级不大于栈顶符号，则栈顶元素依次出栈并输出，直到遇到左括号或者栈空时，才将刚才的那个符号入栈。
*/
static int InfixToPostfix(char *infix,char *postfix)
{
  sqStack s;
  if(InitStack(&s,STKELMT*sizeof(char),sizeof(char))==SERROR)
		prterr("InfixToPostfix init stack error！");
  char c,e;
  int j=0,i=0;
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
				}while(GetLen(&s)&&'('!=e);  //将栈里的所有符号出栈(除非遇到左括号)
			  Push(&s,(void*)&c); //最后将新来的加减号再入栈
			}
		}
      else if('*'==c||'/'==c||'('==c||'^'==c) //如果是乘除号,^或左括号，因为他们的优先级高，所以直接入栈。
		{
		  Push(&s,(void*)&c);
		}
      else if('\n'==c) //判断一下，所有符号是否都已转换完成
		{
		  break;
		}
      else //能走到这个else的，都是我不认识的符号了
		{
		  // printf("\nError:input error,the character %d cann't recognize!\n",c);
		  return -1;
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
static int Calculate(char *arr,void *result)
{
  // printf("%s\n",arr);
  double d,e,f; //d,e 存放两个因数。f存放d,e计算后的结果.
  sqStack s; 
  char *op; //存放后缀表达式中的每个因数或运算符
  char *buf=arr; 
  if(InitStack(&s,STKELMT*sizeof(double),sizeof(double))==SERROR)
		prterr("Calculate init stack error!");
  while((op=strtok(buf," "))!=NULL) 
    {
      buf=NULL;
      switch(op[0])
		{
		case '+':
		  Pop(&s,&d);
		  Pop(&s,&e);
		  f=d+e;
		  Push(&s,&f);
		  break;
		case '-':
		  Pop(&s,&d);
		  Pop(&s,&e);
		  f=e-d;
		  Push(&s,&f);
		  break;
		case '*':
		  Pop(&s,&d);
		  Pop(&s,&e);
		  f=d*e;
		  Push(&s,&f);
		  break;
		case '/':
		  Pop(&s,&d);
		  Pop(&s,&e);
		  f=e/d;
		  Push(&s,&f);
		  break;
	        case '^':
		  Pop(&s,&d);
		  Pop(&s,&e);
		  f=pow(e,d);
		  Push(&s,&f);
		  break;
		default:
		  d=atof(op); //不是运算符，就肯定是因数了。所以，用atof函数，将字符串转换为double类型
		  Push(&s,&d);
		  break;
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
OPT int InitStack(sqStack *s,unsigned stackSize,unsigned typeSize)
{
  s->base=malloc(stackSize);
  if(!s->base)
    return SERROR;
  s->top=s->base;
  s->stackSize=stackSize;
  s->typeSize=typeSize;
  return STRUE;
}

/*
压栈
*/
OPT int Push(sqStack *s,void *e)
{
  if((int)s->top-(int)s->base+s->typeSize>s->stackSize)
    return SFALSE;
  memcpy(s->top,e,s->typeSize);
  s->top=(void*)((int)s->top+s->typeSize);
  return STRUE;
}

/*
出栈
*/
OPT int Pop(sqStack *s,void *e)
{
  if(s->top==s->base)
    return SFALSE;
  s->top=(void*)((int)s->top-(int)s->typeSize);
  memcpy(e,s->top,s->typeSize);
  return STRUE;
}

/*
清栈
*/
OPT int ClearStack(sqStack *s)
{
  s->top=s->base;
  return STRUE;
}

/*
毁栈
*/
OPT int DestroyStack(sqStack *s)
{
  free(s->base);
  s->top=s->base=NULL;
  s->stackSize=s->typeSize=0;
  return STRUE;
}

/*
获取已入栈元素个数
*/
OPT int GetLen(sqStack *s)
{
  return ((int)s->top-(int)s->base)/s->typeSize;
}

