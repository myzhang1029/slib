# slib
![License](https://www.gnu.org/graphics/lgplv3-88x31.png)

![Issue Count](https://codeclimate.com/github/myzhang1029/slib/badges/issue_count.svg)

![Code Climate](https://codeclimate.com/github/myzhang1029/slib/badges/gpa.svg)

[Binary Download Link](https://github.com/myzhang1029/slib/releases)

## Description
The slib stands for the SBL Portable Programming Interface Library.
It is a library written in C, and for C/C++.

## Building
Out-of-source build is NOT supported.
The recommended build tool is GNU make, 
Microsoft Visual Studio nmake is NOT supported.(If you have finished this, please pull request to this repository.

## Contributing
if you want to contribute to this project, please start a pull request.   

## Important
If you are building for two system, make sure you "make clean"
before running next "./configure" and "make".

## build time count(commit 21d9693) (AVG5)
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
     - configure: ./configure(unix) 
     - cc: GCC-7.1.0
     - time: 1.2366s

6.
     - System: Debian 8(GNU/Linux-4.11.4)
     - CPU: 3.8 GHz Intel Core i5
     - Memory: 1.875GB
     - configure:  ./configure --target=win --cc=i686-w64-mingw32-gcc --ar=i686-w64-mingw32-ar(win)
     - cc: GCC-7.1.0
     - time: 10.8202s

