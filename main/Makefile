#Sub Makefile for main mod

include ../config.mk

.PHONY:win unix main.a-unix main.a-win
win:main.a-win
unix:main.a-unix

main.a-win:colorprintf.c error.c getch.c itoa.c mret.c mysh.c randomnum.c sbl.c
	@echo CC colorprintf.o
	@$(CC) $(CFLAGS-WIN) colorprintf.c -o colorprintf.o
	@echo CC error.o
	@$(CC) $(CFLAGS-WIN) error.c -o error.o
	@echo CC getch.o
	@$(CC) $(CFLAGS-WIN) getch.c -o getch.o
	@echo CC itoa.o
	@$(CC) $(CFLAGS-WIN) itoa.c -o itoa.o
	@echo CC mret.o
	@$(CC) $(CFLAGS-WIN) mret.c -o mret.o
	@echo CC mysh.o
	@$(CC) $(CFLAGS-WIN) mysh.c -o mysh.o
	@echo CC randomnum.o
	@$(CC) $(CFLAGS-WIN) randomnum.c -o randomnum.o
	@echo CC sbl.o
	@$(CC) $(CFLAGS-WIN) sbl.c -o sbl.o
	@echo AR math.a
	@ar rcs ../math.a colorprintf.o error.o getch.o mret.o mysh.o randomnum.o sbl.o
  
main.a-unix:colorprintf.c error.c getch.c itoa.c mret.c mysh.c randomnum.c sbl.c
	@echo CC colorprintf.o
	@$(CC) $(CFLAGS-UNIX) colorprintf.c -o colorprintf.o
	@echo CC error.o
	@$(CC) $(CFLAGS-UNIX) error.c -o error.o
	@echo CC getch.o
	@$(CC) $(CFLAGS-UNIX) getch.o -o getch.o
	@echo CC .o
	@$(CC) $(CFLAGS-UNIX) itoa.c -o itoa.o
	@echo CC mret.o
	@$(CC) $(CFLAGS-UNIX) mret.c -o mret.o
	@echo CC mysh.o
	@$(CC) $(CFLAGS-UNIX) mysh.c -o mysh.o
	@echo CC randomnum.o
	@$(CC) $(CFLAGS-UNIX) randomnum.c -o randomnum.o
	@echo CC sbl.o
	@$(CC) $(CFLAGS-UNIX) sbl.c -o sbl.o
	@echo AR math.a
	@ar rcs ../math.a colorprintf.o error.o getch.o mret.o mysh.o randomnum.o sbl.o
