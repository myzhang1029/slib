CC=gcc
CFLAGS=-lm -O2
all:;!ERROR You must specify win|linux

linux:admin
win:admin.exe

admin.exe:./src/slib.h ./src/admin.c slib.dll
	$(CC) src/admin.c slib.dll  -o admin $(CFLAGS) -DPLAT=1

admin:./src/slib.h ./src/admin.c slib.so
	$(CC) src/admin.c slib.so  -o admin $(CFLAGS) -DPLAT=0
.PHONY:clean
	$(REMOVE) *.o
