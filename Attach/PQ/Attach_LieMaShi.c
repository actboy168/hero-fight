#include "../AttachAbility_private.h"

void LieMaShi_Attach(struct Hero* H,  int lv)
{
  Hero_SetAttachBuff(H, lv, LieMaShiBuff_Get);
}
