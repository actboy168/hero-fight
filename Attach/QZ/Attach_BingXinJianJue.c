#include "../AttachAbility_private.h"

void BingXinJianJue_Attach(struct Hero* H,  int lv)
{
  Hero_InfoEx(H)->attribBX += lv*3;
  Hero_Info(H)->attribBX = Hero_InfoEx(H)->attribBX;

  // 精通境
  if (Hero_InfoEx(H)->maxMP - 5940 > 0)
  {
    int addup = (Hero_InfoEx(H)->maxMP - 5940) / 4 * 16;
    if (addup > 580) addup = 580;

    Hero_InfoEx(H)->def += addup;
    Hero_Info(H)->def = Hero_InfoEx(H)->def;
  }
}

