/*
 *  admin.c – The admin project
 *
 *  Copyright (C) 2016, 2017 Zhang Maiyun
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU  General Public License as published by
 *  the Free Software Foundation; either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
#include <slib.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <slib/getopt.h>
#include <slib/math.h>

const char *ver = "4.0.0";

void usage(void);
int ui()
{
    char selection = 0;
    for (;;)
    {
        printf(
            "\n1=查看系统版本\n2=产生随机数\n3=计算器\n4="
            "输出指定范围内的质数"
            "\n5=判断一个数是否质数\n6=判断两数是否互质\n请选择："); /*程序主菜单*/
        fflush(stdin);
        scanf("%c", &selection);
        switch (selection)
        {
            case '1': /* version */
            {
                printf("sbl admin %s\n", ver);
                printf("Build %s，%s\n", __DATE__, __TIME__);
                break;
            }
            case '2':
            {
                unsigned int radmax = 0, radmin = 0;
                printf("输入最小值：");
                scanf("%d", &radmin);
                printf("输入最大值：");
                scanf("%d", &radmax);
                printf("您的随机数是：%ld\n\n",
                       randomnum(clock(), radmax, radmin));
                break;
            }
            case '3': /*计算器*/
            {
                char infix[BUFFERSIZE];
                fflush(stdin);
                printf("输入算式：");
                fflush(stdin);
                fgets(infix, BUFFERSIZE, stdin);
                printf("%lf\n", calculate(infix));
                break;
            }
            case '4': /*输出指定范围内的指数 */
            {
                int pn1, pn2;
                printf("输入最小值：");
                scanf("%d", &pn1);
                printf("\n输入最大值：");
                scanf("%d", &pn2);
                slib_prtpn(pn1, pn2);
                break;
            }
            case '5': /*测试一个数是否质数*/
            {
                int pn;
                printf("输入待测试数:");
                scanf("%d", &pn);
                if (slib_ispn(pn) == STRUE)
                    printf("\n是质数！\n");
                else
                    printf("\n不是质数！\n");
                break;
            }
            case '6': /*测试两个数是否互质*/
            {
                int num1, num2;
                printf("输入数一:");
                scanf("%d", &num1);
                printf("\n输入数二:");
                scanf("%d", &num2);
                if (slib_isrp(num1, num2) == STRUE)
                    printf("\n互质！\n");
                else
                    printf("不互质！\n");
                break;
            }
            case 'q':
                return 0;
            default:
                printf("%d: Unknown option\n", selection);
        } /*switch(m_v.content)*/
    }
}

int main(int argc, const char *argv[])
{
    int c;
    char *sopts = ":uhvr:g:l:p:d:c:";
    if (argc > 1)
    {
        while ((c = getoptGS(argc, argv, sopts)) != -1)
        {
            switch (c)
            {
                case 'u':
                    return ui();
                case 'h':
                    usage();
                    return 0;
                case 'v':
                {
                    printf("sbl admin %s\n", ver);
                    printf("Build %s，%s\n", __DATE__, __TIME__);
                    break;
                }
                case 'r':
                {
                    long n1 = atol(optargGS), n2 = atol(argv[optindGS]);
                    printf("%ld and %ld are", n1, n2);
                    if (!slib_isrp(n1, n2))
                        printf(" not");
                    puts(" coprime");
                    break;
                }
                case 'g':
                {
                    long n1 = atol(optargGS), n2 = atol(argv[optindGS]);
                    printf("gcf(%ld, %ld) = %ld", n1, n2, slib_gcf(n1, n2));
                    break;
                }
                case 'l':
                {
                    long n1 = atol(optargGS), n2 = atol(argv[optindGS]);
                    printf("lcm(%ld, %ld) = %ld", n1, n2, slib_gcf(n1, n2));
                    break;
                }
                case 'p':
                {
                    long n1 = atol(optargGS), n2 = atol(argv[optindGS]);
                    slib_prtpn(n1, n2);
                    break;
                }
                case 'd':
                {
                    long n = atol(optargGS);
                    printf("%ld is", n);
                    if (!slib_ispn(n))
                        printf(" not");
                    puts(" a prime number");
                    break;
                }
                case 'c':
                case '?':
                    usage();
                    fprintf(stderr, "admin: unknown option -%c\n", optopt);
                    return 1;
                case ':':
                    usage();
                    fprintf(stderr, "admin: option -%c needs an argument\n",
                            optopt);
                    return 1;
                default:;
            }
        }
        return 0;
    }
    else
    {
        return ui();
    }
}

void usage(void)
{
    printf("Usage:\n"
           "\tadmin [-uhv] [-r <n1> <n2>] [-g <n1> <n2>] [-l <n1> <n2>]\n"
           "\t[-p <n1> <n2>] [-d <num>] [-c <exp>]\n"
           "Options:"
           "\n\t-u Interactive mode, same as no options"
           "\n\t-h Show this page."
           "\n\t-v Show version."
           "\n\t-r Show whether n1 and n2 are coprime."
           "\n\t-g Greatest common factor(divisor) of n1 and n2."
           "\n\t-l Least common multiple of n1 and n2."
           "\n\t-p Print prime numbers between n1 and n2."
           "\n\t-d Primality test."
           "\n\t-c Calculate exp.\n");
}
