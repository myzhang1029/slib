//�˳���������ڹ���
#include <stdlib.h>
#include <stdio.h>
int se;   //���尴������
int sa;
int sc;   
int num;
long pas;

 int main (void)
 {
      FILE * fp; 
      fp=fopen("1.bnf","r"); 
      if(fp==NULL)
        fopen("1.bnf","w");
      puts ("Welcome");  //��ӭ����
      int se = 1;
      puts ("�����û����������س�");  //��һ��
      scanf ("%d",&sa );
      if (sa == se)
      {
          puts ("1=�鿴ϵͳ,2=�齱,3=��ѯ������Ϣ,4=����Ա��");
          scanf ("%d",&sc);
          if ( sc == 1)
              puts ("12v1.1");
          else if ( sc == 3 )
              puts ("���ǹ���Ա");   //��������
          else if ( sc == 2 )
               srand (time(NULL));
               printf ("%d",rand()%6);
          else if ( sc == 4 )
               {
               printf ("����Ա�����");
               scanf ("%d"&num );
               printf ("����Ա����½����");
               scanf ("%d"&pas );
               FILE *op;
               op=fopen("1.bnf","w");
               printf ("%d"&num);
               printf ("%ld"&pas);
               fprintf (op,"%d"&num );
               fprintf (op,"%ld"&pas );
               fclose(op);
               getch();
               }
      }
      return 0;
 }