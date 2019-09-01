/*
 *  sbltool.c - Executable tool of the slib, preceded by the admin project
 *
 *  Copyright (C) 2016-present Zhang Maiyun
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

#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <slib.h>
#include <slib/getopt.h>
#include <slib/math.h>
#include <slib/stack.h>

const char *ver = "4.0.3";

void usage(void);

void eio(void);

int ui()
{
    int num1, num2;
    signed char selection = 0;
    printf("sbltool  Copyright (C) 2016-present Zhang Maiyun\n"
           "This program comes with ABSOLUTELY NO WARRANTY.\n"
           "This is free software, and you are welcome to redistribute it\n"
           "under certain conditions; visit <https://www.gnu.org/licenses/> "
           "for details.\n");
helpme:
    printf("1: Print program version\n"
           "2: Prime numbers in a range\n"
           "3: Primality test\n"
           "4: Coprime test\n");
    for (;;)
    {
        printf("(admin) ");
        fflush(stdin);
    reparse:
        selection = getchar();
        /* eof or error */
        if (selection == EOF)
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
                printf("sbl admin %s\n", ver);
                printf("Build %s，%s\n", __DATE__, __TIME__);
                break;
            case '2':
                printf("Minimum: ");
                if (scanf("%d", &num1) != 1)
                    eio();
                printf("Maximum: ");
                if (scanf("%d", &num2) != 1)
                    eio();
                slib_prtpn(num1, num2);
                break;
            case '3':
                printf("Which number to test: ");
                if (scanf("%d", &num1) != 1)
                    eio();
                if (slib_ispn(num1) == 1)
                    printf("Is a prime number!\n");
                else
                    printf("Not a prime number!\n");
                break;
            case '4':
                printf("First number: ");
                if (scanf("%d", &num1) != 1)
                    eio();
                printf("Second number: ");
                if (scanf("%d", &num2) != 1)
                    eio();
                if (slib_isrp(num1, num2) == 1)
                    printf("They are coprime!\n");
                else
                    printf("They are not coprime!\n");
                break;
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
int main(int argc, char *argv[])
{
    int c;
    long n1, n2;
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
                    printf("sbl admin %s\n", ver);
                    printf("Build %s，%s\n", __DATE__, __TIME__);
                    break;
                case 'r':
                    n1 = atol(optargGS);
                    n2 = atol(argv[optindGS]);
                    printf("%ld and %ld are", n1, n2);
                    if (!slib_isrp(n1, n2))
                        printf(" not");
                    puts(" coprime");
                    break;
                case 'g':
                    n1 = atol(optargGS);
                    n2 = atol(argv[optindGS]);
                    printf("gcf(%ld, %ld) = %ld\n", n1, n2, slib_gcf(n1, n2));
                    break;
                case 'l':
                    n1 = atol(optargGS);
                    n2 = atol(argv[optindGS]);
                    printf("lcm(%ld, %ld) = %ld\n", n1, n2, slib_gcf(n1, n2));
                    break;
                case 'p':
                    n1 = atol(optargGS);
                    n2 = atol(argv[optindGS]);
                    slib_prtpn(n1, n2);
                    break;
                case 'd':
                    n1 = atol(optargGS);
                    printf("%ld is", n1);
                    if (!slib_ispn(n1))
                        printf(" not");
                    puts(" a prime number");
                    break;
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
