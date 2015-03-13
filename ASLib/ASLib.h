#ifndef INCLUDE_ASLIB_H
#define INCLUDE_ASLIB_H

typedef  void* ASHANDLE;

#ifndef NULL
#define NULL 0
#endif

#if defined(_WIN32) && !defined(__BORLANDC__)
#ifndef strcasecmp
#define strcasecmp stricmp
#endif

#ifndef strncasecmp
#define strncasecmp strnicmp
#endif
#endif

#include "ASFile.h"

#endif
