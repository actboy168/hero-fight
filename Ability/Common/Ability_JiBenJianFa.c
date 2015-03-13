#include "../Ability_private.h"

int JiBenJianFa_cost(struct Ability* self)
{
  return self->level*2 + 28;
}

float JiBenJianFa_damage(struct Ability* self, struct Hero* attacker, struct Hero* target)
{
  return damage_RollAttack(attacker) + (float)(self->level + 2);
}

char JiBenJianFa_name[] =  ("基本剑法");
struct Ability_Info abilityinfo_JiBenJianFa =
{
  JiBenJianFa_name,
  NULL,
  NULL,
  NULL,
  JiBenJianFa_cost,
  NULL,
  NULL,
  JiBenJianFa_damage,
  NULL,
  NULL,
  NULL,
  1,
};

void JiBenJianFa_bind()
{
   Ability_bind(&abilityinfo_JiBenJianFa);
}

