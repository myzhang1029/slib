CC=gcc
CFLAGS=-lm -O2 -L. -lsbl
RM=rm

err:;@echo You must specify win|linux

linux:admin
win:admin.exe

admin.exe:./src/slib.h ./src/admin.c
	$(CC) $(CFLAGS) -DPLAT=1 src/admin.c  -o admin

admin:./src/slib.h ./src/admin.c
	$(CC) $(CFLAGS) -DPLAT=0 src/admin.c -o admin
.PHONY:clean
	$(RM) *.o
