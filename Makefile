CC=gcc
CFLAGS=-lm -O2 -Wall
all:;@echo -e 'Please do make PLATFORM:\n\twin:Windows, MinGW\n\tunix:UNIX, GNU/Linux, BSD'

unix:admin
win:admin.exe

admin.exe:./src/slib.h ./src/admin.c slib.dll
	$(CC) src/admin.c slib.dll  -o admin $(CFLAGS) -DPLAT=1

admin:./src/slib.h ./src/admin.c slib.so
	$(CC) src/admin.c ./slib.so  -o admin $(CFLAGS) -DPLAT=0
.PHONY:clean
	$(REMOVE) *.o
