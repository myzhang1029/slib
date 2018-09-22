#!/bin/sh
# Autoconf-like interface for writing a configure script
#
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#
#  This file is part of the slib.
#  The slib  is free software; you can redistribute it and/or modify
#  it under the terms of the GNU Lesser General Public License as published by
#  the Free Software Foundation; either version 3 of the License, or
#  (at your option) any later version.
#
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU Lesser General Public License for more details.
#
#  You should have received a copy of the GNU Lesser General Public License
#  along with this program; if not, write to the Free Software
#  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
#
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

# Header file check
# $1: name
check_header(){
    printf "Checking for $1... "
    cat > conftest.c << ACEOF
#include <$1>
int main(){}
ACEOF
    if ${cc} conftest.c -o conftest >/dev/null 2>&1;
    then
        echo yes
        rm -f conftest.c conftest conftest.exe
        return 0
    else
        echo no
        rm -f conftest.c conftest conftest.exe
        return 1
    fi
}

# Program check
# $*: names
check_progs(){
    while [ $# -ne 0 ];
    do
        printf "Checking for $1... "
        if ! which $1 2> /dev/null;
        then
            echo no
            echo configure: Error: Required program $1 not found, you may need to install one.
        fi
        shift
    done
}

# AC_PROG_CC
# $1: cross compile prefix
check_cc(){
    w=0
    printf "Checking for C Compiler... "
    if $1-clang -v > /dev/null 2>&1;
    then
        cc="${cross}-clang"
    elif ${cross}-gcc -v > /dev/null 2>&1
    then
        cc="${cross}-gcc"
    elif ${cross}-tcc -v > /dev/null 2>&1;
    then
        cc="${cross}-tcc"
    elif ${cross}-cc -v > /dev/null 2>&1;
    then
        cc="${cross}-cc"
    else # No prefixed CC to use
        w=1
        if clang -v > /dev/null 2>&1;
        then
            cc="clang"
        elif gcc -v > /dev/null 2>&1;
        then
            cc="gcc"
        elif tcc -v > /dev/null 2>&1;
        then
            cc="tcc"
        elif cc -v > /dev/null 2>&1;
        then
            cc="cc"
        else
            echo no
            echo configure: Error: Can not find a C compiler!
            echo Please specify one. Read "./configure --help" for more information.
            exit 1
        fi
    fi
    echo $cc
    if [ "$1" != "" ] && [ $w -eq 1 ];
    then
        echo configure: Warning: Using unprefixed cc while cross-compiling.
    fi
}

# AC_PROG_AR
check_ar(){
    w=0
    printf "Checking for ar... "
    if which ${cross}-ar > /dev/null 2>&1; then
        ar="${cross}-ar"
    elif which ar > /dev/null 2>&1; then
        ar="ar"
        w=1
    else
        echo no
        echo configure: Error: Can not find ar!
        echo Please specify. Read "./configure --help" for more information.
        exit 1
    fi
    echo $ar
    if [ "$1" != "" ] && [ $w -eq 1 ];
    then
        echo configure: Warning: Using unprefixed ar while cross-compiling.
    fi
}

# Extract $os from host triplet
extract_os(){
    proper_triplet=`$srcdir/cmake/config.sub $1` || exit 1
    echo $proper_triplet | cut -f3- -d-
}
