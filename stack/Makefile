#Sub Makefile for stack mod

include ../config.mk

.PHONY:win unix stack.a-unix stack.a-win
win:stack.a-win
unix:stack.a-unix

stack.a-win:push.c pop.c getlen.c clearstack.c initstack.c destroystack.c
	@echo CC push.o
	@$(CC) $(CFLAGS-WIN) push.c -o push.o
  @echo CC pop.o
  @$(CC) $(CFLAGS-WIN) pop.c -o pop.o
  @echo CC getlen.o
  @$(CC) $(CFLAGS-WIN) getlen.o -o getlen.o
  @echo CC clearstack.o
  @$(CC) $(CFLAGS-WIN) clearstack.c -o clearstack.o
  @echo CC initstack.o
  @$(CC) $(CFLAGS-WIN) initstack.c -o initstack.o
  
  @echo AR string.a
  @ar rcs ../string.a module.o mtscat.o
  
stack.a-unix:mtscat.c module.c
	@echo CC mtscat.o
	@$(CC) $(CFLAGS-UNIX) mtscat.c -o mtscat.o
  @echo CC module.o
  @$(CC) $(CFLAGS-UNIX) module.c -o module.o
  @echo AR string.a
  @ar rcs ../string.a module.o mtscat.o
