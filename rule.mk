#Make rules for the slib
#Licence:LGPL
#See LICENCE for more details

.PHONY:err win unix
err:;@echo Must be called by the main Makefile

win:$(TARGET:end=-win.a)
unix:$(TARGET:end=-unix.a)

$(TARGET:end=-win.a):$(CFILES)
	$(CC) $(CFLAGS-WIN) $^
	ar rcs ../$(TARGET:end=.a) $(CFILES:.c=.o)

$(TARGET:end=-unix.a):$(CFILES)
	$(CC) $(CFLAGS-UNIX) $^
	ar rcs ../$(TARGET:end=.a) $(CFILES:.c=.o)
