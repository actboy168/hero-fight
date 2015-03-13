#ifndef INCLUDE_ASXLS_H
#define INCLUDE_ASXLS_H

#include "ASLib.h"

ASHANDLE    ASXlsLoad(const char *filename);
const char* ASXlsGetString(ASHANDLE hXls, int x, int y, const char* def);
int         ASXlsGetInt(ASHANDLE hXls, int x, int y, int def);
void        ASXlsClose(ASHANDLE hXls);

#endif
