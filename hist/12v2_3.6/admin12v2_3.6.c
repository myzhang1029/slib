/*2016 sbl administration software 12 v 2_3.6 */
/* ����ͷ�ļ� */
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "sbllib.h"

const char ver [10] = { "12v2_3.6" };                           /*�汾��*/


int read_csbl( void );	/*CSBL������*/


int write_csbl( void );	/*CSBL������*/


void help_csbl( void );	/*CSBL����*/


int setup( void );	/*�����ʼ������*/


int main( int argc, char * argv[], char * envp[] )	/* ������ */
{
	unsigned int	exitt = 1;	/* �˳����� */
	unsigned int	content = 0;	/* ����ѡ����� */
	content = setup();	/*�����ʼ��*/
	if ( content != 0 )
		prterr( "%d", content );
	puts( "Welcome" );	/* ��ӭ���� */
	do
	{
		printf( "\n1=�鿴ϵͳ�汾\n2=���������\n3=������\n4=�Զ��ػ�\n5=��csbl\
		\n6=дcsbl\n7=�����ļ�\n8=����cmd\n9=csbl����\n��ѡ��");	/*�������˵�*/
		scanf( "%d", &content );
		switch ( content )	/* switch case */
		{
		case (1):
		{
			printf( "sbl admin %s\n", &ver );	/* �汾�� */
			printf( "��%s��%s����\n", __DATE__, __TIME__ );
			break;
		}

		case (2):
		{
			unsigned int rad = 0;	/*���������*/
			printf( "�������ֵ��" );
			scanf( "%d", &rad );
			srand( time( NULL ) );
			printf( "����������ǣ�%d\n\n", rand() % rad );
			break;
		}

		case (3): /* ������ */
		{
			double	result;
			char	infix[BUFFERSIZE];
			fflush( stdin );
			printf( "������ʽ��" );
			fgets( infix, BUFFERSIZE, stdin );
			printf( "%lf\n", calculator( infix ) );	/*ʹ��sbllib.h�еĺ������м���*/
			break;
		}

		case (4):
		{
			system( "shutdown -s" ); /* �Զ��ػ�-30s */
			printf( "����1����ֹ�ر�ϵͳ" );
			if ( scanf( "%d", &exitt ) == 1 )
				system( "shutdown -a" );
			break;
		}

		case (5):	/*������*/
		{
			if ( read_csbl() == -1 )
				prterr( "�޷����ļ���" );
			break;
		}

		case (6):	/*������*/
		{
			if ( write_csbl() == -1 )
				prterr( "�޷����ļ���" );
			break;
		}

		case (7):
		{
			char source[80], destination[80];
			printf( "\n���������踴�Ƶ��ļ��� " );
			fflush( stdin );
			fgets( source, 80, stdin );
			printf( "\n������Ŀ�꣺" );
			fgets( destination, 80, stdin );
			if ( file_copy( source, destination ) == 0 )
				puts( "���Ƴɹ�\n" );
			else
				prterr( "����ʱ���ִ���\n" );
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
		printf( "����1����:" );
		scanf( "%d", &exitt );
	}
	while ( exitt == 1 );
	return(0);
}


void help_csbl( void ) 	/* user - sec9 */
{
	unsigned int code_help;	/* �������� */
	puts( "1=������������2=����������" );
	scanf( "%d", &code_help );
	if ( code_help == 1 )
	{
		puts( "1: ����csbl���������" );
		puts( "2: ��������ת����csbl�룬ÿ��λһ�飬���س�" );
		puts( "3: ���յ����������źž�������һ��" );
		puts( "4: ������Ϻ�����ed����Ϣ��sec.txt" );
	}
	if ( code_help == 2 )
	{
		puts( "1: ����csbl���������" );
		puts( "2: ��������ת������ĸ�����֣����س�" );
		puts( "3: ���յ����������źž�������һ��" );
		puts( "4: ������Ϻ�����~����Ϣ��sec.txt" );
	}
}


int read_csbl( void )	/* user - sec5 */
{
	unsigned int	coding = 1;	/* ���������� */
	FILE * op = fopen( "sec.txt", "a" );
	if ( !op )
		return(-1);
	printf( "����7λʮ��������:" );         /* ������ */
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
			puts( "����" );
		}
		}
		puts( "\n����������ed������" );
	}
	while ( 1 );
}


int write_csbl( void ) /* user - sec6 */
{
	FILE * op = fopen( "sec.txt", "a" );
	if ( !op )
		return(-1);
	fflush( stdin );
	printf( "������ĸ�����Ż����֣�" );
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
			puts( "����" );
		}
		}
		puts( "\n����������~������" );
	}
	while ( 1 );
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


