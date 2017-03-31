CC=gcc
RM=rm
CFLAGS=-shared -O2 -Wall -lm

err:;@echo -e 'Please do make PLATFORM:\n\twin:windows, MinGW\n\tunix:UNIX, GNU/Linux, BSD'

unix:slib.so
win:slib.dll

unix

include main/Makefile
include math/Makefile
include file/Makefile
include string/Makefile

.PHONY:clean
clean:
	$(RM) *.o *.a -r
