﻿/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
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

#include <memory.h>
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define NDEBUG	// turn asserts off
#include <assert.h>

#include "ole.h"
#include "xlstool.h"

const DWORD MSATSECT =		0xFFFFFFFC;	// -4
const DWORD FATSECT =		0xFFFFFFFD;	// -3
const DWORD ENDOFCHAIN =	0xFFFFFFFE;	// -2
const DWORD FREESECT =		0xFFFFFFFF;	// -1

static int sector_pos(OLE2* ole2, int sid);
static int sector_read(OLE2* ole2, BYTE *buffer, int sid);
static int read_MSAT(OLE2* ole2, OLE2Header *oleh);

// Read next sector of stream
void ole2_bufread(OLE2Stream* olest)
{
  BYTE *ptr;

  assert(olest);
  assert(olest->ole);

  if (olest->fatpos!=ENDOFCHAIN)
  {
    if(olest->sfat) {
      assert(olest->ole->SSAT);
      assert(olest->buf);
      assert(olest->ole->SSecID);

      ptr = olest->ole->SSAT + olest->fatpos*olest->ole->lssector;
      memcpy(olest->buf, ptr, olest->bufsize);

      olest->fatpos=olest->ole->SSecID[olest->fatpos];
      olest->pos=0;
      olest->cfat++;
    } else {

      assert(olest->fatpos >= 0);

      //printf("fatpos: %d max=%u\n",olest->fatpos, (olest->ole->cfat*olest->ole->lsector)/4);
      if(olest->fatpos > (olest->ole->cfat*olest->ole->lsector)/4) exit(-1);
      assert((int)olest->fatpos >= 0);
      sector_read(olest->ole, olest->buf, olest->fatpos);
      //printf("Fat val: %d[0x%X]\n",olest->fatpos,olest->ole->SecID[olest->fatpos], olest->ole->SecID[olest->fatpos]);
      olest->fatpos=olest->ole->SecID[olest->fatpos];
      olest->pos=0;
      olest->cfat++;
    }
  }
  // else printf("ENDOFCHAIN!!!\n");
}

// Read part of stream
int ole2_read(void* buf,long size,long count,OLE2Stream* olest)
{
  long didReadCount=0;
  long totalReadCount;;	// was DWORD
  unsigned long needToReadCount;

  totalReadCount=size*count;

  // olest->size inited to -1
  //printf("===== ole2_read(%ld bytes)\n", totalReadCount);

  if (olest->size>=0 && !olest->sfat)	// directory is -1
  {
    int rem;
    rem = olest->size - (olest->cfat*olest->ole->lsector+olest->pos);
    totalReadCount = rem<totalReadCount?rem:totalReadCount;
    if (rem<=0) olest->eof=1;

    // printf("  rem=%ld olest->size=%d - subfunc=%d\n", rem, olest->size, (olest->cfat*olest->ole->lsector+olest->pos) );
    //printf("  totalReadCount=%d (rem=%d size*count=%ld)\n", totalReadCount, rem, size*count);
  }

  while ((!olest->eof) && (didReadCount!=totalReadCount))
  {
    unsigned long remainingBytes;

    needToReadCount	= totalReadCount - didReadCount;
    remainingBytes	= olest->bufsize - olest->pos;
    //printf("  test: (totalReadCount-didReadCount)=%d (olest->bufsize-olest->pos)=%d\n", (totalReadCount-didReadCount), (olest->bufsize-olest->pos) );

    if (needToReadCount < remainingBytes)	// does the current sector contain all the data I need?
    {
      // printf("  had %d bytes of memory, copy=%d\n", (olest->bufsize-olest->pos), needToReadCount);
      memcpy((BYTE*)buf + didReadCount, olest->buf + olest->pos, needToReadCount);
      olest->pos		+= needToReadCount;
      didReadCount	+= needToReadCount;
    } else {
      // printf("  had %d bytes of memory, copy=%d\n", remainingBytes, remainingBytes);
      memcpy((BYTE*)buf + didReadCount, olest->buf + olest->pos, remainingBytes);
      olest->pos		+= remainingBytes;
      didReadCount	+= remainingBytes;
      ole2_bufread(olest);
    }
    assert(didReadCount <= totalReadCount);
    //printf("  if(fatpos=0x%X==EOC=0x%X) && (pos=%d >= bufsize=%d)\n", olest->fatpos, ENDOFCHAIN, olest->pos, olest->bufsize);
    if ((olest->fatpos == ENDOFCHAIN) && (olest->pos >= olest->bufsize))
    {
      olest->eof=1;
    }

    //printf("  eof=%d (didReadCount=%ld != totalReadCount=%ld)\n", olest->eof, didReadCount, totalReadCount);
  }
  // printf("  didReadCount=%ld EOF=%d\n", didReadCount, olest->eof);
  // printf("=====\n");

  return(didReadCount);
}

// Open stream in logical ole file
OLE2Stream* ole2_sopen(OLE2* ole,DWORD start, int size)
{
  OLE2Stream* olest=NULL;

  olest=(OLE2Stream*)calloc(1, sizeof(OLE2Stream));
  olest->ole=ole;
  olest->size=size;
  olest->fatpos=start;
  olest->start=start;
  olest->pos=0;
  olest->eof=0;
  olest->cfat=-1;
  if(size > 0 && size < (int)ole->sectorcutoff) {
    olest->bufsize=ole->lssector;
    olest->sfat = 1;
  } else {
    olest->bufsize=ole->lsector;
  }
  olest->buf=malloc(olest->bufsize);
  ole2_bufread(olest);

  return olest;
}

// Move in stream
void ole2_seek(OLE2Stream* olest,DWORD ofs)
{
  if(olest->sfat) {
    ldiv_t div_rez=ldiv(ofs,olest->ole->lssector);
    int i;
    olest->fatpos=olest->start;

    if (div_rez.quot!=0)
    {
      for (i=0; i<div_rez.quot; i++)
        olest->fatpos=olest->ole->SSecID[olest->fatpos];
    }

    ole2_bufread(olest);
    olest->pos=div_rez.rem;
    olest->eof=0;
    olest->cfat=div_rez.quot;
    //printf("%i=%i %i\n",ofs,div_rez.quot,div_rez.rem);
  } else {
    ldiv_t div_rez=ldiv(ofs,olest->ole->lsector);
    int i;
    olest->fatpos=olest->start;

    if (div_rez.quot!=0)
    {
      for (i=0; i<div_rez.quot; i++)
        olest->fatpos=olest->ole->SecID[olest->fatpos];
    }

    ole2_bufread(olest);
    olest->pos=div_rez.rem;
    olest->eof=0;
    olest->cfat=div_rez.quot;
    //printf("%i=%i %i\n",ofs,div_rez.quot,div_rez.rem);
  }
}

// Open logical file contained in physical OLE file
OLE2Stream*  ole2_fopen(OLE2* ole,char* file)
{
  OLE2Stream* olest;
  int i;

  for (i=0; i<ole->files.count; i++) {
    char *str = ole->files.file[i].name;
    if (str && strcmp(str,file)==0)	// newer versions of Excel don't write the "Root Entry" string for the first set of data
    {
      olest=ole2_sopen(ole,ole->files.file[i].start,ole->files.file[i].size);
      return(olest);
    }
  }
  return(NULL);
}

// Open physical file
OLE2* ole2_open(const char *file, char *charset)
{
  //BYTE buf[1024];
  OLE2Header* oleh;
  OLE2* ole;
  OLE2Stream* olest;
  PSS*	pss;
  char* name = NULL;

  oleh=(OLE2Header*)malloc(512);
  ole=(OLE2*)calloc(1, sizeof(OLE2));
  if (!(ole->file=fopen(file,"rb")))
  {
    free(ole);
    return(NULL);
  }
  // read header and check magic numbers
  fread(oleh,1,512,ole->file);


  // make sure the file looks good. Note: this code only works on Little Endian machines
  if(oleh->id[0] != 0xE011CFD0 || oleh->id[1] != 0xE11AB1A1 || oleh->byteorder != 0xFFFE) {
    fclose(ole->file);
    printf("Not an excel file\n");
    free(ole);
    return NULL;
  }

  //ole->lsector=(WORD)pow(2,oleh->lsector);
  //ole->lssector=(WORD)pow(2,oleh->lssector);
  ole->lsector=512;
  ole->lssector=64;
  assert(oleh->lsectorB==9);	// 2**9 == 512
  assert(oleh->lssectorB==6);	// 2**6 == 64

  ole->cfat=oleh->cfat;
  ole->dirstart=oleh->dirstart;
  ole->sectorcutoff=oleh->sectorcutoff;
  ole->sfatstart=oleh->sfatstart;
  ole->csfat=oleh->csfat;
  ole->difstart=oleh->difstart;
  ole->cdif=oleh->cdif;
  ole->files.count=0;

  // read directory entries
  read_MSAT(ole, oleh);

  // reuse this buffer
  pss = (PSS*)oleh;
  oleh = (void *)NULL;

  olest=ole2_sopen(ole,ole->dirstart, -1);
  do
  {
    ole2_read(pss,1,sizeof(PSS),olest);

    name=unicode_decode(pss->name, pss->bsize, 0, charset);

    if (pss->type == PS_USER_ROOT || pss->type == PS_USER_STREAM) // (name!=NULL) //
    {
      if (ole->files.count==0)
      {
        ole->files.file=malloc(sizeof(struct st_olefiles_data));
      } else {
        ole->files.file=realloc(ole->files.file,(ole->files.count+1)*sizeof(struct st_olefiles_data));
      }
      ole->files.file[ole->files.count].name=name;
      ole->files.file[ole->files.count].start=pss->sstart;
      ole->files.file[ole->files.count].size=pss->size;
      ole->files.count++;

      if(pss->sstart == ENDOFCHAIN)
      {
      }
      else if(pss->type == PS_USER_STREAM) {
      }
      else if(pss->type == PS_USER_ROOT) {
        DWORD sector, k, blocks;
        BYTE *wptr;

        blocks = (pss->size + (ole->lsector - 1)) / ole->lsector;	// count partial
        ole->SSAT = (BYTE *)malloc(blocks*ole->lsector);
        // printf("blocks %d\n", blocks);

        assert(ole->SSecID);

        sector = pss->sstart;
        wptr=(BYTE*)ole->SSAT;
        for(k=0; k<blocks; ++k) {
          // printf("block %d sector %d\n", k, sector);
          assert(sector != ENDOFCHAIN);
          fseek(ole->file,sector*ole->lsector+512,0);
          fread(wptr,1,ole->lsector,ole->file);
          wptr += ole->lsector;
          sector = ole->SecID[sector];
        }
      }
    }
  }
  while (!olest->eof);
  free(olest);
  free(pss);  // DFH

  return ole;
}

void ole2_close(OLE2* ole2)
{
  fclose(ole2->file);
  free(ole2);
}

void ole2_fclose(OLE2Stream* ole2st)
{
  free(ole2st->buf);
  free(ole2st);
}

// Return offset in bytes of a sector from its sid
static int sector_pos(OLE2* ole2, int sid)
{
  return 512 + sid * ole2->lsector;
}
// Read one sector from its sid
static int sector_read(OLE2* ole2, BYTE *buffer, int sid)
{
  size_t num;
  int seeked;

  seeked = fseek(ole2->file, sector_pos(ole2, sid), SEEK_SET);
  if(seeked != 0) {
    printf("seek: wanted to seek to sector %u (0x%x) loc=%u\n", sid, sid, sector_pos(ole2, sid));
  }
  assert(seeked == 0);

  num = fread(buffer, ole2->lsector, 1, ole2->file);
  if(num != 1) {
    printf("fread: wanted %d got %d loc=%u\n", 1, num, sector_pos(ole2, sid));
  }
  assert(num == 1);

  return 0;
}

// Read MSAT
static int read_MSAT(OLE2* ole2, OLE2Header* oleh)
{
  int sectorNum;

  // reconstitution of the MSAT
  ole2->SecID=malloc(ole2->cfat*ole2->lsector);

  // read first 109 sectors of MSAT from header
  {
    int count;
    count = (ole2->cfat < 109) ? ole2->cfat : 109;
    for (sectorNum = 0; sectorNum < count; sectorNum++)
    {
      assert(sectorNum >= 0);
      sector_read(ole2, (BYTE*)(ole2->SecID)+sectorNum*ole2->lsector, oleh->MSAT[sectorNum]);
    }
  }

  // Add additionnal sectors of the MSAT
  {
    unsigned int sid = ole2->difstart;
    BYTE *sector = malloc(ole2->lsector);

    //printf("sid=%d (0x%x)\n", sid, sid);
    while (sid != ENDOFCHAIN)
    {
      int posInSector;

      // read MSAT sector
      assert((int)sid >= 0);
      sector_read(ole2, sector, sid);

      // read content
      for (posInSector = 0; posInSector < (ole2->lsector-4)/4; posInSector++)
      {
        unsigned int s = *(int*)(sector + posInSector*4);
        //printf("   s[%d]=%d (0x%x)\n", posInSector, s, s);

        if (s != FREESECT)
        {
          assert((int)s >= 0);
          sector_read(ole2, (BYTE*)(ole2->SecID)+sectorNum*ole2->lsector, s);
          sectorNum++;
        }
      }

      sid = *(int*)(sector + posInSector*4);
    }

    free(sector);
  }
  // read in short table
  if(ole2->sfatstart != ENDOFCHAIN) {
    DWORD sector, k;
    BYTE *wptr;

    ole2->SSecID = (DWORD *)malloc(ole2->csfat*ole2->lsector);
    sector = ole2->sfatstart;
    wptr=(BYTE*)ole2->SSecID;
    for(k=0; k<ole2->csfat; ++k) {
      assert(sector != ENDOFCHAIN);
      fseek(ole2->file,sector*ole2->lsector+512,0);
      fread(wptr,1,ole2->lsector,ole2->file);
      wptr += ole2->lsector;
      sector = ole2->SecID[sector];
    }
  }

  return 0;
}


