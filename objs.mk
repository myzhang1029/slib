include Make.cfg

#START_TAGETS

fcopy-win.o:file/fcopy.c
	$(CC) $(CFLAGS-WIN) file/fcopy.c -o fcopy.o

fcopy-unix.o:file/fcopy.c
	$(CC) $(CFLAGS-UNIX) file/fcopy.c -o fcopy.o

fsize-win.o:file/fsize.c
	$(CC) $(CFLAGS-WIN) file/fsize.c -o fsize.o

fsize-unix.o:file/fsize.c
	$(CC) $(CFLAGS-UNIX) file/fsize.c -o fsize.o

iofile-win.o:file/iofile.c
	$(CC) $(CFLAGS-WIN) file/iofile.c -o iofile.o

iofile-unix.o:file/iofile.c
	$(CC) $(CFLAGS-UNIX) file/iofile.c -o iofile.o


colorprintf-win.o:main/colorprintf.c
	$(CC) $(CFLAGS-WIN) main/colorprintf.c -o colorprintf.o

colorprintf-unix.o:main/colorprintf.c
	$(CC) $(CFLAGS-UNIX) main/colorprintf.c -o colorprintf.o

colorprintf-win.o:main/error.c
	$(CC) $(CFLAGS-WIN) main/colorprintf.c -o colorprintf.o

colorprintf-unix.o:main/colorprintf.c
	$(CC) $(CFLAGS-UNIX) main/colorprintf.c -o colorprintf.o

colorprintf-win.o:main/colorprintf.c
	$(CC) $(CFLAGS-WIN) main/colorprintf.c -o colorprintf.o

colorprintf-unix.o:main/colorprintf.c
	$(CC) $(CFLAGS-UNIX) main/colorprintf.c -o colorprintf.o
