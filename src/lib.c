/*
 *  lib.c - Main library of the slib
 *
 *  Copyright (C) 2017 Zhang Maiyun
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 *  This file is part of slib.
 *  slib  is free software; you can redistribute it and/or modify
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


OPT long  randomnum( cui seed,cul maximum,cul minimum )
{
	srand(seed);
	return minimum + rand() % (maximum-minimum);
}


OPT int  mysh( ccp path )
{
	char command[20];
	fflush( stdin );
	#if PLAT
	printf( "%s(Enter 'q'  to quit)>", path );
	#else
	printf( "slibsh@localhost %s(Enter 'q' to quit)$",path );
	fgets( command, 19, stdin );
	if ( strcmp(command,"q\n")==0 )
	{
		return STRUE;
	}
	else
	{
		system( command );
		return SFALSE;
	}
}


OPT char *  mtscat(cui amount,...)
{
	vlist strs;
	char *str;
	int count;
	vstart (strs,amount);
	str=varg(strs,char*);
	for(count=0; count<=amount-1; ++count)
	{
		strcat(str,varg(strs,char*));
	}
	vend(strs);
	return str;
}


OPT int getmname(ccp fullpath,char *mname)
{
	int count,count2=0,fpathl=strlen(fullpath);
	for(count=fpathl;count>=0;--count)
	{
		if(fullpath[count]==pathsep)
		{
			for(++count;count<=fpathl;++count,++count2)
			{
				mname[count2]=fullpath[count];
			}
			return STRUE;
		}
	}
	return SFALSE;
}


OPT int getmpath(ccp fullpath,char *mpath)
{
	int count,count2,fpathl=strlen(fullpath);
	for(count=fpathl;count>=0;--count)
	{
		if(fullpath[count]==pathsep)
		{
			for(count2=0;count2<count;++count2)
			{
				mpath[count2]=fullpath[count2];
			}
			mpath[count2+1]='\0';
			mpath[count2]=pathsep;
			return STRUE;
		}
	}
	return SFALSE;
}


OPT uslong  wsbl_frame(int ch)
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


char* itoaS(int value, char* string, int radix)
{
  char tmp[33];
  char* tp = tmp;
  int i;
  unsigned v;
  int sign;
  char* sp;

  if (radix > 36 || radix <= 1)
  {
    __set_errno(EDOM);
    return 0;
  }

  sign = (radix == 10 && value < 0);
  if (sign)
    v = -value;
  else
    v = (unsigned)value;
  while (v || tp == tmp)
  {
    i = v % radix;
    v = v / radix;
    if (i < 10)
      *tp++ = i+'0';
    else
      *tp++ = i + 'a' - 10;
  }

  if (string == 0)
    string = (char*)malloc((tp-tmp)+sign+1);
  sp = string;

  if (sign)
    *sp++ = '-';
  while (tp > tmp)
    *sp++ = *--tp;
  *sp = 0;
  return string;
}


char* ltoaS(long value, char* string, int radix)
{
  char tmp[33];
  char* tp = tmp;
  long i;
  unsigned long v;
  int sign;
  char* sp;

  if (radix > 36 || radix <= 1)
  {
     __set_errno(EDOM);
    return 0;
  }

  sign = (radix == 10 && value < 0);
  if (sign)
    v = -value;
  else
    v = (unsigned long)value;
  while (v || tp == tmp)
  {
    i = v % radix;
    v = v / radix;
    if (i < 10)
      *tp++ = i+'0';
    else
      *tp++ = i + 'a' - 10;
  }

  if (string == 0)
    string = (char*)malloc((tp-tmp)+sign+1);
  sp = string;

  if (sign)
    *sp++ = '-';
  while (tp > tmp)
    *sp++ = *--tp;
  *sp = 0;
  return string;
}


char* ultoaS(unsigned long value, char* string, int radix)
{
  char tmp[33];
  char* tp = tmp;
  long i;
  unsigned long v = value;
  char* sp;

  if (radix > 36 || radix <= 1)
  {
    __set_errno(EDOM);
    return 0;
  }

  while (v || tp == tmp)
  {
    i = v % radix;
    v = v / radix;
    if (i < 10)
      *tp++ = i+'0';
    else
      *tp++ = i + 'a' - 10;
  }

  if (string == 0)
    string = (char*)malloc((tp-tmp)+1);
  sp = string;

  while (tp > tmp)
    *sp++ = *--tp;
  *sp = 0;
  return string;
}


#if ! PLAT
OPT int getch(void) 
{
        int c=0;
        struct termios org_opts, new_opts;
        int res=0;

        res=tcgetattr(STDIN_FILENO, &org_opts);
        assert(res==0);
    
        memcpy(&new_opts, &org_opts, sizeof(new_opts));
        new_opts.c_lflag &= ~(ICANON | ECHO | ECHOE | ECHOK | ECHONL | ECHOPRT | ECHOKE | ICRNL);
        tcsetattr(STDIN_FILENO, TCSANOW, &new_opts);
        c=getchar();

        res=tcsetattr(STDIN_FILENO, TCSANOW, &org_opts);assert(res==0);
        return c;
}
#endif
