#include "../Ability_private.h"

int NuJiaoQiangFa_cost(struct Ability* self)
{
  return self->level * 7 + 67;
}

float NuJiaoQiangFa_damage(struct Ability* self, struct Hero* attacker, struct Hero* target)
{
  return damage_RollAttack(attacker)  + (float)(self->level * 10 + self->master_data_1);
}

void NuJiaoQiangFa_init(struct Ability* self, struct Hero* H)
{
  self->master_data_1 = 0;

  // 精通境
  if (Hero_InfoEx(H)->def - 2200 > 0)
  {
    self->master_data_1 += (Hero_InfoEx(H)->def - 2200) / 8 * 1;
    if (self->master_data_1 > 267) self->master_data_1 = 267;
  }
}

char NuJiaoQiangFa_name[] = ("怒蛟枪法");
struct Ability_Info abilityinfo_NuJiaoQiangFa =
{
  NuJiaoQiangFa_name,
  NuJiaoQiangFa_init,
  NULL,
  NULL,
  NuJiaoQiangFa_cost,
  NULL,
  NULL,
  NuJiaoQiangFa_damage,
  NULL,
  NULL,
  NULL,
  1,
};

void NuJiaoQiangFa_bind()
{
   Ability_bind(&abilityinfo_NuJiaoQiangFa);
}
