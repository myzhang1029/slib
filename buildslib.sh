cd src

gcc -lm -shared error.c lib.c math.c file.c calc.c -o ../build/slib.so


