//此程序起初用于管理
#include <stdlib.h>
#include <stdio.h>
int se;   //定义按键变量
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
      puts ("Welcome");  //欢迎界面
      int se = 1;
      puts ("输入用户名，并按回车");  //第一步
      scanf ("%d",&sa );
      if ( sa == se )
      {
          puts ("输入管理密码");
          scanf ("%d"& pse );
          if ( pse ==192818 )
              puts ("1=查看系统,2=抽奖,3=查询个人信息,4=增加员工");
              scanf ("%d",&sc);
              if ( sc == 1)
              puts ("12v1.1");
              else if ( sc == 3 )
                  puts ("你是管理员");   //按需添加
              else if ( sc == 2 )
                   srand (time(NULL));
                   printf ("%d",rand()%6);
              else if ( sc == 4 )
               {
                   printf ("输入员工编号");
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
                 printf ("1=查看系统，2=抽奖，3=计算器");
                 scanf ("%d" &sc);
                 if ( sc == 1 )
                    puts ("12v1.1");
                 if ( sc == 2 )
                    srand (time(NULL));
                    printf ("%d",rand()%6);
                 if ( sc == 3 )
                 {
                    char token[61]; /*存放表达式字符串的数组*/ 
                    int n=0; 
                    void error(void) /*报告错误函数*/ 
                    { 
                       printf("ERROR!\n"); 
                       exit(1); 
                    } 
                    void match(char expected) /*检查字符匹配的函数*/ 
                   { 
                    if(token[n]==expected) 
token[++n]=getchar(); 
else error(); 
} 
double term(void); /*计算乘除的函数*/ 
double factor(void); /*处理括号和数字的函数*/ 
double exp(void) /*计算加减的函数*/ 
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
if(div==0) /*处理除数为零的情况*/ 
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
while(isdigit(token[n])||token[n]=='.') /*将字符串转换为浮点数*/ 
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
}    //计算器代码结束

      return 0;
 }
