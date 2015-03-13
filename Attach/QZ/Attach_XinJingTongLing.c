#include "../AttachAbility_private.h"

void XinJingTongLing_Attach(struct Hero* H,  int lv)
{
  Hero_InfoEx(H)->attribXJ += lv*4;
  Hero_Info(H)->attribXJ = Hero_InfoEx(H)->attribXJ;
}
