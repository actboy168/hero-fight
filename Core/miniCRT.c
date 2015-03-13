#include "miniCRT.h"
#include <time.h>

unsigned long _seed;

void Crt_init()
{
  _seed = time(NULL);
}

static unsigned long Rand()
{
  return (((_seed = _seed * 214013L + 2531011L) >> 16) & 0x7FFF);
}

unsigned long Crt_GetRandomInt(unsigned long min, unsigned long max)
{
  return min+(((max-min+1)*Rand())>>15);
}

int Crt_GetRandomPercent(unsigned long p)
{
  return (((100*Rand())>>15) < p);
}

int Crt_GetRoundUp(float f)
{
  int n = (int)f;
  if (f - n > 0.0) n++;
  return n;
}
