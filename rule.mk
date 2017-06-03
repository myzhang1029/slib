#Make rules for the slib
#Licence:LGPL
#See LICENCE for more details

include ../config.mk

.PHONY:err win unix

err:;@echo Must be called by the main Makefile

win:$(CFILES:.c=.o)
unix:$(CFILES:.c=.o)

%.o:%.c
	$(CC) $(CFLAGS-$(BUILD)) $^ -o $@ $(LDFLAGS)
