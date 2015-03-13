#include "../Ability_private.h"

int WuLaiGunFa_cost(struct Ability* self)
{
  return 80;
}

void WuLaiGunFa_add_buff_to_target(struct Ability* self, struct Hero* attacker, struct Hero* target)
{
  Hero_AddBuff(target, WuLaiGunFaBuff_Get(self->level));
}

char WuLaiGunFa_name[] =  ("无赖棍法");
struct Ability_Info abilityinfo_WuLaiGunFa =
{
  WuLaiGunFa_name,
  NULL,
  NULL,
  NULL,
  WuLaiGunFa_cost,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  WuLaiGunFa_add_buff_to_target,
  1,
};

void WuLaiGunFa_bind()
{
   Ability_bind(&abilityinfo_WuLaiGunFa);
}
