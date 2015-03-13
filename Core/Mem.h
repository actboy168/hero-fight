#ifndef INCLUDE_MEM
#define INCLUDE_MEM

#include <stdlib.h>

#define Mem_new(p, type) ((p) = malloc(sizeof(type)))
#define Mem_delete(p) do {if (p != NULL) free(p);}while(0)

#endif
