#include "../Ability_private.h"

int BuYi_cost(struct Ability* self)
{
  return self->level * 7 + 71;
}

void BuYi_add_buff_to_attacker(struct Ability* self, struct Hero* attacker, struct Hero* target)
{
  Hero_AddBuff(attacker, BuYiBuff_Get(self->level));
}

void BuYi_before(struct Ability* self, struct Hero* attacker, struct Hero* target)
{
  Hero_Info(attacker)->attribMZ += self->master_data_1;
}

void BuYi_after(struct Ability* self, struct Hero* attacker, struct Hero* target)
{
  Hero_Info(attacker)->attribMZ -= self->master_data_1;
}

float BuYi_damage(struct Ability* self, struct Hero* attacker, struct Hero* target)
{
  return damage_RollAttack(attacker)*(float)(self->level * 0.02 + 1.06);
}

void BuYi_init(struct Ability* self, struct Hero* H)
{
  int addupA = 0, addupB = 0;

  self->master_data_1 = 0;

  // 精通境
  if (Hero_InfoEx(H)->def - 1700 > 0)
  {
    addupA = (Hero_InfoEx(H)->def - 1700) / 110 * 1;
  }

  if (Hero_InfoEx(H)->attribGG - 183 > 0)
  {
    addupB = (Hero_InfoEx(H)->attribGG - 183) / 8 * 1;
  }

  if (addupA > addupB)
  {
    self->master_data_1 = addupA;
  }
  else
  {
    self->master_data_1 = addupB;
  }

  if (self->master_data_1 > 23) self->master_data_1 = 23;
}

char BuYi_name[] =  ("补遗剑法");
struct Ability_Info abilityinfo_BuYi =
{
  BuYi_name,
  BuYi_init,
  NULL,
  NULL,
  BuYi_cost,
  NULL,
  BuYi_before,
  BuYi_damage,
  BuYi_after,
  BuYi_add_buff_to_attacker,
  NULL,
  1,
};

void BuYi_bind()
{
   Ability_bind(&abilityinfo_BuYi);
}
