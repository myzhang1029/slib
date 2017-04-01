AFILES-UNIX=main/main.unix.a math/math.unix.a file/file.unix.a \
	string/string.unix.a stack/stack.unix.a
MAKES=main/Makefile

err:;@echo -e 'Please do make PLATFORM:\n\twin:windows, MinGW\n\tunix:UNIX, GNU/Linux, BSD'

unix:slib.so
win:slib.dll

slib.so:rununix
	$(CC) $(AFILES-UNIX) -shared -c -o slib.so

rununix:


.PHONY:clean
clean:
	$(RM) *.o *.a -r
