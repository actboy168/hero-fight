/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *
 * This file is part of libxls -- A multiplatform, C library
 * for parsing Excel(TM) files.
 *
 * libxls is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * libxls is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with libxls.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Copyright 2004 Komarov Valery
 * Copyright 2006 Christophe Leitienne
 * Copyright 2008-2009 David Hoerl
 */

#include <math.h>
#include <sys/types.h>
#include <wchar.h>
#include <stdio.h>

#include <iconv.h>

#include <stdlib.h>
#include <errno.h>
#include <memory.h>
#include <string.h>

#include "xls.h"

// Convert unicode string to to_enc encoding
char* unicode_decode(const BYTE *s, int len, int *newlen, const char* to_enc)
{
  // Do iconv conversion
  const char *from_enc = "UTF-16LE";
  char* outbuf = 0;

  if(s && len && from_enc && to_enc)
  {
    size_t outlenleft = len;
    int outlen = len;
    size_t inlenleft = len;
    iconv_t ic = iconv_open(to_enc, from_enc);
    char* src_ptr = (char*) s;
    char* out_ptr = 0;

    if(ic != (iconv_t)-1)
    {
      size_t st;
      outbuf = (char*)malloc(outlen + 1);

      if(outbuf)
      {
        out_ptr = (char*)outbuf;
        while(inlenleft)
        {
          st = iconv(ic, &src_ptr, &inlenleft, &out_ptr,(size_t *) &outlenleft);
          if(st == (size_t)(-1))
          {
            if(errno == E2BIG)
            {
              int diff = out_ptr - outbuf;
              outlen += inlenleft;
              outlenleft += inlenleft;
              outbuf = (char*)realloc(outbuf, outlen + 1);
              if(!outbuf)
              {
                break;
              }
              out_ptr = outbuf + diff;
            }
            else
            {
              free(outbuf), outbuf = NULL;
              break;
            }
          }
        }
      }
      iconv_close(ic);
    }
    outlen -= outlenleft;

    if (newlen)
    {
      *newlen = outbuf ? outlen : 0;
    }
    if(outbuf)
    {
      outbuf[outlen] = 0;
    }
  }
  return outbuf;
}

// Read and decode string
char* get_string(BYTE *s, BYTE is2, BYTE is5ver, char *charset)
{
  WORD ln;
  DWORD ofs;
  DWORD sz;
  WORD rt;
  BYTE flag;
  BYTE* str;
  char* ret;
  int new_len;

  new_len = 0;
  flag = 0;
  str=s;

  ofs=0;

  if (is2) {
    // length is two bytes
    ln=*(WORD*)str;
    ofs+=2;
  } else {
    // single byte length
    ln=*(BYTE*)str;
    ofs++;
  }

  if(!is5ver) {
    // unicode strings have a format byte before the string
    flag=*(BYTE*)(str+ofs);
    ofs++;
  }
  if (flag&0x8)
  {
    rt=*(WORD*)(str+ofs);
    ofs+=2;
  }
  if (flag&0x4)
  {
    sz=*(DWORD*)(str+ofs);
    ofs+=4;
  }

  if(flag & 0x1)
  {
    WORD *pTemp = (WORD *)calloc(ln+1, sizeof(WORD));
    memcpy(pTemp,str+ofs,ln*2);
    ret = unicode_decode((BYTE *)pTemp,ln*2, &new_len,charset);
    free(pTemp);
    ofs += ln*2;
  } else {
    ret=(char *)malloc(ln+1);
    memcpy (ret,(str+ofs),ln);
    *(char*)(ret+ln)=0;
    ofs+=ln;
  }

  return ret;
}

char*  xls_getfcell(xlsWorkBook* pWB,struct st_cell_data* cell)
{
  char* out;
  WORD	len, *lPtr;
  static char ret[10240];	// don't want this on the stack, and no recursion so static OK

  //LABELSST
  switch (cell->id)
  {
  case 0x0FD:		//LABELSST
    sprintf(ret,"%s",pWB->sst.string[cell->l].str);
    break;
  case 0x201:		//BLANK
    *ret = '\0';
    break;
  case 0x0BE:		//MULBLANK
    *ret = '\0';
    break;
  case 0x0204:	//LABEL (xlslib generates these)
    lPtr = (WORD *)cell->l;
    len = *lPtr++;
    if(pWB->is5ver) {
      sprintf(ret,"%.*s", len, (char *)lPtr);
      //printf("Found BIFF5 string of len=%d \"%s\"\n", len, ret);
    } else if((*(char *)lPtr & 0x01) == 0) {
      sprintf(ret,"%.*s", len, (char *)lPtr + 1);	// 1 is the format
      //printf("Found BIFF8/ASCII string of len=%d \"%s\"\n", len, ret);
    } else {
      //printf("Found unicode str len=%d\n", len);
      int newlen;
      lPtr = (WORD *)((char *)lPtr + 1);	// skip format
      return unicode_decode((const BYTE *)lPtr, len*2, &newlen, pWB->charset);
    }
    break;
    //		if (cell->id==0x27e || cell->id==0x0BD || cell->id==0x203 || 6 (formula))
  default:
    sprintf(ret,"%i",(int)cell->d);
    break;
  }

  out=(char *)malloc(strlen(ret)+1);
  memcpy(out,ret,strlen(ret)+1);
  return out;
}

