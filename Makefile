include Make.cfg
err:;@echo -e 'Please do make PLATFORM:\n\twin:windows, MinGW\n\tunix:UNIX, GNU/Linux, BSD'

unix:slib.so
win:slib.dll

slib.so:$(FILES)
	$(CC) $(CFLAGS-UNIX) $(FILES) -o slib.so
	
slib.dll:$(FILES)
	$(CC) $(CFLAGS-WIN) $(FILES) -o slib.dll

.PHONY:clean
clean:
	$(RM) *.o *.a -r
