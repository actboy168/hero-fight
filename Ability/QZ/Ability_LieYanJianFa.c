#include "../Ability_private.h"

int LieYanJianFa_cost(struct Ability* self)
{
  return self->level * 41 + 213;
}

void LieYanJianFa_add_buff_to_target(struct Ability* self, struct Hero* attacker, struct Hero* target)
{
  Hero_AddBuff(target, LieYanJianFaBuff_Get(self->level));
}

float LieYanJianFa_damage(struct Ability* self, struct Hero* attacker, struct Hero* target)
{
  return damage_RollAttack(attacker)*(float)((float)self->level*0.04 + 1.10);
}

char LieYanJianFa_name[] = ("烈焰剑法");
struct Ability_Info abilityinfo_LieYanJianFa =
{
  LieYanJianFa_name,
  NULL,
  NULL,
  NULL,
  LieYanJianFa_cost,
  NULL,
  NULL,
  LieYanJianFa_damage,
  NULL,
  NULL,
  LieYanJianFa_add_buff_to_target,
  1,
};

void LieYanJianFa_bind()
{
   Ability_bind(&abilityinfo_LieYanJianFa);
}
