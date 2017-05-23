#Make rules for the slib
#Licence:LGPL
#See LICENCE for more details

.PHONY:err win unix $(TARGET:end=-win) $(TARGET:end=-unix)

err:;@echo Must be called by the main Makefile

win:$(TARGET:end=-win)
unix:$(TARGET:end=-unix)

$(TARGET:end=-win):$(CFILES)
	$(CC) $(CFLAGS-WIN) $^

$(TARGET:end=-unix):$(CFILES)
	$(CC) $(CFLAGS-UNIX) $^
