#ifndef INCLUDE_ASINI_H
#define INCLUDE_ASINI_H

#include "ASLib.h"

ASHANDLE ASIniLoad(const char *filename);
int ASIniSave(ASHANDLE hIni, const char *filename);
const char* ASIniGetString(ASHANDLE hIni, const char *key, const char *value, const char* def);
int ASIniGetInt(ASHANDLE hIni, const char *key, const char *value, int def);
void ASIniClose(ASHANDLE hIni);

const char* ASIniGetValueNameByIndex(ASHANDLE hIni, const char *key, unsigned int index, const char* def);
const char* ASIniGetStringByIndex(ASHANDLE hIni, const char *key, unsigned int index, const char* def);
int ASIniGetIntByIndex(ASHANDLE hIni, const char *key, unsigned int index, int def);

#endif
