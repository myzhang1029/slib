#include "slib.h"

int ser;

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
			ser=2;
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
		ser=1;
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
		ser=3;
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
		ser=3;
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


/*
自定义错误处理函数
*/
OPT int  prterr(ccp fmt,... )
{
	vlist argptr;
	vstart(argptr, fmt);
	fprintf(stderr,"Error:");
	vfprintf(stderr,fmt,argptr);
	if(errno != 0)
		fprintf(stderr,"errcode:%d,more facts:%s\n",errno,strerror(errno));
	else
		fprintf(stderr,"errcode:%d",serr);
	vend(argptr);
	return STRUE;
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


OPT long  fsize( FILE * stream )
{
	long size;
	if ( !stream )
	{
		ser=2;
		return SERROR;
	}
	fseek( stream, 0L, SEEK_END );
	size = ftell( stream );
	return size;
}


OPT int  fcopy( ccp oldname, ccp newname ) /* user - sec7 */
{
	FILE * fold, *fnew;
	fold = fopen( oldname, "rb" );
	if ( !fold )
	{
		ser=1;
		return SERROR;
	}
	fnew = fopen( newname, "wb" );
	if ( !fnew )
	{
		ser=1;
		fclose( fold );
		return SERROR;
	}
	iofile( fold,fnew );
	fclose( fnew );
	fclose( fold );
	return STRUE;
}


OPT int  prtpn( FILE*fp, cul minimum, cul maximum )
{
	long n=0,i=0;
	_Bool torf=0;
	if ( maximum<=2)
	{
		ser=2;
		prterr("input not allowed!");
	}

	if( minimum <= 2)
		fprintf(fp,"2\n");
	for(n=minimum; n<=maximum; ++n)
	{
		for(i=2; i<n; ++i)
		{
			if(n%i!=0)
				torf = 1;
			else
			{
				torf =0;
				break;
			}
		}
		if(torf==1)
		{
			fprintf(fp,"%lu\n",n);
		}
	}
	return STRUE;
}


OPT int ispn( cul testingnum )
{
	long i;
	if( testingnum == 2)
		return STRUE;
	for(i = 2; i<testingnum; ++i)
	{
		if( testingnum%i==0 )
			return SFALSE;
	}
	return STRUE;
}


OPT long randomnum( cui seed,cul maximum,cul minimum )
{
	srand(seed);
	return minimum + rand() % (maximum-minimum);
}


OPT char *  myitoa(int num, char *str, int radix)
{
	char  desting[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

	char* ptr = str;
	int i;
	int j;

	while (num)
	{
		*ptr++  = desting[num % radix];
		num    /= radix;

		if (num < radix)
		{
			*ptr++  = desting[num];
			*ptr    = '\0';
			break;
		}
	}

	j = ptr - str - 1;

	for (i = (ptr - str) / 2; i > 0; --i)
	{
		int temp = str[i];
		str[i]   = str[j];
		str[j--] = temp;
	}

	return str;
}


OPT int  isrp (cul n1,cul n2)
{
	long counter;
	if(n1 == n2)
		return SFALSE;
	if(n1 == 1 || n2 == 1)
		return SFALSE;
	if(n1 % n2 == 0 || n2 % n1 == 0)
		return SFALSE;
	for(counter=2;
	        counter<(n1>n2?n2:n1);
	        ++counter)
	{
		if(n1 % counter == 0 && n2 % counter == 0)
			return SFALSE;
	}
	return STRUE;
}


OPT char *  _strstr(ccp str1,ccp str2)
{
	char *cp =(char*)str1,*s1,*s2;
	if (! *str2)
		return (char*)str1;
	while(cp)
	{
		s1 = cp;
		s2 = (char*)str2;
		while(*s1 && *s2 && !(*s1 - *s2))
			s1++,s2++;
		if(!*s2)
			return cp;
		cp++;
	}
	return NULL;
}


OPT char *  mtscat(cui amount,...)
{
	vlist strs;
	char *str,*buf;
	int counter;
	vstart (strs,amount);
	str=varg(strs,char*);
	for(counter=0; counter<=amount; ++counter)
	{
		buf=varg(strs,char*);
		strcat(str,buf);
	}
	vend(strs);
	return str;
}


OPT int  iofile(FILE *origin,FILE *dest)
{
	int ch;
	rewind(origin);
	if(feof(origin))
		return SFALSE;
	ch=fgetc(origin);
	while(1)
	{
		if(feof(origin))
			break;
		putc(ch,dest);
		ch=fgetc(origin);
	}
	return STRUE;
}


OPT int  prtfile(FILE *stream)
{
	return iofile(stream,stdout);
}


OPT int  average(cui amt,...)
{
	vlist args;
	int count,sum=0;
	vstart(args,amt);
	for(count=0; count<amt; count++)
	{
		sum=sum+varg(args,int);
	}
vend(args);
	return sum/amt;
}


OPT int  gcf(cui n1,cui n2)
{
	int count;
	if(n1==n2)
		return n1;
	if(n2%n1==0)
		return n1;
	if(n1%n2==0)
		return n2;
	for(count=n1>n2?n2/2:n1/2; count>1; --count)
	{
		if(n1%count==0&&n2%count==0)
			return count;
	}
	return 1;
}


OPT int lcm(cui n1,cui n2)
{
	return n1*n2/gcf(n1,n2);
}


OPT int getmname(char *fullpath,char *mname)
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


OPT int getmpath(char *fullpath,char *mpath)
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
	switch ( tolwr(ch) )
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


OPT S_INLINE int  tolwr(int chr)
{
	return chr>=65&&chr<=90?
	       chr+32:chr;
}


OPT S_INLINE int  toupr(int chr)
{
	return chr<=122&&chr>=97?
	       chr-32:chr;
}


OPT S_INLINE int  isalp(int chr)
{
	return(chr>=97&&chr<=122)||(chr<=90&&chr>=65)?
	      STRUE:SFALSE;
}


OPT S_INLINE int  isaln(int chr)
{
	return(chr>=97&&chr<=122)||(chr<=90&&chr>=65)||(chr>=48&&chr<=97)?
	      STRUE:SFALSE;
}


OPT S_INLINE int  isdgt(int chr)
{
	return chr<=90&&chr>=65?
	       STRUE:SFALSE;
}


OPT S_INLINE int  isupr(int chr)
{
	return chr>=65&&chr<=90?
	       STRUE:SFALSE;
}


OPT S_INLINE int  islwr(int chr)
{
	return chr>=97&&chr<=122?
	       STRUE:SFALSE;
}


OPT S_INLINE int  isctl(int chr)
{
	return(chr<=31&&chr>=0)||chr==127?
	      STRUE:
	      SFALSE;
}


OPT S_INLINE int  isprt(int chr)
{
	return chr>=32&&chr<=126?
	       STRUE:SFALSE;
}


OPT S_INLINE int  isgrh(int chr)
{
	return (chr>=33&&chr<=126)?
	       STRUE:SFALSE;
}


OPT S_INLINE int  ispct(int chr)
{
	return(isaln(chr)==SFALSE&&
	       isspc(chr)==SFALSE)?
	      STRUE:SFALSE;
}


OPT S_INLINE int  isspc(int chr)
{
	return(chr>=9&&chr<=13)||chr==32?
	      STRUE:SFALSE;
}


OPT S_INLINE int  isxdgt(int chr)
{
	return((chr>=65&&chr<=70)||(chr>=97&&chr<=102)||(chr>=65&&chr<=90))?
	      STRUE:SFALSE;
}


OPT int eular(cui n)
{
	int count,result=0;
	for(count=0; count<n; ++count)
	{
		if(isrp(n,count))
			++count;
	}
	return result;
}


OPT S_INLINE int *  _serrloc( void )
{
	return &ser;
}
