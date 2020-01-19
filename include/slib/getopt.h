/*
 *  getopt.h - Header file of slib getopt
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

#ifndef SLIB_GETOPT_H
#define SLIB_GETOPT_H 1
#include "slib/general.h"

#ifdef __cplusplus
#define _BEGIN_EXTERN_C extern "C" {
#define _END_EXTERN_C }
#else
#define _BEGIN_EXTERN_C
#define _END_EXTERN_C
#endif

/* Standard GNU options*/
#define no_argument 0       /*Argument Switch Only*/
#define required_argument 1 /*Argument Required*/
#define optional_argument 2 /*Argument Optional*/

/* Shorter Options*/
#define ARG_NONE 0 /*Argument Switch Only*/
#define ARG_REQ 1  /*Argument Required*/
#define ARG_OPT 2  /*Argument Optional*/

_BEGIN_EXTERN_C

/*External variables*/
OPT int optindGS;
OPT int opterrGS;
OPT int optoptGS;
OPT char *optargGS;

struct optionGS
{
    const char *name;
    int has_arg;
    int *flag;
    int val;
};

OPT int getoptGS(int argc, char *const *argv, const char *optstring);

OPT int getopt_longGS(int argc, char *const *argv, const char *options,
                      const struct optionGS *long_options, int *opt_index);

OPT int getopt_long_onlyGS(int argc, char *const *argv, const char *options,
                           const struct optionGS *long_options, int *opt_index);

_END_EXTERN_C

#endif /* SLIB_GETOPT_H */
