#include <stdio.h>/* 包含头文件 */
#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <sbl.h>
#define sleep Sleep 
#define PASW 173643/*程序管理密码*/
#define PASC 0XAF6576/*csbl访问密码*/
int	sa;/* 用户名变量 */
int	sc;/* 功能选项变量 */
int sd;/*计算器变量*/ 
int	se;/* 回第一步变量 */
int sf; /* 解/编码器变量 */
int	sg;/* 解/编码器帮助变量 */
int	num;/* 用户码变量 */
int	pse;/* 密码变量 */
float x;/* 计算器变量1*/
float y;/* 计算器变量2*/ 
int main( void )/* 主函数 */
{
	puts( "Welcome" );/* 欢迎界面 */
first:
	puts( "输入用户名，1=管理员，2=用户，并按回车" );        /* 第一步 :用户还是管理员*/
	scanf( "%d", &sa );
	if ( sa == 3 )
	{
		system( "start admin.com" );
		exit( 0 );
	}
	if ( sa == 4 )
		{
			system( "start void.com" );
			exit( 0 );
		}
	if ( sa == 1 )                          /* 管理员：密码 */
	{
		puts( "输入管理密码" );
		scanf( "%d", &pse );
		if ( pse != PASW )              /* 处理密码错误的情况 */
		{
			puts( "错误密码！" );
			goto first;
		}
		if ( pse == PASW )
		{
administration:
			puts( "1=查看系统,2=抽奖,3=查询个人信息,4=增加员工" );  /* 密码正确：4选项 */
			scanf( "%d", &sc );
			if ( sc == 1 )                          /* 版本号 */
				puts( "12v1.3.6" );
			else if ( sc == 2 )                     /* 抽奖：产生随机数 */
			{
				srand( time( NULL ) );
				printf( "%d", rand() % 10 );
			}else if ( sc == 3 )
			{
				puts( "已登录：管理员，输入1并回车重新登录" );   /* 显示登录情况 */
				scanf( "%d", &se );
				if ( se == 1 )
				{
					goto first;
				}
			}else if ( sc == 4 )
			{
				printf( "输入用户编号\n" ); /* 增加用户 */
				scanf( "%d", &num );
				FILE *op;
				op = fopen( "1.bnf", "a" );
				printf( "%s\n", &num );
				fprintf( op, "%s\r\n", &num );
				fclose( op );
				op = NULL;
				getch();
			}
		}
	}
	if ( sa == 2 )
	{
		int sb = 3;
		printf( "1=查看系统，2=抽奖，3=计算器,4=自动关机,5=查询个人信息,\n" );       /* 用户：7选项 */
		puts( "6=解csbl，7=写csbl，8=复制文件，9=启动cmd，10=csbl帮助" );
		scanf( "%d", &sc );
		switch ( sc )/* switch case */
		{
		case (1):
		{
			puts( "sbl admin 12v1.3.6" );/* 版本号 */
			break;
		}
		case (2):
		{
			srand( time( NULL ) );
			printf( "%d", rand() % 10 );/* 抽奖：随机数 */
			break;
		}

		case (3):                                               /* 计算器 */
		{
			puts( "选择：1=加法，2=减法，3=除法，4=乘法" );
			scanf( "%d", &sd );
			switch ( sd )
			{
			case (1):
			{
				puts( "加法运算程序" );
				printf( "输入两个加数，精度六位，用空格隔开：" );
				scanf( "%f %f", &x, &y );
				printf( "结果：%f\n", x + y );
				break;
			}
			case (2):
			{
				puts( "减法运算程序" );
				printf( "输入被减数，减数，精度六位，用空格隔开：" );
				scanf( "%f %f", &x, &y );
				printf( "结果：%f\n", x - y );
				break;
			}
			case (3):
			{
				puts( "除法运算程序" );
				printf( "输入被除数，除数，精度六位，用空格隔开：" );
				scanf( "%f %f", &x, &y );
				printf( "结果：%f\n", x / y );
				break;
			}
			case (4):
			{
				puts( "乘法运算程序" );
				printf( "输入两个因数，精度六位，用空格隔开：" );
				scanf( "%f %f", &x, &y );
				printf( "结果：%f\n", x * y );
				break;
			}
			}
			break;
		}

		case (4):
		{
			system( "shutdown -s" );        /* 自动关机-30sec */
			break;
		}

		case (5):
		{
			puts( "已登录：用户，输入1并回车重新登录" );    /* 显示登录情况 */
			scanf( "%d", &se );
			if ( se == 1 )
			{
				goto first;
			}
			break;
		}
		case (6):
		{
			puts( "输入密码：" );
			scanf( "%X", &pse );
			if ( pse != PASC )
			{
				puts( "错误密码!" );
				sleep(1000);
				goto first;
			}
			
			while ( 1 )
			{
				puts( "输入7位或2位十六进制码,输入0xf0结束" );        /* 解码器 */
				scanf( "%x", &sf );
				FILE *op;
				op = fopen( "sec.txt", "a" );
				switch ( sf )
				{
				case (0xf1):                            /* "?" */
				{
					puts( "?" );
					fprintf( op, "?" );
					break;
				}
				case (0xf2):                            /* "." */
				{
					puts( "." );
					fprintf( op, "." );
					break;
				}
				case (0x0404491):                       /* A */
				{
					printf( "a" );
					fprintf( op, "a" );
					break;
				}
				case (0x1415454):                       /* B */
				{
					puts( "b" );
					fprintf( op, "b" );
					break;
				}
				case (0x1504015):                       /* C */
				{
					puts( "c" );
					fprintf( op, "c" );
					break;
				}
				case (0x1414454):                       /* D */
				{
					puts( "d" );
					fprintf( op, "d" );
					break;
				}
				case (0x1524895):                       /* E */
				{
					puts( "e" );
					fprintf( op, "e" );
					break;
				}
				case (0x1505010):                       /* F */
				{
					puts( "f" );
					fprintf( op, "f" );
					break;
				}
				case (0x1505096):                       /* G */
				{
					puts( "g" );
					fprintf( op, "g" );
					break;
				}
				case (0x1105011):                       /* H */
				{
					puts( "h" );
					fprintf( op, "h" );
					break;
				}
				case (0x0421084):                       /* I */
				{
					puts( "i" );
					fprintf( op, "i" );
					break;
				}
				case (0x040521c):                       /* J */
				{
					puts( "j" );
					fprintf( op, "j" );
					break;
				}
				case (0x1115051):                       /* K */
				{
					puts( "k" );
					fprintf( op, "k" );
					break;
				}
				case (0x1084215):                       /* L */
				{
					puts( "l" );
					fprintf( op, "l" );
					break;
				}
				case (0x1155551):                       /* M */
				{
					printf( "m" );
					fprintf( op, "m" );
					break;
				}
				case (0x1105411):                       /* N */
				{
					puts( "n" );
					fprintf( op, "n" );
					break;
				}
				case (0x0404404):                       /* O */
				{
					puts( "o" );
					fprintf( op, "o" );
					break;
				}
				case (0x1124410):                       /* P */
				{
					puts( "p" );
					fprintf( op, "p" );
					break;
				}
				case (0x1404415):                       /* Q */
				{
					puts( "q" );
					fprintf( op, "q" );
					break;
				}
				case (0x1405055):                       /* R */
				{
					puts( "r" );
					fprintf( op, "r" );
					break;
				}
				case (0x1101011):                       /* S */
				{
					puts( "s" );
					fprintf( op, "s" );
					break;
				}
				case (0x1501004):                       /* T */
				{
					puts( "t" );
					fprintf( op, "t" );
					break;
				}
				case (0x1505404):                       /* U */
				{
					puts( "u" );
					fprintf( op, "u" );
					break;
				}
				case (0x1105415):                       /* V */
				{
					puts( "v" );
					fprintf( op, "v" );
					break;
				}
				case (0x150540a):                       /* W */
				{
					puts( "w" );
					fprintf( op, "w" );
					break;
				}
				case (0x1151011):                       /* X */
				{
					puts( "x" );
					fprintf( op, "x" );
					break;
				}
				case (0x1151084):                       /* Y */
				{
					printf( "y" );
					fprintf( op, "y" );
					break;
				}
				case (0x1511115):                       /* Z */
				{
					puts( "z" );
					fprintf( op, "z" );
					break;
				}
				default:
				{
					if ( sf == 0xf0 )
					{
						fclose( op );
						system( "sec.txt" );
						exit( 0 );
					}else
						puts( "错误！" );
				}
				}

				puts( "\n继续：" );
			}
		}
		case (8):
		{
			system( "start filecopier.com" ); 
			break;
		}
		case (9):
		{
			system( "start cmd" );
			break;
		}
		case (10):
		{
			puts( "1=解码器帮助，2=编码器帮助" );
			scanf( "%d", &sg );
			if ( sg == 1 )
			{
				puts( "1：输入csbl码访问密码" );
				puts( "2：输入所需转换的csbl码，每七位一组，遇“f”取“f几”并回车" );
				puts( "3: 接收到“继续”信号就输入下一个" );
				puts( "4: 输入完毕后输入0xf0，信息在sec.txt" );
				sleep(1000);
			}
			if ( sg == 2 )
			{
				puts( "1：输入csbl码访问密码" );
				puts( "2：输入所需转换的字母，并回车" );
				puts( "3: 接收到“继续”信号就输入下一个" );
				puts( "4: 输入完毕后输入0xf0，信息在sec.txt" );
				sleep(1000);
			}
			break;
		}
		case (EOF):
		{
			goto administration;
			break;
		}
		}
	}
	e:
	puts("1=退出，2=回到第一步");
	scanf("%d",&se);
	if( se == 1 )
	{
		sleep( 1000 );
		exit(0);
	} 
	else if( se == 2 )
	{
		goto first;
	}
	else
	{
		puts("请重输！！");
	 goto e;
	}
	return(0);
}
