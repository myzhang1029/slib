CC=gcc
RM=rm
CFLAGS=-lm -O2 -Wall -L. -lsbl -Islib/include
err:;@echo 'Please do make PLATFORM:\n\twin:Windows, MinGW\n\tunix:UNIX, GNU/Linux, BSD';exit 1

unix:admin
win:admin.exe

admin.exe:admin.c 
	if [ -f slib/Makefile ] ; then \
		make -f slib/Makefile win; \
		cp slib/libsbl.dll .; \
	else \
		@echo slib/Makefile not found!;\
		@echo Is this project cloned with --recursive option?;\
		@echo If not, please do 'git submodule init&&git submodule update';\
	exit 1;\
	fi
	$(CC) admin.c -o admin $(CFLAGS) -DPLAT=1

admin:admin.c
	if [ -f slib/Makefile ] ; then
		make -f slib/Makefile unix
		cp slib/libsbl.so .              
	else                                    
		@echo slib/Makefile not found!   
		@echo Is this project cloned with --recursive option?                  
		@echo If not, please do 'git submodule init&&git submodule update'     
		exit 1
	fi
	$(CC) admin.c  -o admin $(CFLAGS) -DPLAT=0
.PHONY:clean
	$(RM) *.o
