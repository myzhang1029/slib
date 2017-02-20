@echo off

PATH = %path%;..\tcc;

if not exist ..\slib\build\slib.dll "..\slib\buildslib.bat"

if exist "%~dp0\build\slib.dll" del "%~dp0\build\slib.dll"
if exist "%~dp0\src\slib.def" del "%~dp0\src\slib.def"

copy "..\slib\build\slib.dll" "%~dp0\build\slib.dll" > nul
copy "..\slib\build\slib.def" "%~dp0\src\slib.def" > nul
copy "..\slib\src\slib.h" "%~dp0\src\slib.h" > nul

tcc "%~dp0\src\admin.c" "%~dp0\src\slib.def" -o "%~dp0\build\admin.exe"


pause