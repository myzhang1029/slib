//此程序起初用于管理
#include <stdlib.h>
#include <stdio.h>
int se;   //定义按键变量
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
      puts ("Welcome");  //欢迎界面
      int se = 1;
      puts ("输入用户名，并按回车");  //第一步
      scanf ("%d",&sa );
      if (sa == se)
      {
          puts ("1=查看系统,2=抽奖,3=查询个人信息,4=增加员工");
          scanf ("%d",&sc);
          if ( sc == 1)
              puts ("12v1.1");
          else if ( sc == 3 )
              puts ("你是管理员");   //按需添加
          else if ( sc == 2 )
               srand (time(NULL));
               printf ("%d",rand()%6);
         
      }
      return 0;
 }
