#include "../AttachAbility_private.h"

void HunYuanShi_Attach(struct Hero* H,  int lv)
{
  Hero_InfoEx(H)->attribKX += lv*5;
  Hero_Info(H)->attribKX = Hero_InfoEx(H)->attribKX;
}

