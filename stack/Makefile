#child makefile

OFILES=pop.o push.o initstack.o getlen.o destorystack.o clearstack.o
CFILES=pop.c push.c initstack.c getlen.c destorystack.c clearstack.c
CFLAGS-WIN=-c -O2 -DPLAT=1 -l../include
CFLAGS-UNIX=-c -O2 -DPLAT=0 -l../include

main-unix:main.a.unix

main.a.unix:$(CFILES)
	gcc $(CFLAGS-UNIX) pop.c -o pop.o
	gcc $(CFLAGS-UNIX) push.c -o push.o
	gcc $(CFLAGS-UNIX) initstack.c -o initstack.o
	gcc $(CFLAGS-UNIX) getlen.c -o getlen.o
	gcc $(CFLAGS-UNIX) destorystack.c -o destorystack.o
	gcc $(CFLAGS-UNIX) clearstack.c -o clearstack.o
	ar rcs main.a.unix $(OFILES)

main-win:main.a


main.a:$(CFILES)
	gcc $(CFLAGS-WIN) pop.c -o pop.o
	gcc $(CFLAGS-WIN) push.c -o push.o
	gcc $(CFLAGS-WIN) initstack.c -o initstack.o
	gcc $(CFLAGS-WIN) getlen.c -o getlen.o
	gcc $(CFLAGS-WIN) destorystack.c -o destorystack.o
	gcc $(CFLAGS-WIN) clearstack.c -o clearstack.o
	ar rcs main.a $(OFILES)

