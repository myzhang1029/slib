#include <stdio.h>/* ����ͷ�ļ� */
#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <sbl.h>
#define sleep Sleep 
#define PASW 173643/*�����������*/
#define PASC 0XAF6576/*csbl��������*/
int	sa;/* �û������� */
int	sc;/* ����ѡ����� */
int sd;/*����������*/ 
int	se;/* �ص�һ������ */
int sf; /* ��/���������� */
int	sg;/* ��/�������������� */
int	num;/* �û������ */
int	pse;/* ������� */
float x;/* ����������1*/
float y;/* ����������2*/ 
int main( void )/* ������ */
{
	puts( "Welcome" );/* ��ӭ���� */
first:
	puts( "�����û�����1=����Ա��2=�û��������س�" );        /* ��һ�� :�û����ǹ���Ա*/
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
	if ( sa == 1 )                          /* ����Ա������ */
	{
		puts( "�����������" );
		scanf( "%d", &pse );
		if ( pse != PASW )              /* ��������������� */
		{
			puts( "�������룡" );
			goto first;
		}
		if ( pse == PASW )
		{
administration:
			puts( "1=�鿴ϵͳ,2=�齱,3=��ѯ������Ϣ,4=����Ա��" );  /* ������ȷ��4ѡ�� */
			scanf( "%d", &sc );
			if ( sc == 1 )                          /* �汾�� */
				puts( "12v1.3.6" );
			else if ( sc == 2 )                     /* �齱����������� */
			{
				srand( time( NULL ) );
				printf( "%d", rand() % 10 );
			}else if ( sc == 3 )
			{
				puts( "�ѵ�¼������Ա������1���س����µ�¼" );   /* ��ʾ��¼��� */
				scanf( "%d", &se );
				if ( se == 1 )
				{
					goto first;
				}
			}else if ( sc == 4 )
			{
				printf( "�����û����\n" ); /* �����û� */
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
		printf( "1=�鿴ϵͳ��2=�齱��3=������,4=�Զ��ػ�,5=��ѯ������Ϣ,\n" );       /* �û���7ѡ�� */
		puts( "6=��csbl��7=дcsbl��8=�����ļ���9=����cmd��10=csbl����" );
		scanf( "%d", &sc );
		switch ( sc )/* switch case */
		{
		case (1):
		{
			puts( "sbl admin 12v1.3.6" );/* �汾�� */
			break;
		}
		case (2):
		{
			srand( time( NULL ) );
			printf( "%d", rand() % 10 );/* �齱������� */
			break;
		}

		case (3):                                               /* ������ */
		{
			puts( "ѡ��1=�ӷ���2=������3=������4=�˷�" );
			scanf( "%d", &sd );
			switch ( sd )
			{
			case (1):
			{
				puts( "�ӷ��������" );
				printf( "��������������������λ���ÿո������" );
				scanf( "%f %f", &x, &y );
				printf( "�����%f\n", x + y );
				break;
			}
			case (2):
			{
				puts( "�����������" );
				printf( "���뱻������������������λ���ÿո������" );
				scanf( "%f %f", &x, &y );
				printf( "�����%f\n", x - y );
				break;
			}
			case (3):
			{
				puts( "�����������" );
				printf( "���뱻������������������λ���ÿո������" );
				scanf( "%f %f", &x, &y );
				printf( "�����%f\n", x / y );
				break;
			}
			case (4):
			{
				puts( "�˷��������" );
				printf( "��������������������λ���ÿո������" );
				scanf( "%f %f", &x, &y );
				printf( "�����%f\n", x * y );
				break;
			}
			}
			break;
		}

		case (4):
		{
			system( "shutdown -s" );        /* �Զ��ػ�-30sec */
			break;
		}

		case (5):
		{
			puts( "�ѵ�¼���û�������1���س����µ�¼" );    /* ��ʾ��¼��� */
			scanf( "%d", &se );
			if ( se == 1 )
			{
				goto first;
			}
			break;
		}
		case (6):
		{
			puts( "�������룺" );
			scanf( "%X", &pse );
			if ( pse != PASC )
			{
				puts( "��������!" );
				sleep(1000);
				goto first;
			}
			
			while ( 1 )
			{
				puts( "����7λ��2λʮ��������,����0xf0����" );        /* ������ */
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
						puts( "����" );
				}
				}

				puts( "\n������" );
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
			puts( "1=������������2=����������" );
			scanf( "%d", &sg );
			if ( sg == 1 )
			{
				puts( "1������csbl���������" );
				puts( "2����������ת����csbl�룬ÿ��λһ�飬����f��ȡ��f�������س�" );
				puts( "3: ���յ����������źž�������һ��" );
				puts( "4: ������Ϻ�����0xf0����Ϣ��sec.txt" );
				sleep(1000);
			}
			if ( sg == 2 )
			{
				puts( "1������csbl���������" );
				puts( "2����������ת������ĸ�����س�" );
				puts( "3: ���յ����������źž�������һ��" );
				puts( "4: ������Ϻ�����0xf0����Ϣ��sec.txt" );
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
	puts("1=�˳���2=�ص���һ��");
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
		puts("�����䣡��");
	 goto e;
	}
	return(0);
}
