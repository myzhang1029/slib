#Sub Makefile for math mod

include ../config.mk

.PHONY:win unix math.a-unix math.a-win
win:math.a-win
unix:math.a-unix

math.a-win:average.c c calc.c eular.c gcf.c ispn.c isrp.c lcm.c prtpn.c
	@echo CC average.o
	@$(CC) $(CFLAGS-WIN) average.c -o average.o
	@echo CC calc.o
	@$(CC) $(CFLAGS-WIN) calc.c -o calc.o
	@echo CC eular.o
	@$(CC) $(CFLAGS-WIN) eular.o -o eular.o
	@echo CC gcf.o
	@$(CC) $(CFLAGS-WIN) gcf.c -o gcf.o
	@echo CC ispn.o
	@$(CC) $(CFLAGS-WIN) ispn.c -o ispn.o
	@echo CC isrp.o
	@$(CC) $(CFLAGS-WIN) isrp.c -o isrp.o
	@echo CC lcm.o
	@$(CC) $(CFLAGS-WIN) lcm.c -o lcm.o
	@echo CC prtpn.o
	@$(CC) $(CFLAGS-WIN) prtpn.c -o prtpn.o
	@echo AR math.a
	@ar rcs ../math.a average.o calc.o eular.o gcf.o ispn.o isrp.o lcm.o prtpn.o
  
math.a-unix:average.c c calc.c eular.c gcf.c ispn.c isrp.c lcm.c prtpn.c
	@echo CC average.o
	@$(CC) $(CFLAGS-UNIX) average.c -o average.o
	@echo CC calc.o
	@$(CC) $(CFLAGS-UNIX) calc.c -o calc.o
	@echo CC eular.o
	@$(CC) $(CFLAGS-UNIX) eular.o -o eular.o
	@echo CC gcf.o
	@$(CC) $(CFLAGS-UNIX) gcf.c -o gcf.o
	@echo CC ispn.o
	@$(CC) $(CFLAGS-UNIX) ispn.c -o ispn.o
	@echo CC isrp.o
	@$(CC) $(CFLAGS-UNIX) isrp.c -o isrp.o
	@echo CC lcm.o
	@$(CC) $(CFLAGS-UNIX) lcm.c -o lcm.o
	@echo CC prtpn.o
	@$(CC) $(CFLAGS-UNIX) prtpn.c -o prtpn.o
	@echo AR math.a
	@ar rcs ../math.a average.o calc.o eular.o gcf.o ispn.o isrp.o lcm.o prtpn.o
