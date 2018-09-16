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
#include <slib/stack.h>

const char *ver = "4.0.0";

void usage(void);
int ui()
{
    char selection = 0;
helpme:
    printf("1: Pseudo-random number genertor\n"
           "2: Calculator\n"
           "3: Prime numbers in a range\n"
           "4: Primality test\n"
           "5: Coprime test\n");
    for (;;)
    {
        printf("(admin) ");
        fflush(stdin);
reparse:
        selection = getchar();
        if (feof(stdin))
        {
            puts("");
            return 0;
        }
        switch (selection)
        {
            case '\n':
            case ' ':
                goto reparse;
            case '1':
            {
                unsigned int radmax = 0, radmin = 0;
                printf("Minimum: ");
                scanf("%d", &radmin);
                printf("Maximum: ");
                scanf("%d", &radmax);
                printf("Output: %ld\n", randomnum(clock(), radmax, radmin));
                break;
            }
            case '2': /*计算器*/
            {
                char infix[BUFFERSIZE];
                fflush(stdin);
                printf("Enter expression: ");
                fflush(stdin);
                fgets(infix, BUFFERSIZE, stdin);
                printf("Result: %lf\n", calculate(infix));
                break;
            }
            case '3': /*输出指定范围内的指数 */
            {
                int pn1, pn2;
                printf("Minimum: ");
                scanf("%d", &pn1);
                printf("Maximum: ");
                scanf("%d", &pn2);
                slib_prtpn(pn1, pn2);
                break;
            }
            case '4': /*测试一个数是否质数*/
            {
                int pn;
                printf("Which number to test: ");
                scanf("%d", &pn);
                if (slib_ispn(pn) == STRUE)
                    printf("Is a prime number!\n");
                else
                    printf("Not a prime number!\n");
                break;
            }
            case '5': /*测试两个数是否互质*/
            {
                int num1, num2;
                printf("First number: ");
                scanf("%d", &num1);
                printf("Second number: ");
                scanf("%d", &num2);
                if (slib_isrp(num1, num2) == STRUE)
                    printf("They are coprime!\n");
                else
                    printf("They are not coprime!\n");
                break;
            }
            case 'q':
                return 0;
            case 'h':
                goto helpme;
            default:
                printf("%c: Unknown option\n", selection);
                goto helpme;
        }
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
                    printf("gcf(%ld, %ld) = %ld\n", n1, n2, slib_gcf(n1, n2));
                    break;
                }
                case 'l':
                {
                    long n1 = atol(optargGS), n2 = atol(argv[optindGS]);
                    printf("lcm(%ld, %ld) = %ld\n", n1, n2, slib_gcf(n1, n2));
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
                {
                    printf("%lf\n", calculate(optargGS));
                    break;
                }
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
