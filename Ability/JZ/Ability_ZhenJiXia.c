#include "../Ability_private.h"

int ZhenJiXia_cost(struct Ability* self)
{
  return self->level * 10 + 100;
}

void ZhenJiXia_add_buff_to_attacker(struct Ability* self, struct Hero* attacker, struct Hero* target)
{
  Hero_AddBuff(attacker, ZhenJiXiaBuff_Get());
}

float ZhenJiXia_damage(struct Ability* self, struct Hero* attacker, struct Hero* target)
{
  return damage_RollAttack(attacker)*(float)((float)self->data_1/(float)100.0 + 1.00);
}

char ZhenJiXia_name[] =  ("真稷下剑法");
struct Ability_Info abilityinfo_ZhenJiXia =
{
  ZhenJiXia_name,
  NULL,
  NULL,
  NULL,
  ZhenJiXia_cost,
  NULL,
  NULL,
  ZhenJiXia_damage,
  NULL,
  ZhenJiXia_add_buff_to_attacker,
  NULL,
  1,
};

void ZhenJiXia_bind()
{
   Ability_bind(&abilityinfo_ZhenJiXia);
}
