#include "ASLib.h"

#include <stdlib.h>
#include <string.h>
#include <malloc.h>

#include "ASIni.h"
#include "ASXls.h"



ASFILE_TYPE ASFile_get_file_type(const char *filename)
{
  const char* p = strrchr(filename, '.');

  if (strncasecmp(p, ".ini", 4) == 0)
  {
    return ASFILE_TYPE_INI;
  }

  if (strncasecmp(p, ".xls", 4) == 0)
  {
    return ASFILE_TYPE_XLS;
  }

  return ASFILE_TYPE_UNKNOW;
}

ASHANDLE ASFileOpen(const char *filename)
{
  ASFile* self = NULL;

  self = (ASFile*) malloc(sizeof(ASFile));
  if (NULL == self)
  {
    return NULL;
  }
  memset(self, 0, sizeof(ASFile));

  self->type = ASFile_get_file_type(filename);

  switch (self->type)
  {
  case ASFILE_TYPE_INI:
    self->ptr  = ASIniLoad(filename);
    break;
  case ASFILE_TYPE_XLS:
    self->ptr  = ASXlsLoad(filename);
    break;
  default:
    break;
  }

  return (ASHANDLE)self;
}

void ASFileClose(ASHANDLE hFile)
{
  PASFile self = (PASFile)hFile;

  if (self == NULL)
  {
    return ;
  }

  switch (self->type)
  {
  case ASFILE_TYPE_INI:
    ASIniClose(self->ptr);
    break;
  case ASFILE_TYPE_XLS:
    ASXlsClose(self->ptr);
    break;
  default:
    break;
  }

  free(self);
}
//----------------------------------------------------
const char* ASFileGetHeroName(ASHANDLE hFile)
{
  static const char* def = "Unknow";
  PASFile self = (PASFile)hFile;

  if (self == NULL)
  {
    return def;
  }

  switch (self->type)
  {
  case ASFILE_TYPE_INI:
    return ASIniGetString(self->ptr, "基本信息", "名字", def);
  case ASFILE_TYPE_XLS:
    return ASXlsGetString(self->ptr, 2, 44, def);
    break;
  default:
    break;
  }
  return def;
}

int ASFileGetHeroLevel(ASHANDLE hFile)
{
  static int def = 0;
  PASFile self = (PASFile)hFile;

  if (self == NULL)
  {
    return def;
  }

  switch (self->type)
  {
  case ASFILE_TYPE_INI:
    return ASIniGetInt(self->ptr, "基本信息", "等级", def);
  case ASFILE_TYPE_XLS:
    return ASXlsGetInt(self->ptr, 2, 3, def);
  default:
    break;
  }
  return def;
}

//----------------------------------------------------
const char* ASFileGetAbilityName(ASHANDLE hFile)
{
  static const char* def = "Unknow";
  PASFile self = (PASFile)hFile;

  if (self == NULL)
  {
    return def;
  }

  switch (self->type)
  {
  case ASFILE_TYPE_INI:
    return ASIniGetString(self->ptr, "主动技能", "名字", def);
  case ASFILE_TYPE_XLS:
    return ASXlsGetString(self->ptr, 2, 46, def);
  default:
    break;
  }
  return def;
}

int ASFileGetAbilityLevel(ASHANDLE hFile)
{
  static int def = 1;
  PASFile self = (PASFile)hFile;

  if (self == NULL)
  {
    return def;
  }

  switch (self->type)
  {
  case ASFILE_TYPE_INI:
    return ASIniGetInt(self->ptr, "主动技能", "等级", def);
  case ASFILE_TYPE_XLS:
    return ASXlsGetInt(self->ptr, 3, 46, def);
  default:
    break;
  }
  return def;
}

int ASFileGetAbilityData(ASHANDLE hFile)
{
  static int def = 0;
  PASFile self = (PASFile)hFile;

  if (self == NULL)
  {
    return def;
  }

  switch (self->type)
  {
  case ASFILE_TYPE_INI:
    return ASIniGetInt(self->ptr, "主动技能", "自定义参数", def);
  case ASFILE_TYPE_XLS:
    return ASXlsGetInt(self->ptr, 4, 46, def);
  default:
    break;
  }
  return def;
}

//----------------------------------------------------
const char* ASFileGetAttachAbilityNameByIndex(ASHANDLE hFile, unsigned int index)
{
  static const char* def = "";
  PASFile self = (PASFile)hFile;

  if (self == NULL)
  {
    return def;
  }

  switch (self->type)
  {
  case ASFILE_TYPE_INI:
    return ASIniGetValueNameByIndex(self->ptr, "附加技能", index, def);
  case ASFILE_TYPE_XLS:
    return ASXlsGetString(self->ptr, 2, 47+index, def);
  default:
    break;
  }
  return def;
}

int ASFileGetAttachAbilityLevelByIndex(ASHANDLE hFile, unsigned int index)
{
  static int def = 0;
  PASFile self = (PASFile)hFile;

  if (self == NULL)
  {
    return def;
  }

  switch (self->type)
  {
  case ASFILE_TYPE_INI:
    return ASIniGetIntByIndex(self->ptr, "附加技能", index, def);
  case ASFILE_TYPE_XLS:
    return ASXlsGetInt(self->ptr, 3, 47+index, def);
  default:
    break;
  }
  return def;
}

