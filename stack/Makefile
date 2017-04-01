#child makefile

OFILES=pop.o push.o initstack.o getlen.o destorystack.o clearstack.o
CFILES=pop.c push.c initstack.c getlen.c destorystack.c clearstack.c
include ../Make.cfg

stack.unix.a:$(CFILES)
	$(CC) $(CFLAGS-UNIX) pop.c -o pop.o
	$(CC) $(CFLAGS-UNIX) push.c -o push.o
	$(CC) $(CFLAGS-UNIX) initstack.c -o initstack.o
	$(CC) $(CFLAGS-UNIX) getlen.c -o getlen.o
	$(CC) $(CFLAGS-UNIX) destorystack.c -o destorystack.o
	$(CC) $(CFLAGS-UNIX) clearstack.c -o clearstack.o
	ar rcs stack.unix.a $(OFILES)


stack.a:$(CFILES)
	$(CC) $(CFLAGS-WIN) pop.c -o pop.o
	$(CC) $(CFLAGS-WIN) push.c -o push.o
	$(CC) $(CFLAGS-WIN) initstack.c -o initstack.o
	$(CC) $(CFLAGS-WIN) getlen.c -o getlen.o
	$(CC) $(CFLAGS-WIN) destorystack.c -o destorystack.o
	$(CC) $(CFLAGS-WIN) clearstack.c -o clearstack.o
	ar rcs stack.a $(OFILES)

