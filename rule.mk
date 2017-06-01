#Make rules for the slib
#Licence:LGPL
#See LICENCE for more details

.PHONY:err win unix $(TARGET:end=-win) $(TARGET:end=-unix)

err:;@echo Must be called by the main Makefile

win:$(TARGET:end=-win)
unix:$(TARGET:end=-unix)

$(TARGET:end=-win):$(CFILES:.c=.o)
#	$(CC) $(CFLAGS-WIN) $^

$(TARGET:end=-unix):$(CFILES:.c=.o)
#	$(CC) $(CFLAGS-UNIX) $^

%.o:%.c
	$(CC) $(CFLAGS-$(BUILD)) $^ -o $@
