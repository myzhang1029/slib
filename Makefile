CC=gcc
CFLAGS=-O2
all:;!ERROR You must specify win|linux

linux:./build/admin
win:./build/admin.exe

./build/admin.exe:./src/slib.h ./src/admin.c ./build/slib.dll
	cd build
	$(CC) ../src/admin.c slib.dll  -o admin $(CFLAGS)\
	-DPLAT=1
./build/admin:./src/slib.h ./src/admin.c ./build/slib.so
	cd build
	$(CC) ../src/admin.c slib.so  -o admin $(CFLAGS)\
	-DPLAT=0
rmsrc:
	$(REMOVE) buildadmin.bat buildadmin.sh .gitignore .gitattributes /src/* 
