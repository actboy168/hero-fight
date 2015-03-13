#include "../Buff_private.h"
#include "../BuffList.h"

void CanHongYuJin_Buff_Start(struct Buff* self, struct BuffList* list);
void CanHongYuJin_Buff_Stop(struct Buff* self, struct BuffList* list);

const char CanHongYuJin_startStr[] = ("%s双目尽赤，血脉喷张，体内的鲜血仿佛被点燃般，皮肤散发着阵阵恐怖的红光！");
const char CanHongYuJin_stopStr[] = ("%s双目逐渐恢复正常，血红的气焰慢慢消散！");

struct Buff CanHongYuJinInfo =
{
  CanHongYuJin_ID,
  BUFF_TYPE_TURN,
  1.0,
  CanHongYuJin_Buff_Start,
  CanHongYuJin_Buff_Stop,
  CanHongYuJin_startStr,
  CanHongYuJin_stopStr
};

/*+---------------------------------------------
  |   f(x) = 1.1*x^4-1.1*x^3+0.73*x^2+0.27*x
  |
  |   +% ---> min+(max-min)*f(1-x)
 +---------------------------------------------*/
int CanHongYuJin_get_attackup(int min, int max, struct HeroInfo* attacker)
{
  double x = 1-(double)attacker->HP/(double)attacker->maxHP;
  double y = (((1.1*x-1.1)*x+0.73)*x+0.27)*x;
  int attackup = (int)(min+(max-min)*y);

  return attackup;
}

void CanHongYuJin_Buff_Set(struct BuffList* list)
{
  if(BuffList_HaveBuff(list, CanHongYuJin_ID))
  {
    struct Buff* buff = BuffList_GetBuff(list, CanHongYuJin_ID);
    buff->data_4 = CanHongYuJin_get_attackup(buff->data_1, buff->data_2, list->current);
    BuffList_Apply_Attack(list, buff->data_4, 0);
  }
}

void CanHongYuJin_Buff_Start(struct Buff* self, struct BuffList* list)
{
  self->data_4 = CanHongYuJin_get_attackup(self->data_1, self->data_2, list->current);

  BuffList_Apply_Attack(list, self->data_4, 0);
  list->current->attribMZ += self->data_3;
}

void CanHongYuJin_Buff_Stop(struct Buff* self, struct BuffList* list)
{
  BuffList_Apply_Attack(list, -self->data_4, 0);
  list->current->attribMZ -= self->data_3;
}

struct Buff* CanHongYuJinBuff_Get(int min, int max, unsigned int mz)
{
  CanHongYuJinInfo.data_1 = min;
  CanHongYuJinInfo.data_2 = max;
  CanHongYuJinInfo.data_3 = mz;

  return &CanHongYuJinInfo;
}
