//�˳���������ڹ���
#include <stdlib.h>
#include <stdio.h>
int se;   //���尴������
int sa;
int sc;   
int num;
long pas;
long pse;

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
      if ( sa == se )
      {
          puts ("�����������");
          scanf ("%d"& pse );
          if ( pse ==192818 )
              puts ("1=�鿴ϵͳ,2=�齱,3=��ѯ������Ϣ,4=����Ա��");
              scanf ("%d",&sc);
              if ( sc == 1)
              puts ("12v1.1");
              else if ( sc == 3 )
                  puts ("���ǹ���Ա");   //�������
              else if ( sc == 2 )
                   srand (time(NULL));
                   printf ("%d",rand()%6);
              else if ( sc == 4 )
               {
                   printf ("����Ա�����");
                   scanf ("%d"&num );
                   FILE *op;
                   op=fopen("1.bnf","w");
                   printf ("%d"&num);
                   fprintf (op,"%d"&num );
                   fclose(op);
                   getch();
                }
      }
      if ( sa != se )
      {        
              if ( sa == 2 || sa == 3 || sa == 4 || sa == 5 || sa == 6 || sa == 7 || sa == 8 || sa == 9 || sa == 10 || sa == 11 || sa == 12 )
              {
                 printf ("1=�鿴ϵͳ��2=�齱��3=������");
                 scanf ("%d" &sc);
                 if ( sc == 1 )
                    puts ("12v1.1");
                 if ( sc == 2 )
                    srand (time(NULL));
                    printf ("%d",rand()%6);
                 if ( sc == 3 )
                 {
                    char token[61]; /*��ű��ʽ�ַ���������*/ 
                    int n=0; 
                    void error(void) /*���������*/ 
                    { 
                       printf("ERROR!\n"); 
                       exit(1); 
                    } 
                    void match(char expected) /*����ַ�ƥ��ĺ���*/ 
                   { 
                    if(token[n]==expected) 
token[++n]=getchar(); 
else error(); 
} 
double term(void); /*����˳��ĺ���*/ 
double factor(void); /*�������ź����ֵĺ���*/ 
double exp(void) /*����Ӽ��ĺ���*/ 
{ 
double temp=term(); 
while((token[n]=='+')||(token[n]=='-')) 
switch(token[n]) 
{ 
case'+':match('+'); 
temp+=term(); 
break; 
case'-':match('-'); 
temp-=term(); 
break; 
} 
return temp; 
} 
double term(void) 
{ 
double div; 
double temp=factor(); 
while((token[n]=='*')||(token[n]=='/')) 
switch(token[n]) 
{ 
case'*':match('*'); 
temp*=factor(); 
break; 
case'/':match('/'); 
div=factor(); 
if(div==0) /*�������Ϊ������*/ 
{ 
printf("The divisor is zero!\n"); 
exit(1); 
} 
temp/=div; 
break; 
} 
return temp; 
} 
double factor(void) 
{ 
double temp; 
char number[61]; 
int i=0; 
if(token[n]=='(') 
{ 
match('('); 
temp=exp(); 
match(')'); 
} 
else if(isdigit(token[n])||token[n]=='.') 
{ 
while(isdigit(token[n])||token[n]=='.') /*���ַ���ת��Ϊ������*/ 
{ 
number[i++]=token[n++]; 
token[n]=getchar(); 
} 
number[i]='\0'; 
temp=atof(number); 
} 
else error(); 
return temp; 
} 
main() 
{ 
double result; 
FILE *data=fopen("61590_4.dat","at"); 
if(data==NULL) 
data=fopen("61590_4.dat","wt"); 
if(data==NULL) 
return 0; 
token[n]=getchar(); 
result=exp(); 
if(token[n]=='\n') 
{ 
token[n]='\0'; 
printf("%s=%g\n",token,result); 
fprintf(data,"%s=%g\n",token,result); 
} 
else error(); 
fclose(data); 
return 0; 
getch(); 
}    //�������������

      return 0;
 }
