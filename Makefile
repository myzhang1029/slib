CC=gcc
RM=rm
CFLAGS=-shared -O2

all:;@echo Please do make PLATFORM:\
win:windows, MinGW, Cygwin; unix:UNIX, GNU/Linux, BSD

unix:slib.so
win:slib.dll

slib.dll:./src/slib.h ./src/math.c ./src/lib.c ./src/error.c ./src/file.c ./src/calc.c
	$(CC) ./src/math.c ./src/lib.c ./src/error.c ./src/file.c ./src/calc.c -o slib.dll $(CFLAGS) -DPLAT=1

slib.so:./src/slib.h ./src/math.c ./src/lib.c ./src/error.c ./src/file.c ./src/calc.c
	$(CC) ./src/math.c ./src/lib.c ./src/error.c ./src/file.c ./src/calc.c -o slib.so $(CFLAGS) -DPLAT=0


.PHONY:clean
clean:
	$(RM) *.o
