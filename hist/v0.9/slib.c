#include "slib.h"

int ser;

OPT double  calculator( ccp infix ) //���Ϲ��ܣ��ṩ����
{
	double result;
	char postfix[BUFFERSIZE]; //��ź�׺���ʽ����ʱ������
	InfixToPostfix(infix,postfix); //����׺ת��Ϊ��׺���ʽ
	Calculate(postfix,&result); //�����׺���ʽ�Ľ��
	return result;
}


/*
����׺���ʽת��Ϊ��׺���ʽ
����:infix ָ����׺���ʽ���Իس�����\n��β��
postfix ָ���׺���ʽ��ʱ���������������ת����Ľ����
��ת�����򣺴����ұ�����׺���ʽ��ÿ�����ֺͷ��ţ�����������ֱ�ӱ�����postfix�����У����Ƿ��ţ����ж�����ջ�����ŵ����ȼ����������Ż������ȼ�������ջ�����ţ���ջ��Ԫ�����γ�ջ�������ֱ�����������Ż���ջ��ʱ���Ž��ղŵ��Ǹ�������ջ��
*/
OPT int  InfixToPostfix(ccp infix,char *postfix)
{
	int j=0,i=0;
	char c,e;
	sqStack s;
	if(InitStack(&s,STKELMT*sizeof(char),sizeof(char))==SERROR)
	{
		prterr("InfixToPostfix init stack error��");
	}
	c=*(infix+i); //ȡ����׺���ʽ�еĵ�һ���ַ�
	i++;
	while('\n'!=c) //�������з�����ʾת������
	{
		while(c>='0'&&c<='9') //���ж�һ��ȡ�����ַ��Ƿ������֣���������ֵĻ�����ֱ�Ӵ���postfix����
		{
			postfix[j++]=c;
			c=*(infix+i);
			i++;
			if(c<'0'||c>'9') //����������֣����ں�����ӿո��Ա����ָ�������
			{
				postfix[j++]=' ';
			}
		}
		if(')'==c) //�������֣����ж��Ƿ�Ϊ�����š�[���ŵ����ȼ���ߣ����ԣ�����������ŵĻ����͵��Ƚ���������ĸ�������]
		{
			Pop(&s,(void*)&e);
			while('('!=e) //ֱ������������Ϊֹ
			{
				postfix[j++]=e;
				postfix[j++]=' ';
				Pop(&s,(void*)&e);
			}
		}
		else if('+'==c||'-'==c) //����ǼӼ���,��Ϊ���������ȼ�����ˣ����Դ�ʱ�Ƚ�ջ������з��ų�ջ��(��������������)���ٰѴ˷�����ջ
		{
			if(!GetLen(&s)) //����ǿ�ջ����ֱ�ӽ��Ӽ�����ջ
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
				while(GetLen(&s)&&'('!=e);   //��ջ������з��ų�ջ(��������������)
				Push(&s,(void*)&c); //��������ļӼ�������ջ
			}
		}
		else if('*'==c||'/'==c||'^'==c||'('==c) //��Ϊ���ǵ����ȼ��ߣ�����ֱ����ջ��
		{
			Push(&s,(void*)&c);
		}

		else if('\0'==c)
		{
			continue;
		}

		else if(c=='\n') //�ж�һ�£����з����Ƿ���ת�����
		{
			break;
		}
		else //���ߵ����else�ģ������Ҳ���ʶ�ķ�����
		{
			ser=2;
			prterr("input error,the character %d cann't recognize!\n",c);
			return SERROR;
		}
		c=*(infix+i); //ȡ����һ���ַ�����ת��
		i++;
	}
	while(GetLen(&s)) //ת����ɺ�ջ����ܻ���û��ջ���������
	{
		Pop(&s,(void*)&e);
		postfix[j++]=e;
		postfix[j++]=' ';
	}
	DestroyStack(&s);
	return STRUE;
}


/*
�����׺���ʽ�Ľ��
������arrʹ�ÿո�ָ��ĺ�׺���ʽ�ַ���������arr="31 5 + "
result ���������Ϻ�Ľ��
ע���������ջ�������׺���ʽ�Ľ��������ȡ����׺���ʽ�еķ��Ž��бȽϣ���������֣���ֱ����ջ������Ƿ��ţ����ջ���Σ���������Ҫ��������������м��㣬֮���ٽ���������ջ��֪����׺���ʽ�����з��Ŷ��ѱȽ���ϡ�
*/
OPT int  Calculate(char *arr,void *result)
{
	double d,e,f; //d,e �������������f���d,e�����Ľ��.
	sqStack s;
	char *op; //��ź�׺���ʽ�е�ÿ�������������
	char *buf=arr;
	if(InitStack(&s,STKELMT*sizeof(double),sizeof(double))==SERROR)
		prterr("Calculate init stack error!");
	while((op=strtok(buf,"\32"/*�ո�*/))!=NULL) //����strtok�����ָ��ַ���
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
			d=atof(op); //������������Ϳ϶��������ˡ����ԣ���atof���������ַ���ת��Ϊdouble����
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
��ʼ��ջ
������stackSize:ջ����������С
typeSize:�Ժ�Ҫ��ջ�ĵ���Ԫ�صĴ�С
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
ѹջ
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
��ջ
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
��ջ
*/
OPT int  ClearStack(sqStack *s)
{
	s->top=s->base;
	return STRUE;
}


/*
��ջ
*/
OPT int  DestroyStack(sqStack *s)
{
	free(s->base);
	s->top=s->base=NULL;
	s->stackSize=s->typeSize=0;
	return STRUE;
}


/*
��ȡ����ջԪ�ظ���
*/
OPT int  GetLen(sqStack *s)
{
	return ((int)s->top-(int)s->base)/s->typeSize;
}


/*
�Զ����������
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
