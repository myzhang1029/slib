#child makefile

OFILES=colorprintf.o mysh.o itoa.o getch.o sbl.o randomnum.o error.o
CFILES=colorprintf.c mysh.c itoa.c getch.c sbl.c randomnum.c error.c
include ../Make.cfg

main.unix.a:$(CFILES)
	$(CC) $(CFLAGS-UNIX) colorprintf.c -o colorprintf.o
	$(CC) $(CFLAGS-UNIX) mysh.c -o mysh.o
	$(CC) $(CFLAGS-UNIX) itoa.c -o itoa.o
	$(CC) $(CFLAGS-UNIX) getch.c -o getch.o
	$(CC) $(CFLAGS-UNIX) sbl.c -o sbl.o
	$(CC) $(CFLAGS-UNIX) randomnum.c -o randomnum.o
	$(CC) $(CFLAGS-UNIX) error.c -o error.o
	ar rcs main.unix.a $(OFILES)

main.a:$(CFILES)
	$(CC) $(CFLAGS-WIN) colorprintf.c -o colorprintf.o
	$(CC) $(CFLAGS-WIN) mysh.c -o mysh.o
	$(CC) $(CFLAGS-WIN) itoa.c -o itoa.o
	$(CC) $(CFLAGS-WIN) getch.c -o getch.o
	$(CC) $(CFLAGS-WIN) sbl.c -o sbl.o
	$(CC) $(CFLAGS-WIN) randomnum.c -o randomnum.o
	$(CC) $(CFLAGS-WIN) error.c -o error.o
	ar rcs main.a $(OFILES)

