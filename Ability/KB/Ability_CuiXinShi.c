#include "../Ability_private.h"

int CuiXinShi_cost(struct Ability* self)
{
  return self->level * 2 + 41;
}

void CuiXinShi_add_buff_to_target(struct Ability* self, struct Hero* attacker, struct Hero* target)
{
  Hero_AddBuff(target, CuiXinShiBuff_Get(self->level));
}

float CuiXinShi_damage(struct Ability* self, struct Hero* attacker, struct Hero* target)
{
  return damage_RollAttack(attacker)*(float)((float)self->level*0.02 + 1.04);
}

char CuiXinShi_name[] =  ("摧心式");
struct Ability_Info abilityinfo_CuiXinShi =
{
  CuiXinShi_name,
  NULL,
  NULL,
  NULL,
  CuiXinShi_cost,
  NULL,
  NULL,
  CuiXinShi_damage,
  NULL,
  NULL,
  CuiXinShi_add_buff_to_target,
  1,
};

void CuiXinShi_bind()
{
   Ability_bind(&abilityinfo_CuiXinShi);
}
