/*
 *  sbl.c - *sbl_frame function of the slib
 *
 *  Copyright (C) 2017 Zhang Maiyun
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 *  This file is part of the slib.
 *  The slib  is free software; you can redistribute it and/or modify
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
#include "slib.h"
#include <ctype.h>

OPT unsigned long  wsbl_frame(int ch)
{
	switch ( tolower(ch) )
	{
	case ('\n'):
	{
		return SFALSE;
	}
	case ('?'):
	{
		return 0xa2108e1;
	}
	case ('.'):
	{
		return 0x422a732;
	}
	case ('a'):
	{
		return 0x0404491;
	}
	case ('b'):
	{
		return 0x1415454;
	}
	case ('c'):
	{
		return 0x1504015;
	}
	case ('d'):
	{
		return 0x1414454;
	}
	case ('e'):
	{
		return 0x1524895;
	}
	case ('f'):
	{
		return 0x1505010;
	}
	case ('g'):
	{
		return 0x1505096;
	}
	case ('h'):
	{
		return 0x1105011;
	}
	case ('i'):
	{
		return 0x0421084;
	}
	case ('j'):
	{
		return 0x040521c;
	}
	case ('k'):
	{
		return 0x1115051;
	}
	case ('l'):
	{
		return 0x1105411;
	}
	case ('m'):
	{
		return 0x0404404;
	}
	case ('n'):
	{
		return 0x1124410;
	}
	case ('o'):
	{
		return 0x1404415;
	}
	case ('p'):
	{
		return 0x1124410;
	}
	case ('q'):
	{
		return 0x1404415;
	}
	case ('r'):
	{
		return 0x1405055;
	}
	case ('s'):
	{
		return 0x1101011;
	}
	case ('t'):
	{
		return 0x1501004;
	}
	case ('u'):
	{
		return 0x1505404;
	}
	case ('v'):
	{
		return 0x1105415;
	}
	case ('w'):
	{
		return 0x150540a;
	}
	case ('x'):
	{
		return 0x1151011;
	}
	case ('y'):
	{
		return 0x1151084;
	}
	case ('z'):
	{
		return 0x1511115;
	}
	case ('0'):
	{
		return 0x4529441;
	}
	case ('1'):
	{
		return 0x4611df3;
	}
	case ('2'):
	{
		return 0x41111f5;
	}
	case ('3'):
	{
		return 0x2774707;
	}
	case ('4'):
	{
		return 0x8638849;
	}
	case ('5'):
	{
		return 0xe4384e2;
	}
	case ('6'):
	{
		return 0xe4394e4;
	}
	case ('7'):
	{
		return 0xe108406;
	}
	case ('8'):
	{
		return 0x4410878;
	}
	case ('9'):
	{
		return 0x873a080;
	}
	case ('~'):
	{
		return STRUE;
	}
	default:
	{
		return SERROR;
	}
	}
}


OPT int  rsbl_frame(int code)
{
	switch ( code )
	{
	case ('\n'):
	{
		return SFALSE;
	}
	case (0xa2108e1):       /* "?" */
	{
		return 63;
	}
	case (0x422a732):       /* "." */
	{
		return 46;
	}
	case (0x0404491):       /* A */
	{
		return 97;
	}
	case (0x1415454):       /* B */
	{
		return 98;
	}
	case (0x1504015):       /* C */
	{
		return 99;
	}
	case (0x1414454):       /* D */
	{
		return 100;
	}
	case (0x1524895):       /* E */
	{
		return 101;
	}
	case (0x1505010):       /* F */
	{
		return 102;
	}
	case (0x1505096):       /* G */
	{
		return 103;
	}
	case (0x1105011):       /* H */
	{
		return 104;
	}
	case (0x0421084):       /* I */
	{
		return 105;
	}
	case (0x040521c):       /* J */
	{
		return 106;
	}
	case (0x1115051):       /* K */
	{
		return 107;
	}
	case (0x1084215):       /* L */
	{
		return 108;
	}
	case (0x1155551):       /* M */
	{
		return 109;
	}
	case (0x1105411):       /* N */
	{
		return 110;
	}
	case (0x0404404):       /* O */
	{
		return 111;
	}
	case (0x1124410):       /* P */
	{
		return 112;
	}
	case (0x1404415):       /* Q */
	{
		return 113;
	}
	case (0x1405055):       /* R */
	{
		return 114;
	}
	case (0x1101011):       /* S */
	{
		return 115;
	}
	case (0x1501004):       /* T */
	{
		return 116;
	}
	case (0x1505404):       /* U */
	{
		return 117;
	}
	case (0x1105415):       /* V */
	{
		return 118;
	}
	case (0x150540a):       /* W */
	{
		return 119;
	}
	case (0x1151011):       /* X */
	{
		return 120;
	}
	case (0x1151084):       /* Y */
	{
		return 121;
	}
	case (0x1511115):       /* Z */
	{
		return 122;
	}
	case (0x4529441):
	{
		return 48;
	}
	case (0x4611df3):
	{
		return 49;
	}
	case (0x41111f5):
	{
		return 50;
	}
	case (0x2774707):
	{
		return 51;
	}
	case (0x8638849):
	{
		return 52;
	}
	case (0xe4384e2):
	{
		return 53;
	}
	case (0xe4394e4):
	{
		return 54;
	}
	case (0xe108406):
	{
		return 55;
	}
	case (0x4410878):
	{
		return 56;
	}
	case (0x873a080):
	{
		return 57;
	}
	case (0xed):
	{
		return STRUE;
	}
	default:
	{
		return SERROR;
	}
	}
}

