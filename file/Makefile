#Sub Makefile for file mod

include ../config.mk

.PHONY:win unix file.a-unix file.a-win
win:file.a-win
unix:file.a-unix

file.a-win:fcopy.c fsize.c iofile.c
	@echo CC fcopy.o
	@$(CC) $(CFLAGS-WIN) fcopy.c -o fcopy.o
	@echo CC fsize.o
	@$(CC) $(CFLAGS-WIN) fsize.c -o fsize.o
	@echo CC iofile.o
	@$(CC) $(CFLAGS-WIN) iofile.c -o iofile.o
	@echo AR file.a
	@ar rcs ../file.a fcopy.o fsize.o iofile.o

file.a-unix:fcopy.c fsize.c iofile.c
	@echo CC fcopy.o
	@$(CC) $(CFLAGS-UNIX) fcopy.c -o fcopy.o
	@echo CC fsize.o
	@$(CC) $(CFLAGS-UNIX) fsize.c -o fsize.o
	@echo CC iofile.o
	@$(CC) $(CFLAGS-UNIX) iofile.c -o iofile.o
	@echo AR file.a
	@ar rcs ../file.a fcopy.o fsize.o iofile.o
