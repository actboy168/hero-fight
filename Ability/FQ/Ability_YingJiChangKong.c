#include "../Ability_private.h"

int YingJiChangKong_cost(struct Ability* self)
{
  return self->level * 10 + 160;
}

void YingJiChangKong_add_buff_to_target(struct Ability* self, struct Hero* attacker, struct Hero* target)
{
  Hero_AddBuff(target, YingJiChangKongBuff_Get(self->level));
}

float YingJiChangKong_damage(struct Ability* self, struct Hero* attacker, struct Hero* target)
{
  return damage_RollAttack(attacker)*(float)((float)self->level*0.02 + 1.02);
}

char YingJiChangKong_name[] = ("鹰击长空");
struct Ability_Info abilityinfo_YingJiChangKong =
{
  YingJiChangKong_name,
  NULL,
  NULL,
  NULL,
  YingJiChangKong_cost,
  NULL,
  NULL,
  YingJiChangKong_damage,
  NULL,
  NULL,
  YingJiChangKong_add_buff_to_target,
  1,
};

void YingJiChangKong_bind()
{
   Ability_bind(&abilityinfo_YingJiChangKong);
}
