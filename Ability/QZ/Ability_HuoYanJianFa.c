#include "../Ability_private.h"

int HuoYanJianFa_cost(struct Ability* self)
{
  return self->level * 13 + 54;
}

float HuoYanJianFa_damage(struct Ability* self, struct Hero* attacker, struct Hero* target)
{
  return damage_RollAttack(attacker) + (float)(self->level * 20 + 5);
}

char HuoYanJianFa_name[] =  ("火焰剑法");
struct Ability_Info abilityinfo_HuoYanJianFa =
{
  HuoYanJianFa_name,
  NULL,
  NULL,
  NULL,
  HuoYanJianFa_cost,
  NULL,
  NULL,
  HuoYanJianFa_damage,
  NULL,
  NULL,
  NULL,
  1,
};

void HuoYanJianFa_bind()
{
   Ability_bind(&abilityinfo_HuoYanJianFa);
}

