/* �˳���������ڹ��� */
#include <stdlib.h>
#include <stdio.h>
#include<ctype.h> 
int	se; /* ���尴������ */
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
	puts( "Welcome" );      /* ��ӭ���� */
	int se = 1;
	puts( "�����û����������س�" );   /* ��һ�� */
	scanf( "%d", &sa );
	if ( sa == se )
	{
	    puts ("�����������");
		scanf ("%d",&pse) ;
		if (pse == 173643)
		{
		puts( "1=�鿴ϵͳ,2=�齱,3=��ѯ������Ϣ,4=����Ա��" );
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
				puts( "���ǹ���Ա" );  /*������� */
		}
		else if ( sc == 4 )
		{
			printf( "����Ա�����" );
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
			printf( "1=�鿴ϵͳ��2=�齱��3=������" );
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
				printf ("Sorry���ݲ�֧��");
			}
		    	
		}
	}
    return(0);
}
