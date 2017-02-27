CC=tcc
REMOVE=del
EXTEND=dll

./build/slib.$(EXTEND):./src/slib.h ./src/admin.c ./build/slib.$(EXTEND)
	$(CC) ./src/admin.c ./build/slib.&(EXTEND)  -o ./build/admin
rmsrc:
	$(REMOVE) buildadmin.bat buildadmin.sh .gitignore .gitattributes /src/* 
