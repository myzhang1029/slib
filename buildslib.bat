@echo off

PATH = %path%;..\tcc

tcc -shared "%~dp0\src\lib.c" "%~dp0\src\math.c" "%~dp0\src\file.c" "%~dp0\src\error.c" "%~dp0\src\calc.c" -o "%~dp0\build\slib.dll

echo ��� �����������

pause > nul