# slib
[![Build Status](https://travis-ci.com/myzhang1029/slib.svg?branch=master)](https://travis-ci.com/myzhang1029/slib)

[![Build Status](https://ci.appveyor.com/api/projects/status/svfjuyxpq9ftjqrk?svg=true)](https://ci.appveyor.com/project/myzhang1029/slib-cwdar)

![License](https://img.shields.io/badge/license-LGPL-blue.svg)

## Description
This project is separated from myzhang1029/admin,
which brought me to the world of C, in the computer room
of Primary School Attached to Yunnan Normal University(in Yunnan, China),
(hiding from the teacher), in 2015 when I was 11.  
I just wanted to use these start-up projects to check out some C skills, tools and community integrations.  
So therefore don't laugh at these projects, because they're from a beginner.

The slib is not an acronym, it's just a name.
It is a portable programming interface library,
a library written in C, and for any usage.

## Building
If you are using MinGW and you don't have a MSYS, try:
 ```cmd
 > make -f Makefile.mingw PREFIX=prefix
 > make install 
 ```
Otherwise you can use configure or CMake
Just like usual GNU software do.

This autoconf-like script should run on all POSIX systems, supporting GNU make and BSD make as far as I know:   
```shell
$ ./configure
$ make
$ make install
```
CMake(You could run make/ninja distclean!):  
```shell
$ mkdir build (optional)
$ cd build
$ cmake .. -G Ninja
$ ninja install
```
## Usage
You could see [sbltool.c](https://github.com/myzhang1029/slib/blob/master/sbltool.c) for a rough idea.

## Contributing
if you want to contribute to this project, please start a pull request.   
