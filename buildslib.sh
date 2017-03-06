#!/usr/bin/bash

cd src

gcc -DPLAT=0 -lm -shared error.c lib.c math.c file.c calc.c -o ../build/slib.so
