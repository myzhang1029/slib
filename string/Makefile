#Sub Makefile for string mod

include ../config.mk

.PHONY:win unix string.a-unix string.a-win
win:string.a-win
unix:string.a-unix

string.a-win:mtscat.c module.c
	@echo CC mtscat.o
	@$(CC) $(CFLAGS-WIN) mtscat.c -o mtscat.o
	@echo CC module.o
	@$(CC) $(CFLAGS-WIN) module.o -o module.o
	@echo AR string.a
	@ar rcs ../string.a module.o mtscat.o
  
string.a-unix:mtscat.c module.c
	@echo CC mtscat.o
	@$(CC) $(CFLAGS-UNIX) mtscat.c -o mtscat.o
	@echo CC module.o
	@$(CC) $(CFLAGS-UNIX) module.o -o module.o
	@echo AR string.a
	@ar rcs ../string.a module.o mtscat.o
