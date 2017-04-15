CC=gcc
CFLAGS=-lm -O2 -Wall
all:;@echo -e 'Please do make PLATFORM:\n\twin:Windows, MinGW\n\tunix:UNIX, GNU/Linux, BSD'

unix:admin
win:admin.exe

admin.exe:./src/slib.h ./src/admin.c libsbl.dll
	@if [ -f slib/Makefile ] ; then
		make -f slib/Makefile
		cp slib/libsbl.so .
	@else
		@echo slib/Makefile not found!
		@echo Is this project cloned with --recursive option?
		@echo If not, please do 'git submodule init&&git submodule update'
	@fi
	$(CC) src/admin.c libsbl.dll  -o admin $(CFLAGS) -DPLAT=1

admin:./src/slib.h ./src/admin.c libsbl.so
	@if [ -f slib/Makefile ] ; then          
                make -f slib/Makefile            
                cp slib/libsbl.so .              
        @else                                    
                @echo slib/Makefile not found!   
                @echo Is this project cloned with
 --recursive option?                             
                @echo If not, please do 'git subm
odule init&&git submodule update'                
        @fi
	$(CC) src/admin.c  -o admin $(CFLAGS) -DPLAT=0
.PHONY:clean
	$(REMOVE) *.o
