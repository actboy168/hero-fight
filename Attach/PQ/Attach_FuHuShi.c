#include "../AttachAbility_private.h"

void FuHuShi_Attach(struct Hero* H,  int lv)
{
  Hero_SetAttachBuff(H, lv, FuHuShiBuff_Get);
}
