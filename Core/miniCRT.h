#ifndef INCLUDE_MINICRT
#define INCLUDE_MINICRT

void Crt_init();
int Crt_GetRandomPercent(unsigned long p);
unsigned long Crt_GetRandomInt(unsigned long min, unsigned long max);
int Crt_GetRoundUp(float f);

#endif
