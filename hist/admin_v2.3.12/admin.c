
/*
	2016 ,Zhang Maiyun
	sbl administration software 2.3.12
*/
/* ����ͷ�ļ� */
#include "slib\slib.h"
#pragma warning "a:" 
#pragma comment(lib,"slib\\slib.lib")

ccp ver = "2.3.12";                           /*�汾��*/


int read_csbl( void );	/*CSBL������*/


int write_csbl( void );	/*CSBL������*/


void help_csbl( void );	/*CSBL����*/


int setup( void );	/*�����ʼ������*/


void usage( void );


int main( int argc, ccp argv[], ccp *envp )	/* ������ */
{
	union main_variable
	{
		unsigned int exitt;
		unsigned int content;
		unsigned int shutdownsys;
	} m_v;
	m_v.content = setup();	/*�����ʼ��*/
	if ( m_v.content != 0 )
		prterr( "%d", m_v.content );
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
					printf("���ʣ�");
				else
					printf("�����ʣ�");
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
					printf("��������");
				else
					printf("����������");
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
				result=calculator(argv[2]);
				printf("%s",&argv[2]);
				printf("%lf",&result);
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
					printf("�ɹ���");
				else
					prterr("ʧ�ܣ�");
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
					prterr("���ļ�ʧ�ܣ�");
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
	puts( "Welcome" );	/* ��ӭ���� */
	do
	{
		printf( "\n1=�鿴ϵͳ�汾\n2=���������\n3=������\n4=�Զ��ػ�\n5=��csbl\
		\n6=дcsbl\n7=�����ļ�\n8=����cmd\n9=csbl����\n10=���ָ����Χ�ڵ�����\
		\n11=�ж�һ�����Ƿ�����\n12=�ж������Ƿ���\n��ѡ��");	/*�������˵�*/
		scanf( "%d", &m_v.content );
		switch ( m_v.content )	/* switch case */
		{
		case (1):	/*��ʾ����汾*/
		{
			printf( "sbl admin %s\n", &ver );
			printf( "��%s��%s����\n", __DATE__, __TIME__ );
			break;
		}

		case (2):
		{
			unsigned int radmax = 0,radmin = 0;	/*���������*/
			printf( "������Сֵ��" );
			scanf( "%d",&radmin );
			printf( "�������ֵ��" );
			scanf( "%d",&radmax );
			printf( "����������ǣ�%d\n\n", random(clock(),radmax,radmin) );
			break;
		}

		case (3): /* ������ */
		{
			char	infix[BUFFERSIZE];
			fflush( stdin );
			printf( "������ʽ��" );
			fgets( infix, BUFFERSIZE, stdin );
			printf( "%lf\n", calculator( infix ) );	/*ʹ��sbllib.h�еĺ������м���*/
			break;
		}

		case (4):	/*�ػ���*/
		{
			system( "shutdown /t 20" );
			printf( "����1����ֹ�ر�ϵͳ" );
			if ( scanf( "%d", &m_v.shutdownsys ) == 1 )
				system( "shutdown /a" );
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

		case (7): /*�����ļ�by��21��ѧͨC���ԡ�*/
		{
			char source[80], destination[80];
			printf( "\n���������踴�Ƶ��ļ��� " );
			fflush( stdin );
			fgets( source, 80, stdin );
			printf( "\n������Ŀ�꣺" );
			fgets( destination, 80, stdin );
			if ( fcopy( source, destination ) == STRUE )
				puts( "���Ƴɹ�\n" );
			else
				prterr( "����ʱ���ִ���\n" );
			break;
		}

		case (8):	/*��console��������*/
		{
			while(1)
			{
				if(mycmd( argv[0] )==STRUE)
					break;
			}
			break;
		}

		case (9):/*��/���� ����*/
		{
			help_csbl();
			break;
		}
		case (10):	/*���ָ����Χ�ڵ�ָ�� */
		{
			int pn1,pn2;
			printf("������Сֵ��");
			scanf("%d",&pn1);
			printf("\n�������ֵ��");
			scanf("%d",&pn2);
			prtpn(stdout,pn1,pn2);
			break;
		}
		case (11):	/*����һ�����Ƿ�����*/
		{
			int pn;
			printf("�����������:");
			scanf("%d",&pn);
			if (ispn(pn)==STRUE)
				printf("\n��������\n");
			else
				printf("\n����������\n");
			break;
		}
		case (12):	/*�����������Ƿ���*/
		{
			int num1,num2;
			printf("������һ:");
			scanf("%d",&num1);
			printf("\n��������:");
			scanf("%d",&num2);
			if(isrp(num1,num2)==STRUE)
				printf("\n���ʣ�\n");
			else
				printf("�����ʣ�\n");
			break;
		}
		}/*switch(m_v.content)*/
		printf( "����1����:" );
		scanf( "%d", &m_v.exitt );
		system("cls");
	}
	while ( m_v.exitt == 1 );
	return 0;
}/*main*/


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
	FILE * op = fopen( "sec.txt", "a+" );
	int stat;
	unsigned int coding = 1;	/* ���������� */
	if ( !op )
		return(-1);
	printf( "����7λʮ��������:" );         /* ������ */
	do
	{
		scanf( "%x", &coding );
		stat=rsbl_frame(coding);
		if(stat==STRUE)
		{
			fclose( op );
			op = NULL;
			system( "sec.txt" );
			return 0;
		}
		else if(stat==SERROR)
			puts("����");
		else if(stat==SFALSE)
			continue;
		else
		{
			ptch(stat);
			ptc(stat,op);
		}
		puts( "\n����������ed������" );
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
	printf( "������ĸ�����Ż����֣�" );
	fprintf( op, "0x" );
	do
	{
		stat=wsbl_frame(gtch());
		if(stat==STRUE)
		{
			fclose( op );
			op = NULL;
			system( "sec.txt" );
			return 0;
		}
		else if(stat==SERROR)
			puts("����");
		else if(stat==SFALSE)
			continue;
		else
		{
			printf("%lX",&stat);
			fprintf(op,"%lx",&stat);
		}
		puts( "\n����������~������" );
	}
	while ( 1 );
}


int setup( void )
{
	FILE * fp;
	char title[30]= {"title SBL admin V"};
	strncat(title,ver,15);
	system( title );
	fp = fopen( "admin.sn", "w" );
	if ( !fp )
		return SERROR;
	fprintf( fp, "SBL Admin Software version\t%s\ncreated at\t%s %s", ver, __DATE__
	         , __TIME__ );
	fclose( fp );
	fp = NULL;
	return 0;
}

void usage( void )
{
	printf("Usage:admin [options...] [arguments...]\n"
	       "options:\n\t-u �û����棬�Ͳ������κ�������һ����;\n\t-h ����ҳ��;"
	       "\n\t-r �ж�param1,param2�Ƿ���[param1][param2]"
	       "\n\t-g �õ�param1,param2�����Լ��[param1][param2]"
	       "\n\t-l �õ�param1,param2����С������[param1][param2]"
	       "\n\t-p �õ�����param1��param2֮�������������32000[param1][param2]"
	       "\n\t-d �ж�param1�Ƿ�����[param1]"
	       "\n\t-c ������ʽparam1��ֵ[param1]"
	       "\n\t-f ���ļ�param1���Ƶ�param2[param1][param2]"
	       "\n\t-o ���ļ�param1��ȫ�������Ļ[param1]");
}
