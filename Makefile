CC=tcc
REMOVE=del
EXTEND=dll
./build/slib.$(EXTEND):./src/slib.h ./src/math.c ./src/lib.c ./src/error.c ./src/file.c ./src/calc.c;$(CC) ./src/math.c ./src/lib.c ./src/error.c ./src/file.c ./src/calc.c -o ./build/slib.$(EXTEND)

.PHONY:rmsrc
rmsrc:;$(REMOVE) buildslib.bat buildslib.sh .gitignore .gitattributes /src/* 
