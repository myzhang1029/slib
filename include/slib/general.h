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

#define SBLLIB_VERSION 4
#define SBLLIB_MINOR 1
#define SBLLIB_PATCHLEVEL 0

#ifdef HAVE_CONFIG_H
#include "config.h"
#undef malloc
#undef realloc
#endif

#include <stdio.h>

#if !defined(PLAT)
#if defined(_MSC_VER) || defined(__MINGW32__) || defined(_WIN16) ||            \
    defined(_WIN32) || defined(_WIN64) || defined(__MSDOS__)
#define PLAT 1
#ifndef _CRT_SECURE_NO_WARNINGS /* for MSVC */
#define _CRT_SECURE_NO_WARNINGS
#endif
#undef _CRT_NONSTDC_NO_WARNINGS
#elif defined(__linux__) || defined(__BSD__) | defined(__APPLE__) ||           \
    defined(__unix__)
#define PLAT 0
#else
#error Please define PLAT, see documentation for more details
#endif
#endif

#if PLAT
#include <windows.h>
#endif

#ifndef NULL /* default definition of NULL */
#define NULL (void *)0
#endif

#if PLAT
#define OPT extern __declspec(dllexport) /* used in declarations */
#else
#define OPT extern
#endif

/* register storage specifier */
#ifndef S_REGISTER
#define S_REGISTER register
#endif

#define S_INLINE inline

#ifdef __cplusplus
#define _BEGIN_EXTERN_C extern "C" {
#define _END_EXTERN_C }
#else
#define _BEGIN_EXTERN_C
#define _END_EXTERN_C
#endif
#endif
