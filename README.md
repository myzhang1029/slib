# slib
![License](https://www.gnu.org/graphics/lgplv3-88x31.png)

![Issue Count](https://codeclimate.com/github/myzhang1029/slib/badges/issue_count.svg)

![Code Climate](https://codeclimate.com/github/myzhang1029/slib/badges/gpa.svg)

# Description
The slib stands for the SBL Portable Programming Interface Library.
It is a library written in C, and for C/C++.

# Building
The recommended build tool is GNU make, 
Microsoft Visual Studio nmake is not supported.

# Contributing
if you want to contribute to this project, please start a pull request.   

# Important
If you are building for two system, make sure you "make clean"
before running next "./configure" and "make".

# build time count(commit 5052331) 
 *     Target "unix" on Debian GNU/Linux, version 8,
          CPU intel® core™ i5, gcc version 7.1.0,
          without -j: 1-2s;
 *     Target "win" on Debian GNU/Linux, version 8,
          CPU intel® core™ i5, cross compling using mingw-w64-gcc, version 4.9.1,
          without -j: 10-11s;
 *     Target "win" on msys2, System Windows 7 SP1,
          CPU intel® core™ i5, gcc version 6.3.0,
          without -j: 149s;
 *     Target "unix" on msys2,  System Windows 7 SP1,
          CPU intel® core™ i5, cross compling using Cygwin 2.7.0,
          without -j:48-49s

[Binary Download Link](https://github.com/myzhang1029/slib/releases)
