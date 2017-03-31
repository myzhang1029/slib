#child makefile

OFILES=colorprintf.o mysh.o itoa.o getch.o sbl.o randomnum.o
CFILES=colorprintf.c mysh.c itoa.c getch.c sbl.c randomnum.c
CFLAGS-WIN=-c -O2 -DPLAT=1 -l../include
CFLAGS-UNIX=-c -O2 -DPLAT=0 -l../include

main-unix:main.a.unix

main.a.unix:$(CFILES-UNIX)
	gcc $(CFLAGS-UNIX) colorprintf.c -o colorprintf.o
	gcc $(CFLAGS-UNIX) mysh.c -o mysh.o
	gcc $(CFLAGS-UNIX) itoa.c -o itoa.o
	gcc $(CFLAGS-UNIX) getch.c -o getch.o
	gcc $(CFLAGS-UNIX) sbl.c -o sbl.o
	gcc $(CFLAGS-UNIX) randomnum.c -o randomnum.o
	ar rcs main.a.unix $(OFILES)

main-win:main.a


main.a:$(CFILES-WIN)
	gcc $(CFLAGS-WIN) colorprintf.c -o colorprintf.o
	gcc $(CFLAGS-WIN) mysh.c -o mysh.o
	gcc $(CFLAGS-WIN) itoa.c -o itoa.o
	gcc $(CFLAGS-WIN) getch.c -o getch.o
	gcc $(CFLAGS-WIN) sbl.c -o sbl.o
	gcc $(CFLAGS-WIN) randomnum.c -o randomnum.o
	ar rcs main.a $(OFILES)
