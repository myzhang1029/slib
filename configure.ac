#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([libsbl], [m4_esyscmd([/bin/sh cmake/version.sh])], [myzhang1029@hotmail.com])
AC_SUBST([version_info], [m4_esyscmd([/bin/sh -c "sh cmake/version.sh|tr . :"])])
AC_CONFIG_SRCDIR([include/slib.h])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_MACRO_DIRS([m4])
AM_INIT_AUTOMAKE([subdir-objects])
LT_INIT([win32-dll])
AC_DEFINE_UNQUOTED([sbl_LIBRARY], [1], [Internal build marker])

# Checks for programs.
AC_PROG_CC
AC_PROG_INSTALL

# Checks for libraries.
AC_SEARCH_LIBS([sqrt], [m])

# Checks for header files.
AC_FUNC_ALLOCA
AC_CHECK_HEADERS([fcntl.h memory.h stdint.h stdlib.h string.h termios.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_SIZE_T

# Checks for library functions.
AC_FUNC_MALLOC
AC_FUNC_REALLOC
AC_FUNC_STRTOD
AC_CHECK_FUNCS([isascii memset pow sqrt strchr strerror strrchr])

AC_OUTPUT([Makefile])
