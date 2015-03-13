#include "../AttachAbility_private.h"

void FenXinJianYi_Attach(struct Hero* H,  int lv)
{
  Hero_InfoEx(H)->attribNZ += lv*5;
  Hero_Info(H)->attribNZ = Hero_InfoEx(H)->attribNZ;

  // 精通境
  if (Hero_InfoEx(H)->attribGG - 269 > 0)
  {
    int addup = (Hero_InfoEx(H)->attribGG - 269) / 15 * 1;
    if (addup > 15) addup = 15;

    Hero_InfoEx(H)->def += addup;
    Hero_Info(H)->attribMZ = Hero_InfoEx(H)->attribMZ;
  }
}
