#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([libsbl], [3.3.8], [myzhang1029@hotmail.com])
AM_INIT_AUTOMAKE
LT_INIT
AC_CONFIG_SRCDIR([src/fcopy.c])
AC_CONFIG_HEADERS([config.h])
AC_DEFINE([SLIB_LIBRARY], [1], [Define to disable linker-only features and enable builder-only features])

# Checks for programs.
AC_PROG_CXX
AC_PROG_AWK
AC_PROG_CC
AC_PROG_CPP
AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_MAKE_SET
AC_PROG_RANLIB

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([stddef.h fcntl.h limits.h memory.h stdlib.h string.h strings.h sys/file.h termios.h unistd.h wchar.h wctype.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_HEADER_STDBOOL
AC_C_INLINE
AC_TYPE_SIZE_T
AC_TYPE_SSIZE_T

# Checks for library functions.
AC_FUNC_ALLOCA
AC_FUNC_CHOWN
AC_FUNC_MALLOC
AC_FUNC_MMAP
AC_FUNC_REALLOC
AC_CHECK_FUNCS([bzero ftruncate memmove memset munmap pow strchr strerror strrchr strtol wcwidth])

AC_CONFIG_FILES([Makefile
                 src/Makefile])
AC_OUTPUT
