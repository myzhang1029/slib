
/*
 *  admin.c – The admin project
 *
 *  Copyright (C) 2016, 2017 Zhang Maiyun
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU  General Public License as published by
 *  the Free Software Foundation; either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
/* 包含头文件 */
#include "slib.h"
#include <string.h>
#include <stdlib.h>
#include <time.h>
ccp ver = "3.2.1";                           /*版本号*/

void usage( void );/*使用方法*/ 


int main( int argc, const char *argv[] )	/* 主函数 */
{
	union main_variable
	{
		unsigned int content;
		unsigned int shutdownsys;
	} m_v;
	//char *soptions=":hr:g:l:p:d:c:";
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
				if(isrp(atol(argv[2]),
				        atol(argv[3]))==STRUE)
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
				printf("%lu",gcf(atol(argv[2]),atol(argv[3])));
			return 0;
		}
		else if(strcmp(argv[1],"-l")==0)
		{
			if(argc<4)
				usage();
			else
				printf("%lu",lcm(atol(argv[2]),atol(argv[3])));
			return 0;
		}
		else if(strcmp(argv[1],"-p")==0)
		{
			if(argc<4)
				usage();
			else
				prtpn(stdout,atol(argv[2]),atol(argv[3]));
			return 0;
		}
		else if(strcmp(argv[1],"-d")==0)
		{
			if(argc<3)
				usage();
			else
			{
				if(ispn(atol(argv[2]))==STRUE)
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
		else
		{
			usage();
			return 0;
		}
	}
	for(;;)
	{
		printf( "\n1=查看系统版本\n2=产生随机数\n3=计算器\n4=自动关机\n5=复制文件\n6=启动cmd\n7=输出指定范围内的质数"
		"\n8=判断一个数是否质数\n9=判断两数是否互质\n请选择：");	/*程序主菜单*/
		scanf( "%d", &m_v.content );
		switch ( m_v.content )
		{
		case 1:	/*显示软件版本*/
		{
			printf( "sbl admin %s\n", ver );
			printf( "于%s，%s发布\n", __DATE__, __TIME__ );
			break;
		}

		case 2:
		{
			unsigned int radmax = 0,radmin = 0;	/*随机数变量*/
			printf( "输入最小值：" );
			scanf( "%d",&radmin );
			printf( "输入最大值：" );
			scanf( "%d",&radmax );
			printf( "您的随机数是：%ld\n\n", randomnum(clock(),radmax,radmin) );
			break;
		}

		case 3: /*计算器*/
		{
			char	infix[BUFFERSIZE];
			fflush( stdin );
			printf( "输入算式：" );
			fflush( stdin );
			fgets( infix, BUFFERSIZE, stdin );
			printf( "%lf\n", calculate( infix ) );	/*使用libsbl中的函数进行计算*/
			break;
		}

		case 4:	/*关机器*/
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

		case 5:	/*输出指定范围内的指数 */
		{
			int pn1,pn2;
			printf("输入最小值：");
			scanf("%d",&pn1);
			printf("\n输入最大值：");
			scanf("%d",&pn2);
			prtpn(stdout,pn1,pn2);
			break;
		}
		case 6:	/*测试一个数是否质数*/
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
		case 7:	/*测试两个数是否互质*/
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
		case 'q':
			return 0;
		default:
			printf("%d: Unknown option\n", m_v.content);
		}/*switch(m_v.content)*/
	}
	return 0;
}/*main*/


void usage( void )
{
	printf("Usage:admin [-u] [-h] [-r <n1> <n2>] [-g <n1> <n2>] [-l <n1> <n2>]\n"
	       "\t[-p <n1> <n2>] [-d <num>] [-c <exp>]\n"
	       "options:"
	       "\n\t-u 用户界面，和不键入任何内容是一样的;"
	       "\n\t-h 帮助页面;"
	       "\n\t-r 判断n1, n2是否互质;"
	       "\n\t-g 得到n1,n2的最大公约数;"
	       "\n\t-l 得到n1,n2的最小公倍数;"
	       "\n\t-p 得到介于n1和n2之间的质数;"
	       "\n\t-d 判断num是否质数;"
	       "\n\t-c 计算表达式的值;");
}
