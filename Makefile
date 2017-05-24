CC=gcc
RM=rm
CFLAGS=-lm -O2 -Wall -L. -lsbl -Islib/include

.PHONY:err unix win clean
err:
	@echo 'Please do make PLATFORM:'
	@echo '	win:Windows, MinGW'
	@echo '	unix:UNIX, GNU/Linux, BSD'
	@exit 1

unix:admin
win:admin.exe

admin.exe:admin.c 
	@if ! [ -f slib/Makefile ] ; then\
		echo slib/Makefile not found!;\
		echo Is this project cloned with --recursive option?;\
		echo If not, please do 'git submodule init&&git submodule update';\
	exit 1;\
	fi
	make -C slib win 
	cp slib/libsbl.dll .
	$(CC) admin.c -o admin $(CFLAGS) -DPLAT=1

admin:admin.c
	@if ! [ -f slib/Makefile ] ; then\
		echo slib/Makefile not found!;\
		echo Is this project cloned with --recursive option?;\
		echo If not, please do 'git submodule init&&git submodule update';\
	exit 1;\
	fi
	make -C slib unix
	cp slib/libsbl.so .
	$(CC) admin.c -o admin $(CFLAGS) -DPLAT=0
clean:
	$(RM) *.o
