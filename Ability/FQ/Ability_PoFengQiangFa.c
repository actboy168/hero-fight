#include "../Ability_private.h"

int PoFengQiangFa_cost(struct Ability* self)
{
  return self->level * 3 + 35;
}

void PoFengQiangFa_add_buff_to_attacker(struct Ability* self, struct Hero* attacker, struct Hero* target)
{
  if (self->master_data_1 > 0)
  {
    Hero_AddBuff(attacker, PoFengQiangFaBuff_Get(self->master_data_1));
  }
}

float PoFengQiangFa_damage(struct Ability* self, struct Hero* attacker, struct Hero* target)
{
  return (damage_RollAttack(attacker) + (float)(self->level * 2 + 13))*(float)((float)self->level * 0.005 + 0.55);
}

void PoFengQiangFa_init(struct Ability* self, struct Hero* H)
{
  self->master_data_1 = 0;

  // 精通境
  if (fabs(Hero_InfoEx(H)->speed - 20.0) > 0.0005)
  {
    // 只对防枪有效
    return;
  }

  if (Hero_InfoEx(H)->attribBL - 148 > 0)
  {
    self->master_data_1 += (Hero_InfoEx(H)->attribBL - 148) / 4 * 1;
    if (self->master_data_1 > 64) self->master_data_1 = 64;
  }
}

char PoFengQiangFa_name[] = ("破风枪法");
struct Ability_Info abilityinfo_PoFengQiangFa =
{
  PoFengQiangFa_name,
  PoFengQiangFa_init,
  NULL,
  NULL,
  PoFengQiangFa_cost,
  NULL,
  NULL,
  PoFengQiangFa_damage,
  NULL,
  PoFengQiangFa_add_buff_to_attacker,
  NULL,
  2,
};

void PoFengQiangFa_bind()
{
   Ability_bind(&abilityinfo_PoFengQiangFa);
}
