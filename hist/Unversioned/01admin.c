/* 此程序起初用于管理 */
#include <stdlib.h>
#include <stdio.h>
#include<ctype.h> 
int	se; /* 定义按键变量 */
int	sa;
int	sc;
int	num;
long pse; 

int main( void )
{
	FILE * fp;
	fp = fopen( "1.bnf", "r" );
	if ( fp == NULL )
		fopen( "1.bnf", "w" );
	puts( "Welcome" );      /* 欢迎界面 */
	int se = 1;
	puts( "输入用户名，并按回车" );   /* 第一步 */
	scanf( "%d", &sa );
	if ( sa == se )
	{
	    puts ("输入管理密码");
		scanf ("%d",&pse) ;
		if (pse == 173643)
		{
		puts( "1=查看系统,2=抽奖,3=查询个人信息,4=增加员工" );
		scanf( "%d", &sc );
		if ( sc == 1 )
			puts( "12v1.1" );
		else if ( sc == 2 )
		{
			srand( time( NULL ) );
		    printf( "%d", rand() % 6 );
		}
			
		else if ( sc == 3 )
		{
				puts( "你是管理员" );  /*按需添加 */
		}
		else if ( sc == 4 )
		{
			printf( "输入员工编号" );
			scanf( "%d" ,& num );
			FILE *op;
			op = fopen( "1.bnf", "w" );
			printf( "%d" ,& num );
			fprintf( op, "%d", & num );
			fclose( op );
			getch();
		}
		}
			
	}
	if ( sa != se )
	{
		if ( sa == 2 || sa == 3 || sa == 4 || sa == 5 || sa == 6 || sa == 7 || sa == 8 || sa == 9 || sa == 10 || sa == 11 || sa == 12 || sa == 13 || sa == 14 || sa == 15 || sa == 16 || sa == 17 || sa == 18 || sa == 19 || sa == 20 || sa == 21 )
		{
			printf( "1=查看系统，2=抽奖，3=计算器" );
			scanf( "%d" ,& sc );
			if ( sc == 1 )
			{
					puts( "sbl admin 12v1.1" );
			}
			if ( sc == 2 )
			{
			    srand( time( NULL ) );
			}
			printf( "%d", rand() % 6 );
			if ( sc == 3 )
			{
				printf ("Sorry！暂不支持");
			}
		    	
		}
	}
    return(0);
}
