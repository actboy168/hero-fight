#include "../Ability_private.h"

int PoJiaShi_cost(struct Ability* self)
{
  return self->level * 5 + 53;
}

void PoJiaShi_add_buff_to_target(struct Ability* self, struct Hero* attacker, struct Hero* target)
{
  Hero_AddBuff(target, PoJiaShiBuff_Get(self->level));
}

float PoJiaShi_damage(struct Ability* self, struct Hero* attacker, struct Hero* target)
{
  return damage_RollAttack(attacker)*(float)((float)self->level*0.01 + 1.25);
}

char PoJiaShi_name[] =  ("破甲式");
struct Ability_Info abilityinfo_PoJiaShi =
{
  PoJiaShi_name,
  NULL,
  NULL,
  NULL,
  PoJiaShi_cost,
  NULL,
  NULL,
  PoJiaShi_damage,
  NULL,
  NULL,
  PoJiaShi_add_buff_to_target,
  1,
};

void PoJiaShi_bind()
{
   Ability_bind(&abilityinfo_PoJiaShi);
}
