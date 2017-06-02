CC=gcc
RM=rm
CFLAGS=-lm -O2 -Wall -lsbl

.PHONY:err unix win clean
err:
	@echo 'Please do ./configure'
	@exit 1

unix:admin
win:admin.exe

admin.exe:admin.c 
	$(CC) -o admin $(CFLAGS) -DPLAT=1 admin.c

admin:admin.c
	$(CC) -o admin $(CFLAGS) -DPLAT=0 admin.c
clean:
	$(RM) *.o
