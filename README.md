# slib
![License](https://www.gnu.org/graphics/lgplv3-88x31.png)

<a href="https://codeclimate.com/github/myzhang1029/slib"><img src="https://codeclimate.com/github/myzhang1029/slib/badges/issue_count.svg" /></a>

<a href="https://codeclimate.com/github/myzhang1029/slib"><img src="https://codeclimate.com/github/myzhang1029/slib/badges/gpa.svg" /></a>

[Binary Download Link](https://github.com/myzhang1029/slib/releases)

## Description
This project is seperated from myzhang1029/admin, 
which has brought me to the world of C, in the computer room 
of Primary School Attached to Yunnnan Normal University(in Yunnan, China),
in 2015 when I was 11.
So therefore don't laugh at these projects, because they're from a beginner.

The slib stands for Slib: the portable programming interface LIBrary.
It is a library written in C, and for any usage.

## Building

#### If you are using MinGW and you don't have a MSYS, try
 ```cmd
 > make -f Makefile.mingw PREFIX=prefix
 > make install 
 ```
Otherwise you can use configure or CMake
Just like usual GNU softwares do.

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
You could see [admin.c](https://github.com/myzhang1029/admin/blob/master/admin.c) for a rough idea.

## Contributing
if you want to contribute to this project, please start a pull request.   
