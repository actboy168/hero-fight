#include "../Ability_private.h"

int ZhongXieJianFa_cost(struct Ability* self)
{
  return self->level * 7 + 68;
}

char ZhongXieJianFa_name[] = ("中邪剑法");
struct Ability_Info abilityinfo_ZhongXieJianFa =
{
  ZhongXieJianFa_name,
  NULL,
  NULL,
  NULL,
  ZhongXieJianFa_cost,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  2
};

void ZhongXieJianFa_bind()
{
   Ability_bind(&abilityinfo_ZhongXieJianFa);
}
