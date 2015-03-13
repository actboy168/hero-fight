#include "HeroState.h"

#include "Config.h"
#include "Output.h"
#include "miniCRT.h"
#include "Mem.h"

struct HeroState
{
  // 等级压制修正值
  double fix;

  int BJAddup, PJAddup, MZAddup, ARAddup;

  // 战斗统计
  int CSCount, MZCount, BJCount, PJCount, BPCount, ARCount;
};

static int isTurn(int* addup, int cur)
{
  *addup += ((cur > 100)? 100: cur);
  if ((*addup > 0) && Crt_GetRandomPercent(*addup))
  {
    *addup -= 100;
    return 1;
  }
  else
  {
    return 0;
  }
}

int HeroState_isMingZhong(struct HeroState* self, int attribMZ,  int attribSB, int flag, int isStats)
{
  int mz = attribSB, ret = 0;

  //闪避最小为0
  if (mz < 0) mz = 0;
  mz = attribMZ - mz;

  if (flag)
    mz = (int)(self->fix*mz);

  if (mz < CONST_MIN_MZ) mz = CONST_MIN_MZ;
  if (mz > CONST_MAX_MZ) mz = CONST_MAX_MZ;

  ret = isTurn(&self->MZAddup, mz);
  if (isStats)
  {
    self->CSCount++;
    self->MZCount += ret;
  }
  return ret;
}

int HeroState_isBJAndPJ(struct HeroState* self, int attribBJ, int attribKB, int attribPJ, int attribKP, int flag, int isStats)
{
  int bj = attribBJ - attribKB,  pj = attribPJ - attribKP;

  if (flag)
  {
    bj = (int)(self->fix*bj);
    pj = (int)(self->fix*pj);
  }

  if (bj < CONST_MIN_BJ) bj = CONST_MIN_BJ;
  if (bj > CONST_MAX_BJ) bj = CONST_MAX_BJ;

  if (pj < CONST_MIN_PJ) pj = CONST_MIN_PJ;
  if (pj > CONST_MAX_PJ) pj = CONST_MAX_PJ;

  bj = isTurn(&self->BJAddup, bj);
  pj = isTurn(&self->PJAddup, pj);

  if (isStats)
  {
    self->BJCount += bj;
    self->PJCount += pj;
    self->BPCount += (bj&&pj);
  }

  return ((bj<<1) | pj);
}

int HeroState_checkAbilityRandom(struct HeroState* self, int AR, int flag, int isStats)
{
  int ret = 0;
  ret = isTurn(&self->ARAddup, AR);
  if (isStats) self->ARCount += ret;
  return ret;
}

void HeroState_setFix(struct HeroState* self, int LvSub)
{
  static double modify[] = {
  //-10 ~ -1
  0.500, 0.500, 0.500, 0.588, 0.741,
  0.850, 0.923, 0.968, 0.990, 0.999,
  // 0
  1.000,
  // 1 ~ 10
  1.001, 1.010, 1.032, 1.077, 1.150,
  1.259, 1.412, 1.614, 1.875, 2.000,
  };

  if (LvSub < -10) LvSub = -10;
  if (LvSub >  10) LvSub =  10;

  self->fix = modify[LvSub+10];
}

struct HeroState* HeroState_Create()
{
  struct HeroState* self = Mem_new(self, struct HeroState);

  memset(self, 0, sizeof(struct HeroState));

  HeroState_setFix(self, 0);

  return self;
}

void HeroState_Destroy(struct HeroState* self)
{
  Mem_delete(self);
}

void HeroState_Reset(struct HeroState* self)
{
  double temp = self->fix;

  memset(self, 0, sizeof(struct HeroState));
  self->fix = temp;
}

int HeroState_GetCS(struct HeroState* self)
{
  return self->CSCount;
}

int HeroState_GetMZ(struct HeroState* self)
{
  return self->MZCount;
}

int HeroState_GetBJ(struct HeroState* self)
{
  return self->BJCount;
}

int HeroState_GetPJ(struct HeroState* self)
{
  return self->PJCount;
}

int HeroState_GetBP(struct HeroState* self)
{
  return self->BPCount;
}

int HeroState_GetAbilityCount(struct HeroState* self)
{
  return self->ARCount;
}

