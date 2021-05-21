
#include <string.h>
#include <stdio.h>
#include <stdlib.h> 
#include <stdarg.h>
#include <errno.h>

#ifndef Status_Defined
#define Status_Defined 
#define TRUE 1
#define FALSE 0
#define THEERROR -1
#define STACKELEMENT 100 //定义堆栈中可入栈元素个数
#define BUFFERSIZE 100  //定义临时缓冲区大小
#endif

typedef struct  //定义堆栈：堆栈中只定义栈大小和每次入栈元素大小，栈中一律使用空指针进行操作。这样，我们自己定义的栈就做到了和数据类型无关性。真正实现了栈的通用。
{
  void *base; //指向栈底
  void *top;  //指向栈顶
  int stackSize; //栈的空间总容量大小
  int typeSize; //入栈时，单个元素占用空间大小
} sqStack;

int InitStack(sqStack *s,unsigned stackSize,unsigned typeSize); //初始化栈
int Push(sqStack *s,void *e); //入栈
int Pop(sqStack *s,void *e); //出栈
int ClearStack(sqStack *s); //清空栈内所有元素
int DestroyStack(sqStack *s); //销毁栈
int GetLen(sqStack *s); //获取已入栈元素个数

int Calculate(char *arr,void *result); //计算表达式结果：参数一：arr为使用空格分隔的采用后缀表达式表示的要计算的字符串,例：arr={"3 5 + "}。参数二：result存放计算结果。
int InfixToPostfix(const char *infix,char *postfix); //将中缀表达式转换为后缀表达式。例：infix={"3+5\n"} ,转换后，postfix={"3 5 + "};

int prterr(const char*fmt,...);//自定义错误处理函数
double CalcWOP( const char *infix ); 
const char ver [10] = { "12v2_3.6" };                           /*版本号*/

int file_copy( const char *oldname, const char *newname );      /*文件复制函数*/


int read_csbl( void );	/*CSBL解码器*/


int write_csbl( void );	/*CSBL编码器*/


void help_csbl( void );	/*CSBL帮助*/


int file_size( const char * filename );	/*获取文件长度*/


int mycmd( const char * path );	/*自定义commander程序*/


int setup( void );	/*程序初始化函数*/


int main( int argc, char * argv[], char * envp[] )	/* 主函数 */
{
	unsigned int	exitt = 1;	/* 退出变量 */
	unsigned int	content = 0;	/* 功能选项变量 */
	content = setup();	/*程序初始化*/
	if ( content != 0 )
		prterr( "%d", content );
	puts( "Welcome" );	/* 欢迎界面 */
	do
	{
		printf( "\n1=查看系统版本\n2=产生随机数\n3=计算器\n4=自动关机\n5=解csbl\
		\n6=写csbl\n7=复制文件\n8=启动cmd\n9=csbl帮助\n请选择：");	/*程序主菜单*/
		scanf( "%d", &content );
		switch ( content )	/* switch case */
		{
		case (1):
		{
			printf( "sbl admin %s\n", &ver );	/* 版本号 */
			printf( "于%s，%s发布\n", __DATE__, __TIME__ );
			break;
		}

		case (2):
		{
			unsigned int rad = 0;	/*随机数变量*/
			printf( "输入最大值：" );
			scanf( "%d", &rad );
			srand( time( NULL ) );
			printf( "您的随机数是：%d\n\n", rand() % rad );
			break;
		}

		case (3): /* 计算器 */
		{
			double	result;
			char	infix[BUFFERSIZE];
			fflush( stdin );
			printf( "输入算式：" );
			fgets( infix, BUFFERSIZE, stdin );
			printf( "%lf\n", CalcWOP( infix ) );	/*使用calculator.h中的函数进行计算*/
			break;
		}

		case (4):
		{
			system( "shutdown -s" ); /* 自动关机-30s */
			printf( "输入1来阻止关闭系统" );
			if ( scanf( "%d", &exitt ) == 1 )
				system( "shutdown -a" );
			break;
		}

		case (5):	/*解码器*/
		{
			if ( read_csbl() == -1 )
				prterr( "无法打开文件！" );
			break;
		}

		case (6):	/*编码器*/
		{
			if ( write_csbl() == -1 )
				prterr( "无法打开文件！" );
			break;
		}

		case (7):
		{
			char source[80], destination[80];
			printf( "\n请输入所需复制的文件： " );
			fflush( stdin );
			fgets( source, 80, stdin );
			printf( "\n请输入目标：" );
			fgets( destination, 80, stdin );
			if ( file_copy( source, destination ) == 0 )
				puts( "复制成功\n" );
			else
				prterr( "复制时出现错误\n" );
			break;
		}

		case (8):
		{
			mycmd( argv[0] );
			break;
		}

		case (9):
		{
			help_csbl();
			break;
		}
		}
		printf( "输入1继续:" );
		scanf( "%d", &exitt );
	}
	while ( exitt == 1 );
	return(0);
}


int file_copy( const char *oldname, const char *newname ) /* user - sec7 */
{
	FILE * fold, *fnew;
	int	c;
	if ( (fold = fopen( oldname, "rb" ) ) == NULL )
	{
		return(-1);
	}
	if ( (fnew = fopen( newname, "wb" ) ) == NULL )
	{
		fclose( fold );
		return(-1);
	}
	while ( 1 )
	{
		c = fgetc( fold );
		if ( !feof( fold ) )
			fputc( c, fnew );
		else
			break;
	}
	fclose( fnew );
	fclose( fold );
	return(0);
}


void help_csbl( void ) 	/* user - sec9 */
{
	unsigned int code_help;	/* 帮助变量 */
	puts( "1=解码器帮助，2=编码器帮助" );
	scanf( "%d", &code_help );
	if ( code_help == 1 )
	{
		puts( "1: 输入csbl码访问密码" );
		puts( "2: 输入所需转换的csbl码，每七位一组，并回车" );
		puts( "3: 接收到“继续”信号就输入下一个" );
		puts( "4: 输入完毕后输入ed，信息在sec.txt" );
	}
	if ( code_help == 2 )
	{
		puts( "1: 输入csbl码访问密码" );
		puts( "2: 输入所需转换的字母、数字，并回车" );
		puts( "3: 接收到“继续”信号就输入下一个" );
		puts( "4: 输入完毕后输入~，信息在sec.txt" );
	}
}


int read_csbl( void )	/* user - sec5 */
{
	unsigned int	coding = 1;	/* 解码器变量 */
	FILE * op = fopen( "sec.txt", "a" );
	if ( !op )
		return(-1);
	printf( "输入7位十六进制码:" );         /* 解码器 */
	do
	{
		scanf( "%x", &coding );
		switch ( coding )
		{
		case ('\n'):
		{
			continue;
		}
		case (0xa2108e1):       /* "?" */
		{
			puts( "?" );
			fprintf( op, "?" );
			break;
		}
		case (0x422a732):       /* "." */
		{
			puts( "." );
			fprintf( op, "." );
			break;
		}
		case (0x0404491):       /* A */
		{
			printf( "a" );
			fprintf( op, "a" );
			break;
		}
		case (0x1415454):       /* B */
		{
			puts( "b" );
			fprintf( op, "b" );
			break;
		}
		case (0x1504015):       /* C */
		{
			puts( "c" );
			fprintf( op, "c" );
			break;
		}
		case (0x1414454):       /* D */
		{
			puts( "d" );
			fprintf( op, "d" );
			break;
		}
		case (0x1524895):       /* E */
		{
			puts( "e" );
			fprintf( op, "e" );
			break;
		}
		case (0x1505010):       /* F */
		{
			puts( "f" );
			fprintf( op, "f" );
			break;
		}
		case (0x1505096):       /* G */
		{
			puts( "g" );
			fprintf( op, "g" );
			break;
		}
		case (0x1105011):       /* H */
		{
			puts( "h" );
			fprintf( op, "h" );
			break;
		}
		case (0x0421084):       /* I */
		{
			puts( "i" );
			fprintf( op, "i" );
			break;
		}
		case (0x040521c):       /* J */
		{
			puts( "j" );
			fprintf( op, "j" );
			break;
		}
		case (0x1115051):       /* K */
		{
			puts( "k" );
			fprintf( op, "k" );
			break;
		}
		case (0x1084215):       /* L */
		{
			puts( "l" );
			fprintf( op, "l" );
			break;
		}
		case (0x1155551):       /* M */
		{
			printf( "m" );
			fprintf( op, "m" );
			break;
		}
		case (0x1105411):       /* N */
		{
			puts( "n" );
			fprintf( op, "n" );
			break;
		}
		case (0x0404404):       /* O */
		{
			puts( "o" );
			fprintf( op, "o" );
			break;
		}
		case (0x1124410):       /* P */
		{
			puts( "p" );
			fprintf( op, "p" );
			break;
		}
		case (0x1404415):       /* Q */
		{
			puts( "q" );
			fprintf( op, "q" );
			break;
		}
		case (0x1405055):       /* R */
		{
			puts( "r" );
			fprintf( op, "r" );
			break;
		}
		case (0x1101011):       /* S */
		{
			puts( "s" );
			fprintf( op, "s" );
			break;
		}
		case (0x1501004):       /* T */
		{
			puts( "t" );
			fprintf( op, "t" );
			break;
		}
		case (0x1505404):       /* U */
		{
			puts( "u" );
			fprintf( op, "u" );
			break;
		}
		case (0x1105415):       /* V */
		{
			puts( "v" );
			fprintf( op, "v" );
			break;
		}
		case (0x150540a):       /* W */
		{
			puts( "w" );
			fprintf( op, "w" );
			break;
		}
		case (0x1151011):       /* X */
		{
			puts( "x" );
			fprintf( op, "x" );
			break;
		}
		case (0x1151084):       /* Y */
		{
			printf( "y" );
			fprintf( op, "y" );
			break;
		}
		case (0x1511115):       /* Z */
		{
			puts( "z" );
			fprintf( op, "z" );
			break;
		}
		case (0x4529441):
		{
			puts( "0" );
			fprintf( op, "0" );
			break;
		}
		case (0x4611df3):
		{
			puts( "1" );
			fprintf( op, "1" );
			break;
		}
		case (0x41111f5):
		{
			puts( "2" );
			fprintf( op, "2" );
			break;
		}
		case (0x2774707):
		{
			puts( "3" );
			fprintf( op, "3" );
			break;
		}
		case (0x8638849):
		{
			puts( "4" );
			fprintf( op, "4" );
			break;
		}
		case (0xe4384e2):
		{
			puts( "5" );
			fprintf( op, "5" );
			break;
		}
		case (0xe4394e4):
		{
			puts( "6" );
			fprintf( op, "6" );
			break;
		}
		case (0xe108406):
		{
			puts( "7" );
			fprintf( op, "7" );
			break;
		}
		case (0x4410878):
		{
			puts( "8" );
			fprintf( op, "8" );
			break;
		}
		case (0x873a080):
		{
			puts( "9" );
			fprintf( op, "9" );
			break;
		}
		case (0xed):
		{
			fclose( op );
			op = NULL;
			system( "sec.txt" );
			return(0);
		}
		default:
		{
			puts( "错误！" );
		}
		}
		puts( "\n继续，输入ed结束：" );
	}
	while ( 1 );
}


int write_csbl( void ) /* user - sec6 */
{
	FILE * op = fopen( "sec.txt", "a" );
	if ( !op )
		return(-1);
	fflush( stdin );
	printf( "输入字母、符号或数字：" );
	fprintf( op, "0x" );
	do
	{
		switch ( getchar() )
		{
		case ('\n'):
		{
			continue;
		}
		case ('?'):
		{
			puts( "?" );
			fprintf( op, "a2108e1" );
			break;
		}
		case ('.'):
		{
			puts( "." );
			fprintf( op, "422a732" );
			break;
		}
		case ('a'):
		{
			printf( "a" );
			fprintf( op, "0404491" );
			break;
		}
		case ('b'):
		{
			puts( "b" );
			fprintf( op, "1415454" );
			break;
		}
		case ('c'):
		{
			puts( "c" );
			fprintf( op, "1504015" );
			break;
		}
		case ('d'):
		{
			puts( "d" );
			fprintf( op, "1414454" );
			break;
		}
		case ('e'):
		{
			puts( "e" );
			fprintf( op, "1524895" );
			break;
		}
		case ('f'):
		{
			puts( "f" );
			fprintf( op, "1505010" );
			break;
		}
		case ('g'):
		{
			puts( "g" );
			fprintf( op, "1505096" );
			break;
		}
		case ('h'):
		{
			puts( "h" );
			fprintf( op, "1105011" );
			break;
		}
		case ('i'):
		{
			puts( "i" );
			fprintf( op, "0421084" );
			break;
		}
		case ('j'):
		{
			puts( "j" );
			fprintf( op, "040521c" );
			break;
		}
		case ('k'):
		{
			puts( "k" );
			fprintf( op, "1115051" );
			break;
		}
		case ('l'):
		{
			puts( "l" );
			fprintf( op, "1105411" );
			break;
		}
		case ('m'):
		{
			printf( "m" );
			fprintf( op, "0404404" );
			break;
		}
		case ('n'):
		{
			puts( "n" );
			fprintf( op, "1124410" );
			break;
		}
		case ('o'):
		{
			puts( "o" );
			fprintf( op, "1404415" );
			break;
		}
		case ('p'):
		{
			puts( "p" );
			fprintf( op, "1124410" );
			break;
		}
		case ('q'):
		{
			puts( "q" );
			fprintf( op, "1404415" );
			break;
		}
		case ('r'):
		{
			puts( "r" );
			fprintf( op, "1405055" );
			break;
		}
		case ('s'):
		{
			puts( "s" );
			fprintf( op, "1101011" );
			break;
		}
		case ('t'):
		{
			puts( "t" );
			fprintf( op, "1501004" );
			break;
		}
		case ('u'):
		{
			puts( "u" );
			fprintf( op, "1505404" );
			break;
		}
		case ('v'):
		{
			puts( "v" );
			fprintf( op, "1105415" );
			break;
		}
		case ('w'):
		{
			puts( "w" );
			fprintf( op, "150540a" );
			break;
		}
		case ('x'):
		{
			puts( "x" );
			fprintf( op, "1151011" );
			break;
		}
		case ('y'):
		{
			printf( "y" );
			fprintf( op, "1151084" );
			break;
		}
		case ('z'):
		{
			puts( "z" );
			fprintf( op, "1511115" );
			break;
		}
		case ('0'):
		{
			puts( "0" );
			fprintf( op, "4529441" );
			break;
		}
		case ('1'):
		{
			puts( "1" );
			fprintf( op, "4611df3" );
			break;
		}
		case ('2'):
		{
			puts( "2" );
			fprintf( op, "41111f5" );
			break;
		}
		case ('3'):
		{
			puts( "3" );
			fprintf( op, "2774707" );
			break;
		}
		case ('4'):
		{
			puts( "4" );
			fprintf( op, "8638849" );
			break;
		}
		case ('5'):
		{
			puts( "5" );
			fprintf( op, "e4384e2" );
			break;
		}
		case ('6'):
		{
			puts( "6" );
			fprintf( op, "e4394e4" );
			break;
		}
		case ('7'):
		{
			puts( "7" );
			fprintf( op, "e108406" );
			break;
		}
		case ('8'):
		{
			puts( "8" );
			fprintf( op, "4410878" );
			break;
		}
		case ('9'):
		{
			puts( "9" );
			fprintf( op, "873a080" );
			break;
		}
		case ('~'):
		{
			fclose( op );
			op = NULL;
			system( "sec.txt" );
			return(0);
		}
		default:
		{
			puts( "错误！" );
		}
		}
		puts( "\n继续，输入~结束：" );
	}
	while ( 1 );
}


int file_size( const char* filename )
{
	int size;
	FILE * fp = fopen( filename, "r" );
	if ( !fp )
		return(-1);
	fseek( fp, 0L, SEEK_END );
	size = ftell( fp );
	fclose( fp );
	return(size);
}


int mycmd( const char * path )
{
	char cmd[20];
	fflush( stdin );
	printf( "%s(输入1返回程序)>", path );
	fgets( cmd, 19, stdin );
	if ( cmd == "1" )
	{
		return(0);
	}
	else
	{
		system( cmd );
		mycmd( path );
	}
	return(0);
}


int setup( void )
{
	FILE * fp;
	system( "title SBL admin V2.3.0" );
	fp = fopen( "serial_number.sn", "a" );
	if ( !fp )
		return(-1);
	if ( file_size( "serial_number.sn" ) == 0 )
	{
		fprintf( fp, "SBL Admin Software version%s created at%s %s"
			 , &ver, __DATE__, __TIME__ );
	}
	fclose( fp );
	fp = fopen( "sec.txt", "w+" );
	if ( !fp )
		return(-2);
	fclose( fp );
	fp = NULL;
	return(0);
}



double CalcWOP( const char *infix ) //整合以下功能，提供计算 
{
  double result;
  char postfix[BUFFERSIZE]={'\0'}; //存放后缀表达式的临时缓冲区
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
int InfixToPostfix(const char *infix,char *postfix)
{
  int j=0,i=0;
  char c,e;
  sqStack s;
  if(InitStack(&s,STACKELEMENT*sizeof(char),sizeof(char))==THEERROR)
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
				}while(GetLen(&s)&&'('!=e);  //将栈里的所有符号出栈(除非遇到左括号)
			  Push(&s,(void*)&c); //最后将新来的加减号再入栈
			}
		}
      else if('*'==c||'/'==c||'('==c) //如果是乘除号或左括号，因为他们的优先级高，所以直接入栈。
		{
		  Push(&s,(void*)&c);
		}
      else if('\n'==c) //判断一下，所有符号是否都已转换完成
		{
		  break;
		}
      else //能走到这个else的，都是我不认识的符号了
		{
		  printf("\nError:input error,the character %d cann't recognize!\n",c);
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
  return TRUE;
}

/*
计算后缀表达式的结果
参数：arr使用空格分隔的后缀表达式字符串。例：arr="31 5 + "
result 保存计算完毕后的结果
注：如何利用栈来计算后缀表达式的结果：依次取出后缀表达式中的符号进行比较，如果是数字，则直接入栈；如果是符号，则出栈两次，弹出两个要计算的因数，进行计算，之后再将计算结果入栈。知道后缀表达式中所有符号都已比较完毕。
*/
int Calculate(char *arr,void *result)
{
  // printf("%s\n",arr);
  double d,e,f; //d,e 存放两个因数。f存放d,e计算后的结果.
  sqStack s; 
  char *op; //存放后缀表达式中的每个因数或运算符
  char *buf=arr; //声明bufhe saveptr两个变量，是strtok_r函数的需要。
  char *saveptr=NULL;
  if(InitStack(&s,STACKELEMENT*sizeof(double),sizeof(double))==THEERROR)
		prterr("Calculate init stack error!");
  while((op=strtok(buf," "))!=NULL) //利用strtok_r函数分隔字符串
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
		default:
		  d=atof(op); //不是运算符，就肯定是因数了。所以，用atof函数，将字符串转换为double类型
		  Push(&s,&d);
		  break;
		}      
    }
  Pop(&s,result);
  DestroyStack(&s);
  return TRUE;
}

/*
初始化栈
参数：stackSize:栈的总容量大小
typeSize:以后要入栈的单个元素的大小
*/
int InitStack(sqStack *s,unsigned stackSize,unsigned typeSize)
{
  s->base=malloc(stackSize);
  if(!s->base)
    return THEERROR;
  s->top=s->base;
  s->stackSize=stackSize;
  s->typeSize=typeSize;
  return TRUE;
}

/*
压栈
*/
int Push(sqStack *s,void *e)
{
  if((int)s->top-(int)s->base+s->typeSize>s->stackSize)
    return FALSE;
  memcpy(s->top,e,s->typeSize);
  s->top=(void*)((int)s->top+s->typeSize);
  return TRUE;
}

/*
出栈
*/
int Pop(sqStack *s,void *e)
{
  if(s->top==s->base)
    return FALSE;
  s->top=(void*)((int)s->top-(int)s->typeSize);
  memcpy(e,s->top,s->typeSize);
  return TRUE;
}

/*
清栈
*/
int ClearStack(sqStack *s)
{
  s->top=s->base;
  return TRUE;
}

/*
毁栈
*/
int DestroyStack(sqStack *s)
{
  free(s->base);
  s->top=s->base=NULL;
  s->stackSize=s->typeSize=0;
  return TRUE;
}

/*
获取已入栈元素个数
*/
int GetLen(sqStack *s)
{
  return ((int)s->top-(int)s->base)/s->typeSize;
}

/*
自定义错误处理函数
*/
int prterr(const char *fmt,... )
{
va_list argptr;
va_start(argptr, fmt);
fprintf(stderr, "%s,%s,Error:",__FILE__,__LINE__);
vfprintf(stderr,fmt,argptr);
fprintf(stderr,"errcode:%d,more facts:%s", strerror(errno),errno);
va_end(argptr);
return 0;
}
