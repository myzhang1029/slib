#Make rules for the slib
#Licence:LGPL
#See LICENCE for more details

.PHONY:err win unix
err:;@echo Must be called by the main Makefile

win:$(TARGET:end=-win.a)
unix:$(TARGET:end=-unix.a)

$(TARGET:end=-win.a):$(CFILES)
	@echo $(CFILES:.c=)|xargs -i {} echo CC {}.o;$(CC) $(CFLAGS) {}.c
	@echo AR $(TARGET:end=.a);ar rcs $(TARGET:end=.a) $(CFILES:.c=.o)
