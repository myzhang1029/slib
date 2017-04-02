include Make.cfg
err:;@echo -e 'Please do make PLATFORM:\n\twin:windows, MinGW\n\tunix:UNIX, GNU/Linux, BSD'

unix:slib.so
win:slib.dll

slib.so:
	$(CC) $(CFLAGS-UNIX) $(FILES) -o slib.so
	
slib.dll:
	$(CC) $(CFLAGS-WIN) $(FILES) -o slib.dll

.PHONY:clean unix win
clean:
	$(RM) *.o *.a -r
