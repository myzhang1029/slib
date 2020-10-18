/*
 *  sbltool.c - Executable tool of the slib, preceded by the admin project
 *
 *  Copyright (C) 2016-2020 Zhang Maiyun
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <slib.h>
#include <slib/getopt.h>
#include <slib/math.h>
#include <slib/stack.h>

#define INT_LEN 22
#define chk_fgets(s, l, f)                                                     \
    if (!fgets((s), (l), (f)))                                                 \
    exit(puts(""))

const char *ver = "4.1.0-ndless";

void usage(void);

void eio(void);

int ui()
{
    int selection = 0;
    char buffer[INT_LEN];
    printf("sbltool  Copyright (C) 2016-2020 Zhang Maiyun\n"
           "This program comes with ABSOLUTELY NO WARRANTY.\n"
           "This is free software, and you are welcome to redistribute it\n"
           "under certain conditions; visit <https://www.gnu.org/licenses/> "
           "for details.\n");
helpme:
    printf("1: Print program version\n"
           "2: Prime numbers in a range\n"
           "3: Primality test\n"
           "4: Coprime test\n"
           "5: Greatest common factor\n"
           "6: Lowest common multiple\n");
    for (;;)
    {
        printf("(admin) ");
        fflush(stdout);
        chk_fgets(buffer, INT_LEN, stdin);
        selection = strtod(buffer, NULL);
        chk_fgets(buffer, INT_LEN, stdin);
        if (selection == 0)
            /* It is a character */
            selection = buffer[0];
        switch (selection)
        {
            case '\n':
            case ' ':
                goto helpme;
            case 1:
                printf("sbl admin v%s with slib v%d.%d.%d\n", ver,
                       SBLLIB_VERSION, SBLLIB_MINOR, SBLLIB_PATCHLEVEL);
                printf("Build %s, %s\n", __DATE__, __TIME__);
                break;
            case 2:
            {
                slib_uint num1, num2;
                printf("Minimum: ");
                fflush(stdout);
                chk_fgets(buffer, INT_LEN, stdin);
                num1 = strtoslib(buffer, NULL, 0);
                chk_fgets(buffer, INT_LEN, stdin);
                printf("Maximum: ");
                fflush(stdout);
                chk_fgets(buffer, INT_LEN, stdin);
                num2 = strtoslib(buffer, NULL, 0);
                chk_fgets(buffer, INT_LEN, stdin);
                slib_prtpn(num1, num2);
                break;
            }
            case 3:
            {
                slib_uint num;
                printf("Which number to test: ");
                fflush(stdout);
                chk_fgets(buffer, INT_LEN, stdin);
                num = strtoslib(buffer, NULL, 0);
                chk_fgets(buffer, INT_LEN, stdin);
                if (slib_ispn(num) == 1)
                    printf("Is a prime number!\n");
                else
                    printf("Not a prime number!\n");
                break;
            }
            case 4:
            {
                slib_uint num1, num2;
                printf("First number: ");
                fflush(stdout);
                chk_fgets(buffer, INT_LEN, stdin);
                num1 = strtoslib(buffer, NULL, 0);
                chk_fgets(buffer, INT_LEN, stdin);
                printf("Second number: ");
                fflush(stdout);
                chk_fgets(buffer, INT_LEN, stdin);
                num2 = strtoslib(buffer, NULL, 0);
                chk_fgets(buffer, INT_LEN, stdin);
                if (slib_isrp(num1, num2) == 1)
                    printf("They are coprime!\n");
                else
                    printf("They are not coprime!\n");
                break;
            }
            case 5:
            {
                slib_uint num1, num2;
                printf("First number: ");
                fflush(stdout);
                chk_fgets(buffer, INT_LEN, stdin);
                num1 = strtoslib(buffer, NULL, 0);
                chk_fgets(buffer, INT_LEN, stdin);
                printf("Second number: ");
                fflush(stdout);
                chk_fgets(buffer, INT_LEN, stdin);
                num2 = strtoslib(buffer, NULL, 0);
                chk_fgets(buffer, INT_LEN, stdin);
                printf("gcf(%" PRIslib ", %" PRIslib ") = %" PRIslib "\n", num1,
                       num2, slib_gcf(num1, num2));
                break;
            }
            case 6:
            {
                slib_uint num1, num2;
                printf("First number: ");
                fflush(stdout);
                chk_fgets(buffer, INT_LEN, stdin);
                num1 = strtoslib(buffer, NULL, 0);
                chk_fgets(buffer, INT_LEN, stdin);
                printf("Second number: ");
                fflush(stdout);
                chk_fgets(buffer, INT_LEN, stdin);
                num2 = strtoslib(buffer, NULL, 0);
                chk_fgets(buffer, INT_LEN, stdin);
                printf("lcm(%" PRIslib ", %" PRIslib ") = %" PRIslib "\n", num1,
                       num2, slib_lcm(num1, num2));
                break;
            }
            case 'q':
                return 0;
            case 'h':
                goto helpme;
            default:
                printf("%s: Unknown option\n", buffer);
                goto helpme;
        }
    }
}
int main(int argc, char *argv[])
{
    int c;
    const char *sopts = ":uhvr:g:l:p:d:c:";
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
                    printf("sbl admin v%s with slib v%d.%d.%d\n", ver,
                           SBLLIB_VERSION, SBLLIB_MINOR, SBLLIB_PATCHLEVEL);
                    printf("Build %s, %s\n", __DATE__, __TIME__);
                    break;
                case 'r':
                {
                    slib_uint n1, n2;
                    n1 = strtoslib(optargGS, NULL, 0);
                    n2 = strtoslib(argv[optindGS], NULL, 0);
                    printf("%" PRIslib " and %" PRIslib " are", n1, n2);
                    if (!slib_isrp(n1, n2))
                        printf(" not");
                    puts(" coprime");
                    break;
                }
                case 'g':
                {
                    slib_uint n1, n2;
                    n1 = strtoslib(optargGS, NULL, 0);
                    n2 = strtoslib(argv[optindGS], NULL, 0);
                    printf("gcf(%" PRIslib ", %" PRIslib ") = %" PRIslib "\n",
                           n1, n2, slib_gcf(n1, n2));
                    break;
                }
                case 'l':
                {
                    slib_uint n1, n2;
                    n1 = strtoslib(optargGS, NULL, 0);
                    n2 = strtoslib(argv[optindGS], NULL, 0);
                    printf("lcm(%" PRIslib ", %" PRIslib ") = %" PRIslib "\n",
                           n1, n2, slib_lcm(n1, n2));
                    break;
                }
                case 'p':
                {
                    slib_uint n1, n2;
                    n1 = strtoslib(optargGS, NULL, 0);
                    n2 = strtoslib(argv[optindGS], NULL, 0);
                    slib_prtpn(n1, n2);
                    break;
                }
                case 'd':
                {
                    slib_uint n;
                    n = strtoslib(optargGS, NULL, 0);
                    printf("%" PRIslib " is", n);
                    if (!slib_ispn(n))
                        printf(" not");
                    puts(" a prime number");
                    break;
                }
                case '?':
                    usage();
                    fprintf(stderr, "admin: unknown option -%c\n", optoptGS);
                    return 1;
                case ':':
                    usage();
                    fprintf(stderr, "admin: option -%c needs an argument\n",
                            optoptGS);
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
           "Options:\n"
           "\t-u\tInteractive mode, same as no options\n"
           "\t-h\tShow this page.\n"
           "\t-v\tShow version.\n"
           "\t-r\tShow whether n1 and n2 are coprime.\n"
           "\t-g\tGreatest common factor(divisor) of n1 and n2.\n"
           "\t-l\tLeast common multiple of n1 and n2.\n"
           "\t-p\tPrint prime numbers between n1 and n2.\n"
           "\t-d\tPrimality test.\n");
}
void eio(void)
{
    fprintf(stderr, "\nHmm... You've entered something I don't know!\n");
    exit(2);
}
