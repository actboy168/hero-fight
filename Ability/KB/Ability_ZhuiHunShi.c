#include "../Ability_private.h"

int ZhuiHunShi_cost(struct Ability* self)
{
  return self->level * 2 + 26;
}

void ZhuiHunShi_add_buff_to_target(struct Ability* self, struct Hero* attacker, struct Hero* target)
{
  Hero_AddBuff(target, ZhuiHunShiBuff_Get(self->level));
}

char ZhuiHunShi_name[] =  ("追魂式");
struct Ability_Info abilityinfo_ZhuiHunShi =
{
  ZhuiHunShi_name,
  NULL,
  NULL,
  NULL,
  ZhuiHunShi_cost,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  ZhuiHunShi_add_buff_to_target,
  1,
};

void ZhuiHunShi_bind()
{
   Ability_bind(&abilityinfo_ZhuiHunShi);
}
