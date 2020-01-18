/*
 *  slib.h - This is the header file of the slib
 *
 *  Copyright (C) 2016-2020 Zhang Maiyun
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
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef SLIB_GENERAL_H
#define SLIB_GENERAL_H
#define SBLLIB_VERSION 4
#define SBLLIB_MINOR 5
#define SBLLIB_PATCHLEVEL 0
#endif

#ifdef HAVE_CONFIG_H
#include "config.h"
#undef malloc
#undef realloc
#endif /* HAVE_CONFIG_H */

#include <stdio.h>

#ifndef NULL
#define NULL (void *)0
#endif /* NULL */

#ifndef OPT
#ifdef _WIN32
#ifdef BUILD_DLL
#define OPT extern __declspec(dllexport) /* used in declarations */
#else
#define OPT extern __declspec(dllimport) /* used in declarations */
#endif
#else
#define OPT extern
#endif /* _WIN32 */
#endif /* OPT */

#ifndef S_REGISTER
#define S_REGISTER register
#define S_INLINE inline
#endif /* S_REGISTER */

#ifndef slib_bool
#ifdef HAVE_BOOL_H
#include <stdbool.h>
#define slib_bool _Bool
#else
#define slib_bool int
#define true 1
#define false 0
#endif /* HAVE_BOOL_H */
#endif /* slib_bool */

#ifndef _BEGIN_EXTERN_C
#ifdef __cplusplus
#define _BEGIN_EXTERN_C extern "C" {
#define _END_EXTERN_C }
#else
#define _BEGIN_EXTERN_C
#define _END_EXTERN_C
#endif /* __cplusplus */
#endif /* _BEGIN_EXTERN_C */

/* likely and unlikely branches */
#ifndef likely
#if defined(__GNUC__) &&                                                       \
    (__GNUC__ > 2 || (__GNUC__ == 2 && (__GNUC_MINOR__ > 95)))
#define likely(x) __builtin_expect(!!(x), 1)
#define unlikely(x) __builtin_expect(!!(x), 0)
#else /* !__GNUC__ or GCC < 2.95 */
#define likely(x) (x)
#define unlikely(x) (x)
#endif /* __GNUC__ */
#endif /* likely */

#ifdef DMALLOC
#include <dmalloc.h>
#endif /* DMALLOC */
