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
 * Copyright 2006-2009 Christophe Leitienne
 * Copyright 2008-2009 David Hoerl
 */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include <memory.h>
#include <math.h>
#include <sys/types.h>
#include <string.h>
#include <wchar.h>
#include <assert.h>

#include "xls.h"

#define min(a,b) ((a) < (b) ? (a) : (b))

static double NumFromRk(BYTE* rk);
extern char* xls_addSheet(xlsWorkBook* pWB,BOUNDSHEET* bs);
extern void xls_addRow(xlsWorkSheet* pWS,ROW* row);
extern void xls_makeTable(xlsWorkSheet* pWS);
extern struct st_cell_data *xls_addCell(xlsWorkSheet* pWS,BOF* bof,BYTE* buf);
extern void xls_addColinfo(xlsWorkSheet* pWS,COLINFO* colinfo);
extern void xls_mergedCells(xlsWorkSheet* pWS,BOF* bof,BYTE* buf);
extern void xls_parseWorkBook(xlsWorkBook* pWB);
extern void xls_preparseWorkSheet(xlsWorkSheet* pWS);
extern void xls_formatColumn(xlsWorkSheet* pWS);
extern void xls_parseWorkSheet(xlsWorkSheet* pWS);

extern xlsSummaryInfo *xls_summaryInfo(xlsWorkBook* pWB);
extern void xls_close_summaryInfo(xlsSummaryInfo *pSI);
extern void xls_dumpSummary(char *buf,int isSummary,xlsSummaryInfo	*pSI);

typedef struct {
  uint32_t		format[4];
  uint32_t		offset;
} sectionList;

typedef struct {
  uint16_t		sig;
  uint16_t		_empty;
  uint32_t		os;
  uint32_t		format[4];
  uint32_t		count;
  sectionList		secList[0];
} header;

typedef struct {
  uint32_t		propertyID;
  uint32_t		sectionOffset;
} propertyList;

typedef struct {
  uint32_t		length;
  uint32_t		numProperties;
  propertyList	properties[0];
} sectionHeader;

typedef struct {
  uint32_t		propertyID;
  uint32_t		data[0];
} property;

void xls_addSST(xlsWorkBook* pWB,SST* sst,DWORD size)
{
  pWB->sst.continued=0;
  pWB->sst.lastln=0;
  pWB->sst.lastid=0;
  pWB->sst.lastrt=0;
  pWB->sst.lastsz=0;

  pWB->sst.count = sst->num;
  pWB->sst.string =(struct str_sst_string *)calloc(pWB->sst.count, sizeof(struct str_sst_string));
  xls_appendSST(pWB,&sst->strings,size-8);
}

void xls_appendSST(xlsWorkBook* pWB,BYTE* buf,DWORD size)
{
  DWORD ln; // String character count
  DWORD ofs; // Current offset in SST buffer
  DWORD rt; // Count or rich text formatting runs
  DWORD sz; // Size of asian phonetic settings block
  BYTE flag; // String flags
  char* ret;

  sz = rt = ln = 0;	// kch
  ofs=0;

  while(ofs<size)
  {
    int ln_toread;

    // Restore state when we're in a continue record
    // or read string length
    if (pWB->sst.continued)
    {
      ln=pWB->sst.lastln;
      rt=pWB->sst.lastrt;
      sz=pWB->sst.lastsz;
    }
    else
    {
      ln=*(WORD*)(buf+ofs);
      rt = 0;
      sz = 0;

      ofs+=2;
    }

    // Read flags
    if (  (!pWB->sst.continued)
          ||(  (pWB->sst.continued)
               &&(ln != 0) ) )
    {
      flag=*(BYTE*)(buf+ofs);
      ofs++;

      // Count of rich text formatting runs
      if (flag & 0x8)
      {
        rt=*(WORD*)(buf+ofs);
        ofs+=2;
      }

      // Size of asian phonetic settings block
      if (flag & 0x4)
      {
        sz=*(DWORD*)(buf+ofs);
        ofs+=4;
      }
    }
    else
    {
      flag = 0;
    }

    // Read characters (compressed or not)
    ln_toread = 0;
    if (ln > 0)
    {
      if (flag & 0x1)
      {
        int new_len = 0;
        ln_toread = min((size-ofs)/2, ln);

        ret=unicode_decode(buf+ofs,ln_toread*2, &new_len,pWB->charset);

        if (ret == NULL)
        {
          ret = strdup("*failed to decode utf16*");
          new_len = strlen(ret);
        }

        ret = (char *)realloc(ret,new_len+1);
        *(char*)(ret+new_len)=0;

        ln -= ln_toread;
        ofs+=ln_toread*2;
      }
      else
      {
        ln_toread = min((size-ofs), ln);

        ret = (char *)malloc(ln_toread + 1);
        memcpy (ret, (buf+ofs),ln_toread);
        *(char*)(ret+ln_toread)=0;

        ln -= ln_toread;
        ofs+=ln_toread;
      }
    }
    else
    {
      ret = strdup("");
    }

    if (  (ln_toread > 0)
          ||(!pWB->sst.continued) )
    {
      // Concat string if it's a continue, or add string in table
      if (!pWB->sst.continued)
      {
        pWB->sst.lastid++;
        pWB->sst.string[pWB->sst.lastid-1].str=ret;
      }
      else
      {
        char *tmp;
        tmp=pWB->sst.string[pWB->sst.lastid-1].str;
        tmp=(char *)realloc(tmp,strlen(tmp)+strlen(ret)+1);
        pWB->sst.string[pWB->sst.lastid-1].str=tmp;
        memcpy(tmp+strlen(tmp),ret,strlen(ret)+1);
      }
    }

    // Jump list of rich text formatting runs
    if (  (ofs < size)
          &&(rt > 0) )
    {
      int rt_toread = min((size-ofs)/4, rt);
      rt -= rt_toread;
      ofs += rt_toread*4;
    }

    // Jump asian phonetic settings block
    if (  (ofs < size)
          &&(sz > 0) )
    {
      int sz_toread = min((size-ofs), sz);
      sz -= sz_toread;
      ofs += sz_toread;
    }

    pWB->sst.continued=0;
  }

  // Save current character count and count of rich text formatting runs and size of asian phonetic settings block
  if (ln > 0 || rt > 0 || sz > 0) {
    pWB->sst.continued = 1;
    pWB->sst.lastln = ln;
    pWB->sst.lastrt = rt;
    pWB->sst.lastsz = sz;
  }
}

static double NumFromRk(BYTE* rk)
{
  volatile double num; // volatile necessary at least for Cygwin GCC 3.4.4
  DWORD drk;
  drk=*(DWORD*)rk;

  // What kind of value is this ?
  if (drk & 0x02) {
    // Floating point value;
    num = (double)(drk >> 2);
  } else {
    // Integer value
    *(1+(DWORD *)&num) = drk & 0xfffffffc;
    *((DWORD *)&num) = 0;
  }

  // Is value multiplied by 100 ?
  if (drk & 0x01) {
    num = num / 100.0;
  }

  return num;
}

char* xls_addSheet(xlsWorkBook* pWB, BOUNDSHEET *bs)
{
  char* name;
  DWORD filepos;
  BYTE visible, type;

  filepos = bs->filepos;
  visible = bs->visible;
  type = bs->type;

  name=get_string(bs->name, 0, pWB->is5ver, pWB->charset);

  if (pWB->sheets.count==0)
  {
    pWB->sheets.sheet=(struct st_sheet_data *) malloc((pWB->sheets.count+1)*sizeof (struct st_sheet_data));
  }
  else
  {
    pWB->sheets.sheet=(struct st_sheet_data *) realloc(pWB->sheets.sheet,(pWB->sheets.count+1)*sizeof (struct st_sheet_data));
  }
  pWB->sheets.sheet[pWB->sheets.count].name=name;
  pWB->sheets.sheet[pWB->sheets.count].filepos=filepos;
  pWB->sheets.sheet[pWB->sheets.count].visibility=visible;
  pWB->sheets.sheet[pWB->sheets.count].type=type;
  pWB->sheets.count++;

  return name;
}

void xls_addRow(xlsWorkSheet* pWS,ROW* row)
{
  struct st_row_data* tmp;

  tmp=&pWS->rows.row[row->index];
  tmp->height=row->height;
  tmp->fcell=row->fcell;
  tmp->lcell=row->lcell;
  tmp->flags=row->flags;
  tmp->xf=row->xf&0xFF;
  tmp->xfflags=(row->xf&0xF000)>>12;
}

void xls_makeTable(xlsWorkSheet* pWS)
{
  WORD i,t;
  struct st_row_data* tmp;
  pWS->rows.row=(struct st_row_data *)calloc((pWS->rows.lastrow+1),sizeof(struct st_row_data));

  for (t=0; t<=pWS->rows.lastrow; t++)
  {
    tmp=&pWS->rows.row[t];
    tmp->index=t;
    tmp->fcell=0;
    tmp->lcell=pWS->rows.lastcol;

    tmp->cells.cell=(struct st_cell_data *)calloc((pWS->rows.lastcol+1),sizeof(struct st_cell_data));

    for (i=0; i<=pWS->rows.lastcol; i++)
    {
      tmp->cells.cell[i].col=i;
      tmp->cells.cell[i].row=t;
      tmp->cells.cell[i].width=pWS->defcolwidth;
      tmp->cells.cell[i].xf=0;
      tmp->cells.cell[i].str=NULL;
      tmp->cells.cell[i].d=0;
      tmp->cells.cell[i].l=0;
      tmp->cells.cell[i].ishiden=0;
      tmp->cells.cell[i].colspan=0;
      tmp->cells.cell[i].rowspan=0;
      tmp->cells.cell[i].id=0x201;
      tmp->cells.cell[i].str=NULL;
    }
  }
}

struct st_cell_data *xls_addCell(xlsWorkSheet* pWS,BOF* bof,BYTE* buf)
{
  struct st_cell_data*	cell;
  struct st_row_data*		row;
  int						i;

  row=&pWS->rows.row[((COL*)buf)->row];
  cell=&row->cells.cell[((COL*)buf)->col];

  cell->id=bof->id;
  cell->xf=((COL*)buf)->xf;

  switch (bof->id)
  {
  case 0x0006:	//FORMULA
    // test for formula, if
    if (((FORMULA*)buf)->res!=0xffff) {
      cell->l=0;
      // if a double, then set double and clear l
      cell->d=*(double *)&((FORMULA*)buf)->resid;
      cell->str=xls_getfcell(pWS->workbook,cell);
    } else {
      cell->l = 0xFFFF;
      switch(((FORMULA*)buf)->resid) {
      case 0:		// String
        return cell;	// cell is half complete, get the STRING next record
      case 1:		// Boolean
        cell->d = (double)((FORMULA*)buf)->resdata[2];
        sprintf((cell->str = malloc(5)), "bool");
        break;
      case 2:		// error
        cell->d = (double)((FORMULA*)buf)->resdata[2];
        sprintf((cell->str = malloc(6)), "error");
        break;
      case 3:		// empty string
        cell->str = calloc(1,1);
        break;
      }
    }
    break;
  case 0x00BD:	//MULRK
    for (i=0; i<=*(WORD *)(buf+(bof->size-2))-((COL*)buf)->col; i++)
    {
      cell=&row->cells.cell[((COL*)buf)->col + i];
      //cell=&row->cells.cell[((COL*)buf)->col - row->fcell + i];  DFH - inconsistent
      //				col=row->cols[i];
      cell->id=bof->id;
      cell->xf=*((WORD *)(buf+(4+i*6)));
      cell->d=NumFromRk((BYTE *)(buf+(4+i*6+2)));
      cell->str=xls_getfcell(pWS->workbook,cell);
    }
    break;
  case 0x00BE:	//MULBLANK
    for (i=0; i<=*(WORD *)(buf+(bof->size-2))-((COL*)buf)->col; i++)
    {
      cell=&row->cells.cell[((COL*)buf)->col + i];
      //cell=&row->cells.cell[((COL*)buf)->col-row->fcell+i];
      //				col=row->cols[i];
      cell->id=bof->id;
      cell->xf=*((WORD *)(buf+(4+i*2)));
      cell->str=xls_getfcell(pWS->workbook,cell);
    }
    break;
  case 0x00FD:	//LABELSST
    cell->l=*(WORD *)&((LABELSST*)buf)->value;
    cell->str=xls_getfcell(pWS->workbook,cell);
    break;
  case 0x027E:	//RK
    cell->d=NumFromRk(((RK*)buf)->value);
    cell->str=xls_getfcell(pWS->workbook,cell);
    break;
  case 0x0201:	//BLANK
    break;
  case 0x0203:	//NUMBER
    cell->d=*(double *)&((BR_NUMBER*)buf)->value;
    cell->str=xls_getfcell(pWS->workbook,cell);
    break;
  case 0x0204:	//LABEL
    cell->l = (long)&((LABEL*)buf)->value;
    cell->str=xls_getfcell(pWS->workbook,cell);
    cell->l = 0;
    break;
  default:
    cell->str=xls_getfcell(pWS->workbook,cell);
    break;
  }

  return cell;
}

void xls_addColinfo(xlsWorkSheet* pWS,COLINFO* colinfo)
{
  struct st_colinfo_data* tmp;

  if (pWS->colinfo.count==0)
  {
    pWS->colinfo.col=(struct st_colinfo_data *) malloc(sizeof(struct st_colinfo_data));
  }
  else
  {
    pWS->colinfo.col=(struct st_colinfo_data *) realloc(pWS->colinfo.col,(pWS->colinfo.count+1)*sizeof(struct st_colinfo_data));
  }

  tmp=&pWS->colinfo.col[pWS->colinfo.count];
  tmp->first=colinfo->first;
  tmp->last=colinfo->last;
  tmp->width=colinfo->width;
  tmp->xf=colinfo->xf;
  tmp->flags=colinfo->flags;

  pWS->colinfo.count++;
}

void xls_mergedCells(xlsWorkSheet* pWS,BOF* bof,BYTE* buf)
{
  int count=*((WORD*)buf);
  int i,c,r;
  struct MERGEDCELLS* span;

  for (i=0; i<count; i++)
  {
    span=(struct MERGEDCELLS*)(buf+(2+i*sizeof(struct MERGEDCELLS)));
    //		printf("Merged Cells: [%i,%i] [%i,%i] \n",span->colf,span->rowf,span->coll,span->rowl);
    for (r=span->rowf; r<=span->rowl; r++)
      for (c=span->colf; c<=span->coll; c++)
        pWS->rows.row[r].cells.cell[c].ishiden=1;
    pWS->rows.row[span->rowf].cells.cell[span->colf].colspan=(span->coll-span->colf+1);
    pWS->rows.row[span->rowf].cells.cell[span->colf].rowspan=(span->rowl-span->rowf+1);
    pWS->rows.row[span->rowf].cells.cell[span->colf].ishiden=0;
  }
}

void xls_parseWorkBook(xlsWorkBook* pWB)
{
  BOF bof1;
  BOF bof2;
  BYTE* buf;
  BYTE once;
  //DWORD size;

  // this to prevent compiler warnings
  once=0;
  bof2.size = 0;
  bof2.id = 0;
  do
  {
    ole2_read(&bof1, 1, 4, pWB->olestr);

    buf=(BYTE *)malloc(bof1.size);
    ole2_read(buf, 1, bof1.size, pWB->olestr);

    switch (bof1.id) {
    case 0x00A:		// EOF
      //verbose("EOF");
      break;
    case 0x809:		// BIFF5-8
    {
      BIFF *b = (BIFF*)buf;
      if (b->ver==0x600)
        pWB->is5ver=0;
      else
        pWB->is5ver=1;
      pWB->type=b->type;
    }
    break;
    case 0x042:		// CODEPAGE
      pWB->codepage=*(WORD*)buf;
      break;
    case 0x03c:		// CONTINUE
      if(once) {
        if (bof2.id==0xfc)
          xls_appendSST(pWB,buf,bof1.size);
        bof1=bof2;
      }
      break;
    case 0x003D:	// WINDOW1
      break;
    case 0x0fc:		// SST
      xls_addSST(pWB,(SST*)buf,bof1.size);
      break;
    case 0x0ff:		// EXTSST
      break;
    case 0x085:		// BOUNDSHEET
    {
      BOUNDSHEET *bs = (BOUNDSHEET *)buf;
      char *s;
      // different for BIFF5 and BIFF8
      s = xls_addSheet(pWB,bs);
    }
    break;
    case 0x0e0:  	// XF
      break;
    case 0x031:		// FONT
      break;
    case 0x41E:		//FORMAT
      break;
    case 0x0293:	// STYLE
      break;
    case 0x0092:	// PALETTE
      break;
    case 0x0022: // 1904
      break;
    default:
      break;
    }
    free(buf);

    bof2=bof1;
    once=1;

  }
  while ((!pWB->olestr->eof)&&(bof1.id!=0x0A));
}

void xls_preparseWorkSheet(xlsWorkSheet* pWS)
{
  BOF tmp;
  BYTE* buf;

  ole2_seek(pWS->workbook->olestr,pWS->filepos);
  do
  {
    ole2_read(&tmp, 1,4,pWS->workbook->olestr);
    buf=(BYTE *)malloc(tmp.size);
    ole2_read(buf, 1,tmp.size,pWS->workbook->olestr);
    switch (tmp.id)
    {
    case 0x55:     //DEFCOLWIDTH
      pWS->defcolwidth=*(WORD*)buf*256;
      break;
    case 0x7D:     //COLINFO
      xls_addColinfo(pWS,(COLINFO*)buf);
      break;
    case 0x208:		//ROW
      if (pWS->rows.lastcol<((ROW*)buf)->lcell)
        pWS->rows.lastcol=((ROW*)buf)->lcell;
      if (pWS->rows.lastrow<((ROW*)buf)->index)
        pWS->rows.lastrow=((ROW*)buf)->index;
      break;
    }
    free(buf);
  }
  while ((!pWS->workbook->olestr->eof)&&(tmp.id!=0x0A));
}

void xls_formatColumn(xlsWorkSheet* pWS)
{
  DWORD i,t,ii;
  DWORD fcol,lcol;

  for (i=0; i<pWS->colinfo.count; i++)
  {
    if (pWS->colinfo.col[i].first<=pWS->rows.lastcol)
      fcol=pWS->colinfo.col[i].first;
    else
      fcol=pWS->rows.lastcol;

    if (pWS->colinfo.col[i].last<=pWS->rows.lastcol)
      lcol=pWS->colinfo.col[i].last;
    else
      lcol=pWS->rows.lastcol;

    for (t=fcol; t<=lcol; t++) {
      for (ii=0; ii<=pWS->rows.lastrow; ii++)
      {
        if (pWS->colinfo.col[i].flags&1)
          pWS->rows.row[ii].cells.cell[t].ishiden=1;
        pWS->rows.row[ii].cells.cell[t].width=pWS->colinfo.col[i].width;
      }
    }
  }
}

void xls_parseWorkSheet(xlsWorkSheet* pWS)
{
  BOF tmp;
  BYTE* buf;
  struct st_cell_data *cell;
  xlsWorkBook *pWB = pWS->workbook;

  xls_preparseWorkSheet(pWS);
  // printf("size=%d fatpos=%d)\n", pWS->workbook->olestr->size, pWS->workbook->olestr->fatpos);

  xls_makeTable(pWS);
  xls_formatColumn(pWS);

  cell = (void *)0;
  ole2_seek(pWS->workbook->olestr,pWS->filepos);
  do
  {
    ole2_read(&tmp, 1,4,pWS->workbook->olestr);
    buf=(BYTE *)malloc(tmp.size);
    ole2_read(buf, 1,tmp.size,pWS->workbook->olestr);

    switch (tmp.id)
    {
    case 0x0A:		//EOF
      break;
    case 0x0E5: 	//MERGEDCELLS
      xls_mergedCells(pWS,&tmp,buf);
      break;
    case 0x208:		//ROW
      xls_addRow(pWS,(ROW*)buf);
      break;
    case 0x20B:		//INDEX
      break;
    case 0x0BD:		//MULRK
    case 0x0BE:		//MULBLANK
    case 0x203:		//NUMBER
    case 0x27e:		//RK
    case 0xFD:		//LABELSST
    case 0x201:		//BLANK
    case 0x204:		//LABEL
    case 0x06:		//FORMULA
      cell = xls_addCell(pWS,&tmp,buf);
      break;
    case 0x207:		//STRING, only follows a formula
      if(cell && cell->id == 0x06) { // formula
        cell->str = get_string(buf, !pWB->is5ver, pWB->is5ver, pWB->charset);
      }
      break;
    default:
      break;
    }
    free(buf);
  }
  while ((!pWS->workbook->olestr->eof)&&(tmp.id!=0x0A));  // 0x0A == EOF
}

xlsWorkSheet * xls_getWorkSheet(xlsWorkBook* pWB,int num)
{
  xlsWorkSheet * pWS;
  pWS=(xlsWorkSheet *)calloc(1, sizeof(xlsWorkSheet));
  pWS->filepos=pWB->sheets.sheet[num].filepos;
  pWS->workbook=pWB;
  pWS->rows.lastcol=0;
  pWS->rows.lastrow=0;
  pWS->colinfo.count=0;
  return(pWS);
}

xlsWorkBook* xls_open(const char *file,char* charset)
{
  xlsWorkBook* pWB;
  OLE2*		ole;

  pWB=(xlsWorkBook*)calloc(1, sizeof(xlsWorkBook));

  // open excel file
  if (!(ole=ole2_open(file, charset)))
  {
    return(NULL);
  }

  if ((pWB->olestr=ole2_fopen(ole,"\005SummaryInformation")))
  {
    pWB->summary = calloc(1,4096);
    ole2_read(pWB->summary, 4096, 1, pWB->olestr);
    ole2_fclose(pWB->olestr);
  }

  if ((pWB->olestr=ole2_fopen(ole,"\005DocumentSummaryInformation")))
  {
    pWB->docSummary = calloc(1,4096);
    ole2_read(pWB->docSummary, 4096, 1, pWB->olestr);
    ole2_fclose(pWB->olestr);
  }

  // open Workbook
  if (!(pWB->olestr=ole2_fopen(ole,"Workbook")) && !(pWB->olestr=ole2_fopen(ole,"Book")))
  {
    ole2_close(ole);
    return(NULL);
  }

  pWB->sheets.count=0;
  pWB->charset = (char *)malloc(strlen(charset) * sizeof(char));
  strcpy(pWB->charset, charset);
  xls_parseWorkBook(pWB);

  return(pWB);
}

xlsRow *xls_row(xlsWorkSheet* pWS, WORD cellRow)
{
  struct st_row_data *row;

  if(cellRow > pWS->rows.lastrow) return NULL;
  row = &pWS->rows.row[cellRow];

  return row;
}

xlsCell	*xls_cell(xlsWorkSheet* pWS, WORD cellRow, WORD cellCol)
{
  struct st_row_data	*row;

  if(cellRow > pWS->rows.lastrow) return NULL;
  row = &pWS->rows.row[cellRow];
  if(cellCol >= row->lcell) return NULL;

  return &row->cells.cell[cellCol];
}

void xls_close_WB(xlsWorkBook* pWB)
{
  OLE2*		ole;

  // OLE first
  ole=pWB->olestr->ole;
  ole2_fclose(pWB->olestr);
  ole2_close(ole);

  // WorkBook
  free(pWB->charset);

  // Sheets
  {
    DWORD i;
    for(i=0; i<pWB->sheets.count; ++i) {
      free(pWB->sheets.sheet[i].name);
    }
    free(pWB->sheets.sheet);
  }

  // SST
  {
    DWORD i;
    for(i=0; i<pWB->sst.count; ++i) {
      free(pWB->sst.string[i].str);
    }
    free(pWB->sst.string);
  }

  // buffers
  if(pWB->summary)  free(pWB->summary);
  if(pWB->docSummary) free(pWB->docSummary);

  // TODO - free other dynamically allocated objects like string table??
  free(pWB);
}

void xls_close_WS(xlsWorkSheet* pWS)
{
//    st_colinfo	colinfo;

  // ROWS
  {
    DWORD i, j;
    for(j=0; j<pWS->rows.lastrow; ++j) {
      struct st_row_data *row = &pWS->rows.row[j];
      for(i=0; i<row->cells.count; ++i) {
        free(row->cells.cell[i].str);
      }
      free(row->cells.cell);
    }
    free(pWS->rows.row);

  }

  // COLINFO
  {
    free(pWS->colinfo.col);
  }
  free(pWS);
}

//
// http://poi.apache.org/hpsf/internals.html
// or google "DocumentSummaryInformation and UserDefined Property Sets" and look for MSDN hits
//

xlsSummaryInfo *xls_summaryInfo(xlsWorkBook* pWB)
{
  xlsSummaryInfo	*pSI;

  pSI = (xlsSummaryInfo *)calloc(1, sizeof(xlsSummaryInfo));
  xls_dumpSummary(pWB->summary, 1, pSI);
  xls_dumpSummary(pWB->docSummary, 0, pSI);

  return pSI;
}

void xls_close_summaryInfo(xlsSummaryInfo *pSI)
{
  if(pSI->title)		free(pSI->title);
  if(pSI->subject)	free(pSI->subject);
  if(pSI->author)		free(pSI->author);
  if(pSI->keywords)	free(pSI->keywords);
  if(pSI->comment)	free(pSI->comment);
  if(pSI->lastAuthor)	free(pSI->lastAuthor);
  if(pSI->appName)	free(pSI->appName);
  if(pSI->category)	free(pSI->category);
  if(pSI->manager)	free(pSI->manager);
  if(pSI->company)	free(pSI->company);

  free(pSI);
}

void xls_dumpSummary(char *buf,int isSummary,xlsSummaryInfo *pSI) {
  header			*head;
  sectionList		*secList;
  propertyList	*plist;
  sectionHeader	*secHead;
  property		*prop;
  uint32_t i, j;

  if(!buf) return;	// perhaps the document was missing??

  head = (header *)buf;
  //printf("header: \n");
  //printf("  sig=%x\n", head->sig);
  //printf("  os=%x\n", head->os >> 16);
  //printf("  class=%8.8x%8.8x%8.8x%8.8x\n", head->format[0], head->format[1], head->format[2], head->format[3]);
  //printf("  count=%x\n", head->count);

  for(i=0; i<head->count; ++i) {
    secList = &head->secList[i];
    //printf("Section %d:\n", i);
    //printf("  class=%8.8x%8.8x%8.8x%8.8x\n", secList->format[0], secList->format[1], secList->format[2], secList->format[3]);
    //printf("  offset=%d (now at %ld\n", secList->offset, (char *)secList - (char *)buf + sizeof(sectionList));


    secHead = (sectionHeader *)((char *)head + secList->offset);
    //printf("  len=%d\n", secHead->length);
    //printf("  properties=%d\n", secHead->numProperties);
    for(j=0; j<secHead->numProperties; ++j) {
      char **s;

      plist = &secHead->properties[j];
      //printf("      ---------\n");
      //printf("      propID=%d offset=%d\n", plist->propertyID, plist->sectionOffset);
      prop = (property *)((char *)secHead + plist->sectionOffset);
      //printf("      propType=%d\n", prop->propertyID);

      switch(prop->propertyID) {
      case 2:
        //printf("      shortVal=%x\n", *(uint16_t *)prop->data);
        break;
      case 3:
        //printf("      wordVal=%x\n", *(uint32_t *)prop->data);
        break;
      case 30:
        //printf("      longVal=%llx\n", *(uint64_t *)prop->data);
        //printf("      s[%u]=%s\n", *(uint32_t  *)prop->data, (char *)prop->data + 4);
        if(isSummary) {
          switch(plist->propertyID) {
          case 2:
            s = &pSI->title;
            break;
          case 3:
            s = &pSI->subject;
            break;
          case 4:
            s = &pSI->author;
            break;
          case 5:
            s = &pSI->keywords;
            break;
          case 6:
            s = &pSI->comment;
            break;
          case 8:
            s = &pSI->lastAuthor;
            break;
          case 18:
            s = &pSI->appName;
            break;
          default:
            s = NULL;
            break;
          }
        } else {
          switch(plist->propertyID) {
          case 2:
            s = &pSI->category;
            break;
          case 14:
            s = &pSI->manager;
            break;
          case 15:
            s = &pSI->company;
            break;
          default:
            s = NULL;
            break;
          }
        }
        if(s) *s = strdup((char *)prop->data + 4);
        break;
      case 64:
        //printf("      longVal=%llx\n", *(uint64_t *)prop->data);
        break;
      case 65:
        break;
      default:
        //printf("      UNKNOWN!\n");
        break;
      }
    }
  }
}
