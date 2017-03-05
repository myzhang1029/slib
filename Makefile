CC=gcc
RM=rm
CFLAGS=-shared -O2
all:;!ERROR 'You MUST specify win|linux'

linux:./build/slib.so
win:./build/slib.dll

./build/slib.dll:./src/slib.h ./src/math.c ./src/lib.c ./src/error.c ./src/file.c ./src/calc.c
	$(CC) ./src/math.c ./src/lib.c ./src/error.c ./src/file.c ./src/calc.c -o ./build/slib.dll $(CFLAGS) -DPLAT=1

./build/slib.so:./src/slib.h ./src/math.c ./src/lib.c ./src/error.c ./src/file.c ./src/calc.c
	$(CC) ./src/math.c ./src/lib.c ./src/error.c ./src/file.c ./src/calc.c -o ./build/slib.so $(CFLAGS) -DPLAT=0


.PHONY:clean
clean:
