#ifndef INCLUDE_ASFILE_H
#define INCLUDE_ASFILE_H

#include "ASLib.h"

#include "ASIni.h"
#include "ASXls.h"

typedef enum
{
  ASFILE_TYPE_UNKNOW = 1,
  ASFILE_TYPE_INI,
  ASFILE_TYPE_XLS,
} ASFILE_TYPE;

typedef struct _tag_ASFile
{
  ASHANDLE    ptr;
  ASFILE_TYPE type;
}
ASFile, *PASFile;

//----------------------------------------------------
ASHANDLE    ASFileOpen(const char *filename);
void        ASFileClose(ASHANDLE hFile);
//----------------------------------------------------
const char* ASFileGetHeroName(ASHANDLE hFile);
int         ASFileGetHeroLevel(ASHANDLE hFile);
//----------------------------------------------------
const char* ASFileGetAbilityName(ASHANDLE hFile);
int         ASFileGetAbilityLevel(ASHANDLE hFile);
int         ASFileGetAbilityData(ASHANDLE hFile);
//----------------------------------------------------
const char* ASFileGetAttachAbilityNameByIndex(ASHANDLE hFile, unsigned int index);
int         ASFileGetAttachAbilityLevelByIndex(ASHANDLE hFile, unsigned int index);
//----------------------------------------------------


#define ASFileGetHeroInfo_ini(hFile, key, def)  (ASIniGetInt((hFile), "属性", (key), (def)))
#define ASFileGetHeroInfo_xls(hFile, x, y, def) (ASXlsGetInt((hFile), (x)-'A', (y)-1, (def)))

#endif
