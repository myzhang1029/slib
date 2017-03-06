@echo off


gcc -DPLAT=1 -O2 -shared .\src\lib.c .\src\math.c .\src\file.c .\src\error.c .\src\calc.c -o .\build\slib.dll


pause
