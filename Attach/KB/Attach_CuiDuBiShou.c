#include "../AttachAbility_private.h"

void CuiDuBiShou_Attach(struct Hero* H,  int lv)
{
  Hero_SetAttachBuff(H, lv, CuiDuBiShouBuff_Get);
}

