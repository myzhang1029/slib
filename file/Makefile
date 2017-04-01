#child makefile

OFILES=fcopy.o fsize.o iofile.o
CFILES=fcopy.c fsize.c iofile.o
include ../Make.cfg

stack.unix.a:$(CFILES-UNIX)
	$(CC) $(CFLAGS-UNIX) fcopy.c -o fcopy.o
	$(CC) $(CFLAGS-UNIX) fsize.c -o fsize.o
	$(CC) $(CFLAGS-UNIX) iofile.c -o iofile.o
	ar rcs stack.unix.a $(OFILES)

stack.a:$(CFILES-WIN)
	$(CC) $(CFLAGS-WIN) fcopy.c -o fcopy.o
	$(CC) $(CFLAGS-WIN) fsize.c -o fsize.o
	$(CC) $(CFLAGS-WIN) iofile.c -o iofile.o
	ar rcs stack.a $(OFILES)
