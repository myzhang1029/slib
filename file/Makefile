#child makefile

OFILES=fcopy.o fsize.o iofile.o
CFILES=fcopy.c fsize.c iofile.o
CFLAGS-WIN=-c -O2 -DPLAT=1 -l../include
CFLAGS-UNIX=-c -O2 -DPLAT=0 -l../include

main-unix:main.a.unix

main.a.unix:$(CFILES-UNIX)
	gcc $(CFLAGS-UNIX) fcopy.c -o fcopy.o
	gcc $(CFLAGS-UNIX) fsize.c -o fsize.o
	gcc $(CFLAGS-UNIX) iofile.c -o iofile.o
	ar rcs main.a.unix $(OFILES)

main-win:main.a

<<<<<<<<<<<<<<<<<Not Finished
main.a:$(CFILES-WIN)
	gcc $(CFLAGS-WIN) colorprintf.c -o colorprintf.o
	gcc $(CFLAGS-WIN) mysh.c -o mysh.o
	gcc $(CFLAGS-WIN) itoa.c -o itoa.o
	ar rcs main.a $(OFILES)
