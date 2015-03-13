#include "../Ability_private.h"

int SouXin_cost(struct Ability* self)
{
  return self->level * 4 + 41;
}

float SouXin_damage(struct Ability* self, struct Hero* attacker, struct Hero* target)
{
  return damage_RollAttack(attacker)*(float)((float)((float)self->data_1+(float)self->master_data_1/(float)10.0)/(float)100.0 + 1.00);
}

void SouXin_init(struct Ability* self, struct Hero* H)
{
  self->master_data_1 = 0;

  // 精通境
  if (Hero_InfoEx(H)->attribSF - 292 > 0)
  {
    self->master_data_1 += (Hero_InfoEx(H)->attribSF - 292) / 9 * 2;
    if (self->master_data_1 > 30) self->master_data_1 = 30;
  }
}

char SouXin_name[] = ("搜心剑法");
struct Ability_Info abilityinfo_SouXin =
{
  SouXin_name,
  SouXin_init,
  NULL,
  NULL,
  SouXin_cost,
  NULL,
  NULL,
  SouXin_damage,
  NULL,
  NULL,
  NULL,
  2
};

void SouXin_bind()
{
   Ability_bind(&abilityinfo_SouXin);
}
