#!/usr/bin/bash

cd src

gcc -DPLAT=0 -lm -shared -O2 error.c lib.c math.c file.c calc.c -o ../slib.so
