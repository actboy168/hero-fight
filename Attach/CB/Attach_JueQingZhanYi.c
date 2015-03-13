#include "../AttachAbility_private.h"

void JueQingZhanYi_Attach(struct Hero* H, int lv)
{
  Hero_InfoEx(H)->attribBS += lv*5;
  Hero_Info(H)->attribBS = Hero_InfoEx(H)->attribBS;
}

