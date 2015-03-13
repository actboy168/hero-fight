#include "../Ability_private.h"

int ShiPo_cost(struct Ability* self)
{
  return self->level * 4 + 41;
}

float ShiPo_damage(struct Ability* self, struct Hero* attacker, struct Hero* target)
{
  return damage_RollAttack(attacker)*(float)(self->level * 0.04 + 1.24);
}

char ShiPo_name[] =  ("噬魄");
struct Ability_Info abilityinfo_ShiPo =
{
  ShiPo_name,
  NULL,
  NULL,
  NULL,
  ShiPo_cost,
  NULL,
  NULL,
  ShiPo_damage,
  NULL,
  NULL,
  NULL,
  1,
};

void ShiPo_bind()
{
  // 无视冰心
  Ability_set_antiBX(&abilityinfo_ShiPo);
  Ability_bind(&abilityinfo_ShiPo);
}

