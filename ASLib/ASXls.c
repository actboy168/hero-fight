#include "ASLib.h"
#include "libxls/xls.h"

#include <stdlib.h>
#include <string.h>
#include <malloc.h>

#ifndef MAX_PATH
#define MAX_PATH 260
#endif

typedef struct
{
  xlsWorkBook*  pWorkBook;
  xlsWorkSheet* pWorkSheet;
}
ASXls, *PASXls;

ASHANDLE ASXlsLoad(const char *filename)
{
  ASXls* self = NULL;
  char* sheet = NULL;
  int   index = 0;
  char path[MAX_PATH];

  self = (ASXls*) malloc(sizeof(ASXls));
  if (NULL == self)
  {
    return NULL;
  }
  memset(self, 0, sizeof(ASXls));

  strcpy(path, filename);
  sheet = strrchr(path, '#');

  if (sheet != NULL)
  {
    *sheet = '\0';
    index = atoi(sheet+1)-1;
  }

  self->pWorkBook = xls_open(path, "UTF-8");
  if (self->pWorkBook != NULL)
  {
    if (index < 0 || index >= self->pWorkBook->sheets.count)
    {
      index = 0;
    }
    self->pWorkSheet = xls_getWorkSheet(self->pWorkBook, index);
    xls_parseWorkSheet(self->pWorkSheet);
  }

  return (ASHANDLE)self;
}

const char* ASXlsGetString(ASHANDLE hXls, int x, int y, const char* def)
{
  PASXls self = (PASXls)hXls;

  if (self == NULL || self->pWorkSheet == NULL)
  {
    return def;
  }

  if (x < 0 || y < 0)
  {
    return def;
  }

  if (y > self->pWorkSheet->rows.lastrow || x > self->pWorkSheet->rows.lastcol)
  {
    return def;
  }

  {
    char* ret = self->pWorkSheet->rows.row[y].cells.cell[x].str;

    if (NULL == ret)
      return def;
    else
      return ret;
  }
}

int ASXlsGetInt(ASHANDLE hXls, int x, int y, int def)
{
  const char* ret = ASXlsGetString(hXls, x, y, "");

  if (ret == NULL || *ret == '\0')
  {
    return def;
  }
  else
  {
    return atoi(ret);
  }
}

void ASXlsClose(ASHANDLE hXls)
{
  PASXls self = (PASXls)hXls;

  if (self == NULL)
  {
    return ;
  }

  if (NULL != self->pWorkSheet)
  {
    xls_close_WS(self->pWorkSheet);
  }

  if (NULL != self->pWorkBook)
  {
    xls_close_WB(self->pWorkBook);
  }

  free(self);
}
