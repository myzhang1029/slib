/*
 *  slib.h - This is the header file of the slib
 *
 *  Copyright (C) 2016 - 2018 Zhang Maiyun
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 *  This file is part of the slib.
 *  The slib is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation; either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

#if defined(_MSC_VER) && _MSC_VER >= 100
#pragma once
#endif

#ifndef SLIB_GENERAL_H
#define SLIB_GENERAL_H

#define SBLLIB_VERSION 3
#define SBLLIB_MINOR 4
#define SBLLIB_PATCHLEVEL 2

#ifdef HAVE_CONFIG_H
#include "config.h"
#undef malloc
#undef realloc
#endif

#include <errno.h>
#include <stdio.h>

#if !defined(PLAT)
#if defined(_MSC_VER) || defined(__MINGW32__) || defined(_WIN16) || defined(_WIN32) || defined(_WIN64) ||              \
    defined(__MSDOS__)
#define PLAT 1
#elif defined(__linux__) || defined(__BSD__) | defined(__APPLE__) || defined(__unix__)
#define PLAT 0
#else
#error Please define PLAT, see documentation for more details
#endif
#endif

#if PLAT
#include <windows.h>
#endif

#ifndef _CRT_SECURE_NO_WARNINGS /*for MSVC compiling envirment*/
#define _CRT_SECURE_NO_WARNINGS
#endif
#undef _CRT_NONSTDC_NO_WARNINGS

#ifndef NULL /*give default definition for NULL*/
#define NULL (void *)0
#endif

#ifndef __set_errno
#define __set_errno(x) errno = x
#endif

#define STRUE 1 /*status*/
#define SFALSE 0
#define SERROR -1

#if PLAT
#define OPT extern __declspec(dllexport) /*use in declartions*/
#else
#define OPT extern
#endif

/*BOOL*/
#if !((defined(__bool_true_false_are_defined) && __bool_true_false_are_defined == 1) || defined(HAVE_BOOL) || (defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901L)) || !defined(__GNUC__) ||           \
     __GNUC__ < 5)
typedef struct boolS { unsigned val:1; } boolS;
#define bool boolS
#define _Bool boolS
#define true (struct boolS){1}
#define false (struct boolS){0}
#define __bool_true_false_are_defined 1
#endif

#define S_INLINE inline

/*debugger*/
#define D_STABLE
#define D_UNSTABLE
#define D_TESTING

#ifdef __cplusplus
#define _BEGIN_EXTERN_C extern "C" {
#define _END_EXTERN_C }
#else
#define _BEGIN_EXTERN_C
#define _END_EXTERN_C
#endif
#endif
