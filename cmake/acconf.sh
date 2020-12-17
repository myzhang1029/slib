#!/bin/sh
#
#  Autoconf-like interface for writing a configure script
#
#  Copyright (C) 2017-2020 Zhang Maiyun
#
#  This file is part of the slib.
#  The slib is free software; you can redistribute it and/or modify
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
#  along with this program.  If not, see <https://www.gnu.org/licenses/>.
#

# This script is intended to be called by source or .(dot)
# Prior to calling this script, define:
# $CONFIGROOT to the folder containing config.guess/config.sub
# Optionally define:
# $ERROR_REDIR to where stderr should go

if [ "$CONFIGROOT" = "" ]
then
    echo "Undefined variable in acconf.sh" >&2
    exit 1
fi

if [ "$ERROR_REDIR" = "" ]
then
    ERROR_REDIR="/dev/null"
fi

# Get proper triplet
# $1: optional cross compile prefix
get_proper_triplet() {
    if [ "$1" = "" ]
    then
        "$CONFIGROOT/config.guess" || exit 1
    else
        "$CONFIGROOT/config.sub" "$1" || exit 1
    fi
}

# Header file check
# $1: name
check_header() {
    printf "Checking for %s... " "$1"
    cat >conftest.c <<ACEOF
#include <$1>
int main()
{return 0;}
ACEOF
    if "$cc" conftest.c -o conftest >/dev/null 2>"$ERROR_REDIR"
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

# Type size check
# $1: name
check_type() {
    printf "Checking for size of %s... " "$1"
    cat >conftest.c <<ACEOF
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
int main()
{printf("%zu\n", sizeof($1));return 0;}
ACEOF
    if "$cc" conftest.c -o conftest >/dev/null 2>"$ERROR_REDIR"
    then
        size="$(./conftest 2>/dev/null || ./conftest.exe 2>/dev/null)"
        if [ "$size" = "" ]
        then
            echo "cannot determine"
            size=0
        else
            echo "$size"
        fi
        rm -f conftest.c conftest conftest.exe
        return "$size"
    else
        echo no
        rm -f conftest.c conftest conftest.exe
        return 0
    fi
}

# Program check
# $*: names
check_progs() {
    while [ "$#" -ne 0 ]
    do
        printf "Checking for %s... " "$1"
        if ! type "$1" 2>/dev/null
        then
            echo no
            echo "configure: Error: Required program $1 not found, you may need to install one."
            exit 1
        fi
        shift
    done
}

# AC_PROG_CC
# $1: optional cross compile prefix
check_cc() {
    w=0
    hosttrip="$1"
    printf "Checking for C Compiler... "
    if "$hosttrip-gcc" -v >/dev/null 2>"$ERROR_REDIR"
    then
        cc="$hosttrip-gcc"
    elif "$hosttrip-clang" -v >/dev/null 2>"$ERROR_REDIR"
    then
        cc="$hosttrip-clang"
    elif "$hosttrip-tcc" -v >/dev/null 2>"$ERROR_REDIR"
    then
        cc="$hosttrip-tcc"
    elif "$hosttrip-cc" -v >/dev/null 2>"$ERROR_REDIR"
    then
        cc="$hosttrip-cc"
    else
        if ! [ "$hosttrip" = "" ]
        then
            hosttrip="$("$CONFIGROOT/config.sub" "$1")"
            if "${hosttrip}-gcc" -v >/dev/null 2>"$ERROR_REDIR"
            then
                cc="${hosttrip}-gcc"
                return
            elif "${hosttrip}-clang" -v >/dev/null 2>"$ERROR_REDIR"
            then
                cc="${hosttrip}-clang"
                return
            elif "${hosttrip}-tcc" -v >/dev/null 2>"$ERROR_REDIR"
            then
                cc="${hosttrip}-tcc"
                return
            elif "${hosttrip}-cc" -v >/dev/null 2>"$ERROR_REDIR"
            then
                cc="${hosttrip}-cc"
                return
            else
                :
            fi
        fi
        # No prefixed CC to use
        w=1
        if gcc -v >/dev/null 2>"$ERROR_REDIR"
        then
            cc="gcc"
        elif clang -v >/dev/null 2>"$ERROR_REDIR"
        then
            cc="clang"
        elif tcc -v >/dev/null 2>"$ERROR_REDIR"
        then
            cc="tcc"
        elif cc -v >/dev/null 2>"$ERROR_REDIR"
        then
            cc="cc"
        else
            echo no
            echo configure: Error: Can not find a C compiler!
            echo "Please specify one. Read \`./configure --help' for more information."
            exit 1
        fi
    fi
    echo "$cc"
    if [ "$1" != "" ] && [ "$w" -eq 1 ]
    then
        echo configure: Warning: Using unprefixed cc while cross-compiling.
    fi
}

# AC_PROG_AR
# $1: optional cross compile prefix
check_ar() {
    w=0
    hosttrip="$(get_proper_triplet "$1")"
    printf "Checking for ar... "
    if which "$hosttrip-ar" >/dev/null 2>"$ERROR_REDIR"
    then
        ar="$hosttrip-ar"
    elif which ar >/dev/null 2>"$ERROR_REDIR"
    then
        ar="ar"
        w=1
    else
        echo no
        echo configure: Error: Can not find ar!
        echo "Please specify one. Read \`./configure --help' for more information."
        exit 1
    fi
    echo $ar
    if [ "$1" != "" ] && [ $w -eq 1 ]
    then
        echo configure: Warning: Using unprefixed ar while cross-compiling.
    fi
}

# Check whether the compiler works
# Must call check_cc first
check_cc_works() {
    possible_files="a.out conftest.exe conftest a.exe a_out.exe b.out conftest.*"
    cat >conftest.c <<ACEOF
#include <stdio.h>
int main()
{return 0;}
ACEOF
    printf 'Checking whether the C Compiler works... '
    if ${cc} conftest.c >/dev/null 2>"$ERROR_REDIR"
    then
        echo yes
    else
        echo no
        echo The C Compiler cannot compile a simple source file
        echo The failed source file was:
        cat conftest.c
        rm -f "$possible_files" conftest.c
        exit 1
    fi
    printf 'Checking for extension of executables... '
    for file in $possible_files
    do
        ac_ext=c
        test -f "$file" || continue
        case $file in
        *.$ac_ext | *.xcoff | *.tds | *.d | *.pdb | *.xSYM | *.bb | *.bbg | *.map | *.inf | *.dSYM | *.o | *.obj)
            # Not the right one
            ;;
        [ab].out)
            # We found the default executable.
            break
            ;;
        *.*)
            if [ "$exesuf" = "" ]
            then
                exesuf=$(expr "$file" : '[^.]*\(\..*\)')
            fi
            break
            ;;
        *)
            break
            ;;
        esac
    done
    echo "$exesuf"
    rm -f "$possible_files" conftest.c
}

# Check whether the copiler produces shared objects
# and receive correct $sosuf $soflags $append_version
# Must call check_cc first
# $1: optional cross compile prefix
# $2: library version
check_shared_works() {
    printf 'Checking whether the C Compiler accepts -shared... '
    cat >conftest.c <<ACEOF
#include <stdio.h>
int main(){;}
ACEOF
    if ${cc} -shared -o conftest.so conftest.c >/dev/null
    then
        echo yes
    else
        echo no
        echo The C Compiler cannot produce shared objects
        echo The failed source file was:
        echo "#include <stdio.h>"
        echo "int main(){;}"
        rm -f "$possible_files"
        exit 1
    fi
    rm -f conftest.so conftest.c
    # For sosuf
    printf "Checking for extension of shared objects... "
    case "$(get_proper_triplet "$1")" in
    *linux* | *gnu* | *bsd* | *sunos* | *minix* | *solaris*)
        export sosuf=".so"
        export soflags="-shared -O2 -lm"
        export cflags="${cflags}"
        export append_version=true
        ;;
    *darwin* | *step*)
        export sosuf=".dylib"
        export soflags="-dynamiclib -current_version $2"
        export append_version=true
        ;;
    *windows* | *mingw* | *msys* | *cygwin*)
        export sosuf=".dll"
        export soflags="-shared"
        export append_version=""
        ;;
    *)
        echo unknown
        echo "configure: Error: unable to determine suffix for shared objects(aka dylib/so/dll), please add option --sosuffix"
        exit 1
        ;;
    esac
    echo "$sosuf"
    return 0
}

# Extract $os from host triplet
# $1: optional cross compile prefix
extract_os() {
    get_proper_triplet "$1" | cut -f3- -d-
}
