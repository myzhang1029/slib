CFILES=average.c calc.c clearstack.c colorprintf.c destorystack.c error.c eular.c fcopy.c fsize.c gcf.c getch.c getlen.c getopt.c initstack.c iofile.c ispn.c isrp.c itoa.c lcm.c mret.c mtscat.c mysh.c pop.c prtpn.c push.c randomnum.c sbl.c sleepS.c splitpathS.c

#Make rules for the slib
#Licence:LGPL
#See LICENCE for more details

include ../config.mk

.PHONY:err win unix

err:;@echo Must be called by the main Makefile

win:$(CFILES:.c=.o)
unix:$(CFILES:.c=.o)

%.o:%.c
	$(CC) $(CFLAGS-$(BUILD)) $^ -o $@
