//�˳���������ڹ���
#include <stdlib.h>
#include <stdio.h>
int se;   //���尴������
int sa;
int sc;   
int num;
int pas;

 int main (void)
 {
      FILE * fp; 
      fp=fopen("d:\\1.bnf","r"); 
      if(fp==NULL)
        fopen("1.txt","w");
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
         
      }
      return 0;
 }