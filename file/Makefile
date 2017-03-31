#child makefile

OFILES=fcopy.o fsize.o iofile.o
CFILES=fcopy.c fsize.c iofile.o
CFLAGS-WIN=-c -O2 -DPLAT=1 -l../include
CFLAGS-UNIX=-c -O2 -DPLAT=0 -l../include

stack.unix.a:$(CFILES-UNIX)
	gcc $(CFLAGS-UNIX) fcopy.c -o fcopy.o
	gcc $(CFLAGS-UNIX) fsize.c -o fsize.o
	gcc $(CFLAGS-UNIX) iofile.c -o iofile.o
	ar rcs stack.unix.a $(OFILES)

stack.a:$(CFILES-WIN)
	gcc $(CFLAGS-WIN) fcopy.c -o fcopy.o
	gcc $(CFLAGS-WIN) fsize.c -o fsize.o
	gcc $(CFLAGS-WIN) iofile.c -o iofile.o
	ar rcs stack.a $(OFILES)
