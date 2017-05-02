#Sub Makefile for stack mod

include ../config.mk

.PHONY:win unix stack.a-unix stack.a-win
win:stack.a-win
unix:stack.a-unix

stack.a-win:push.c pop.c getlen.c clearstack.c initstack.c destorystack.c
	@echo CC push.o
	@$(CC) $(CFLAGS-WIN) push.c -o push.o
	@echo CC pop.o
	@$(CC) $(CFLAGS-WIN) pop.c -o pop.o
	@echo CC getlen.o
	@$(CC) $(CFLAGS-WIN) getlen.c -o getlen.o
	@echo CC clearstack.o
	@$(CC) $(CFLAGS-WIN) clearstack.c -o clearstack.o
	@echo CC initstack.o
	@$(CC) $(CFLAGS-WIN) initstack.c -o initstack.o
	@echo CC destroystack.o
	@$(CC) $(CFLAGS-WIN) destorystack.c -o destorystack.o
	@echo AR stack.a
	@ar rcs ../stack.a push.o pop.o getlen.o clearstack.o initstack.o destorystack.o
  
stack.a-unix:push.c pop.c getlen.c clearstack.c initstack.c destorystack.c
	@echo CC push.o
	@$(CC) $(CFLAGS-UNIX) push.c -o push.o
	@echo CC pop.o
	@$(CC) $(CFLAGS-UNIX) pop.c -o pop.o
	@echo CC getlen.o
	@$(CC) $(CFLAGS-UNIX) getlen.c -o getlen.o
	@echo CC clearstack.o
	@$(CC) $(CFLAGS-UNIX) clearstack.c -o clearstack.o
	@echo CC initstack.o
	@$(CC) $(CFLAGS-UNIX) initstack.c -o initstack.o
	@echo CC destroystack.o
	@$(CC) $(CFLAGS-UNIX) destorystack.c -o destorystack.o
	@echo AR stack.a
	@ar rcs ../stack.a push.o pop.o getlen.o clearstack.o initstack.o destorystack.o
