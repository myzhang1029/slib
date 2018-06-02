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
Otherwise you can use GNU make or xmake(github: tboox/xmake)
Just like usual GNU softwares do.

GNU make:   
```shell
$ ./configure
$ make
# make install
```
xmake:
```shell
$ xmake 
# xmake install
$ xmake -f -k shared
$ xmake
# xmake install
# cp include/slib.h (prefix)/include/slib.h
```
Microsoft Visual Studio nmake is NOT yet supported.(If you have finished this, please pull request to this repository.

## Contributing
if you want to contribute to this project, please start a pull request.   

## build time count(commit 21d9693) (AVG5)
### These results are deprecated
 1.
     - System: macOS 10.12(Darwin-16.6.0)
     - CPU: 3.8 GHz Intel Core i5
     - Memory: 8GB
     - configure: ./configure(unix)
     - cc: Apple LLVM version 8.1.0 (clang-802.0.42)
     - time: 0.9174s

 2.
     - System: macOS 10.12(Darwin-16.6.0)
     - CPU: 3.8 GHz Intel Core i5
     - Memory: 8GB
     - configure: ./configure --target=win --cc=i686-w64-mingw32-gcc --ar=i686-w64-mingw32-ar(win)
     - cc: GCC-7.1.0
     - time: 9.5148s

 3.
     - System: Debian 8(GNU/Linux-4.11.4)
     - CPU: 3.8 GHz Intel Core i5
     - Memory: 1.875GB
     - configure: ./configure(unix) 
     - cc: clang version 3.5.0-10
     - time: 1.1352s

 4.
     - System: Debian 8(GNU/Linux-4.11.4)
     - CPU: 3.8 GHz Intel Core i5
     - Memory: 1.875GB
     - configure: ./configure(unix) 
     - cc: GCC-7.1.0
     - time: 1.2366s
 
 5.
     - System: Debian 8(GNU/Linux-4.11.4)
     - CPU: 3.8 GHz Intel Core i5
     - Memory: 1.875GB
     - configure:  ./configure --target=win --cc=i686-w64-mingw32-gcc --ar=i686-w64-mingw32-ar(win)
     - cc: GCC-7.1.0
     - time: 10.8202s

