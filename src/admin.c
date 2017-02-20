
/*
	2016 ,Zhang Maiyun
	sbl administration software 2.4.0
*/
/* 包含头文件 */
#include "slib.h"

ccp ver = "3.0.0";                           /*版本号*/


int read_csbl( void );	/*CSBL解码器*/


int write_csbl( void );	/*CSBL编码器*/


void help_csbl( void );	/*CSBL帮助*/


void usage( void );/*使用方法*/ 



int main( int argc, ccp argv[] )	/* 主函数 */
{
	union main_variable
	{
		unsigned int exitt;
		unsigned int content;
		unsigned int shutdownsys;
	} m_v;
	
	if (argc>1)
	{
		if(strcmp(argv[1],"-u")==0);
		else if(strcmp(argv[1],"-h")==0)
		{
			usage();
			return 0;
		}
		else if(strcmp(argv[1],"-r")==0)
		{
			if(argc<4)
				usage();
			else
			{
				if(isrp(atoi(argv[2]),
				        atoi(argv[3]))==STRUE)
					printf("互质！");
				else
					printf("不互质！");
			}
			return 0;
		}
		else if(strcmp(argv[1],"-g")==0)
		{
			if(argc<4)
				usage();
			else
				printf("%d",gcf(atoi(argv[2]),atoi(argv[3])));
			return 0;
		}
		else if(strcmp(argv[1],"-l")==0)
		{
			if(argc<4)
				usage();
			else
				printf("%d",lcm(atoi(argv[2]),atoi(argv[3])));
			return 0;
		}
		else if(strcmp(argv[1],"-p")==0)
		{
			if(argc<4)
				usage();
			else
				prtpn(stdout,atoi(argv[2]),atoi(argv[3]));
			return 0;
		}
		else if(strcmp(argv[1],"-d")==0)
		{
			if(argc<3)
				usage();
			else
			{
				if(ispn(atoi(argv[2]))==STRUE)
					printf("是质数！");
				else
					printf("不是质数！");
			}
			return 0;
		}
		else if(strcmp(argv[1],"-c")==0)
		{
			if(argc<3)
				usage();
			else
			{
				double result;
				puts(argv[2]);
				result=calculate(argv[2]);
				printf("%s",argv[2]);
				printf("%lf",result);
			}
			return 0;
		}
		else if(strcmp(argv[1],"-f")==0)
		{
			if(argc<4)
				usage();
			else
			{
				if(fcopy(argv[2],argv[3])==STRUE)
					printf("成功！");
				else
					prterr("失败！");
			}
			return 0;
		}
		else if(strcmp(argv[1],"-o")==0)
		{
			if(argc<3)
				usage();
			else
			{
				FILE *fp=fopen(argv[2],"r");
				if(!fp)
					prterr("打开文件失败！");
				else
					prtfile(fp);
			}
			return 0;
		}
		else
		{
			usage();
			return 0;
		}
	}
	do
	{
		#if PLAT
		system("cls");
		#else
		system("clear");
		#endif
		printf( "\n1=查看系统版本\n2=产生随机数\n3=计算器\n4=自动关机\n5=解csbl\
		\n6=写csbl\n7=复制文件\n8=启动cmd\n9=csbl帮助\n10=输出指定范围内的质数\
		\n11=判断一个数是否质数\n12=判断两数是否互质\n请选择：");	/*程序主菜单*/
		scanf( "%d", &m_v.content );
		switch ( m_v.content )	/* switch case */
		{
		case (1):	/*显示软件版本*/
		{
			printf( "sbl admin %s\n", ver );
			printf( "于%s，%s发布\n", __DATE__, __TIME__ );
			break;
		}

		case (2):
		{
			unsigned int radmax = 0,radmin = 0;	/*随机数变量*/
			printf( "输入最小值：" );
			scanf( "%d",&radmin );
			printf( "输入最大值：" );
			scanf( "%d",&radmax );
			printf( "您的随机数是：%ld\n\n", randomnum(clock(),radmax,radmin) );
			break;
		}

		case (3): /*计算器*/
		{
			char	infix[BUFFERSIZE];
			fflush( stdin );
			printf( "输入算式：" );
			fgets( infix, BUFFERSIZE, stdin );
			printf( "%lf\n", calculate( infix ) );	/*使用sbllib.h中的函数进行计算*/
			break;
		}

		case (4):	/*关机器*/
		{
			#if PLAT
			system( "shutdown /t 20" );
			#else
			system( "shutdown +0.3");
			#endif
			printf( "输入1来阻止关闭系统" );
			if ( scanf( "%d", &m_v.shutdownsys ) == 1 )
			#if PLAT
				system( "shutdown /a" );
			#else
				system("shutdown -c");
			#endif
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

		case (7): /*复制文件by《21天学通C语言》*/
		{
			char source[80], destination[80];
			printf( "\n请输入所需复制的文件： " );
			fflush( stdin );
			fgets( source, 80, stdin );
			printf( "\n请输入目标：" );
			fgets( destination, 80, stdin );
			if ( fcopy( source, destination ) == STRUE )
				puts( "复制成功\n" );
			else
				prterr( "复制时出现错误\n" );
			break;
		}

		case (8):	/*向console发送命令*/
		{
			char *str;
			getmpath(argv[0],str);
			while(1)
			{
				if(mysh( str )==STRUE)
					break;
			}
			break;
		}

		case (9):/*解/编码 帮助*/
		{
			help_csbl();
			break;
		}
		case (10):	/*输出指定范围内的指数 */
		{
			int pn1,pn2;
			printf("输入最小值：");
			scanf("%d",&pn1);
			printf("\n输入最大值：");
			scanf("%d",&pn2);
			prtpn(stdout,pn1,pn2);
			break;
		}
		case (11):	/*测试一个数是否质数*/
		{
			int pn;
			printf("输入待测试数:");
			scanf("%d",&pn);
			if (ispn(pn)==STRUE)
				printf("\n是质数！\n");
			else
				printf("\n不是质数！\n");
			break;
		}
		case (12):	/*测试两个数是否互质*/
		{
			int num1,num2;
			printf("输入数一:");
			scanf("%d",&num1);
			printf("\n输入数二:");
			scanf("%d",&num2);
			if(isrp(num1,num2)==STRUE)
				printf("\n互质！\n");
			else
				printf("不互质！\n");
			break;
		}
		}/*switch(m_v.content)*/
		printf( "输入1继续:" );
		scanf( "%d", &m_v.exitt );
	}
	while ( m_v.exitt == 1 );
	return 0;
}/*main*/


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
	FILE * op = fopen( "sec.txt", "a+" );
	int stat;
	unsigned int coding = 1;	/* 解码器变量 */
	if ( !op )
		return(-1);
	printf( "输入7位十六进制码:" );         /* 解码器 */
	do
	{
		scanf( "%x", &coding );
		stat=rsbl_frame(coding);
		if(stat==STRUE)
		{
			fclose( op );
			op = NULL;
			#if PLAT
			system( "sec.txt" );
			#else
			system("vi sec.txt");
			#endif
			return 0;
		}
		else if(stat==SERROR)
			puts("错误！");
		else if(stat==SFALSE)
			continue;
		else
		{
			putchar(stat);
			putc(stat,op);
		}
		puts( "\n继续，输入ed结束：" );
	}
	while ( 1 );
}


int write_csbl( void ) /* user - sec6 */
{
	FILE * op = fopen( "sec.txt", "a+" );
	unsigned long stat;
	if ( !op )
		return(-1);
	fflush( stdin );
	printf( "输入字母、符号或数字：" );
	fprintf( op, "0x" );
	do
	{
		stat=wsbl_frame(getchar());
		if(stat==STRUE)
		{
			fclose( op );
			op = NULL;
			#if PLAT
			system( "sec.txt" );
			#else
			system("vi sec.txt");
			#endif
			return 0;
		}
		else if(stat==SERROR)
			puts("错误！");
		else if(stat==SFALSE)
			continue;
		else
		{
			printf("%lX",stat);
			fprintf(op,"%lx",stat);
		}
		puts( "\n继续，输入~结束：" );
	}
	while ( 1 );
}

void usage( void )
{
	printf("Usage:admin [options...] [arguments...]\n"
	       "options:\n\t-u 用户界面，和不键入任何内容是一样的;\n\t-h 帮助页面;"
	       "\n\t-r 判断param1,param2是否互质[param1][param2]"
	       "\n\t-g 得到param1,param2的最大公约数[param1][param2]"
	       "\n\t-l 得到param1,param2的最小公倍数[param1][param2]"
	       "\n\t-p 得到介于param1和param2之间的质数，上限32000[param1][param2]"
	       "\n\t-d 判断param1是否质数[param1]"
	       "\n\t-c 计算表达式param1的值[param1]"
	       "\n\t-f 把文件param1复制到param2[param1][param2]"
	       "\n\t-o 将文件param1完全输出到屏幕[param1]");
}
