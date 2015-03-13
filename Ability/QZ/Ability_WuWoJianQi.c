#include "../Ability_private.h"

int WuWoJianQi_cost(struct Ability* self)
{
  return self->level * 56 + 301;
}

float WuWoJianQi_damage(struct Ability* self, struct Hero* attacker, struct Hero* target)
{
  return damage_RollAttack(attacker)*(float)(self->level * 0.08 + 1.60 + (float)self->master_data_1/(float)100.0);
}

void WuWoJianQi_init(struct Ability* self, struct Hero* H)
{
  self->master_data_1 = 0;

  // 精通境
  if (Hero_InfoEx(H)->maxMP - 5940 > 0)
  {
    self->master_data_1 += (Hero_InfoEx(H)->maxMP - 5940) / 137 * 1;
    if (self->master_data_1 > 107) self->master_data_1 = 107;
  }
}

char WuWoJianQi_name[] =  ("无我剑气");
struct Ability_Info abilityinfo_WuWoJianQi =
{
  WuWoJianQi_name,
  WuWoJianQi_init,
  NULL,
  NULL,
  WuWoJianQi_cost,
  NULL,
  NULL,
  WuWoJianQi_damage,
  NULL,
  NULL,
  NULL,
  1,
};

void WuWoJianQi_bind()
{
   Ability_bind(&abilityinfo_WuWoJianQi);
}

