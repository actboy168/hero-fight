#include "../Ability_private.h"

#include "../../Core/miniCRT.h"

int WuMing_check(struct Ability* self, struct Hero* attacker)
{
  return (Hero_Info(attacker)->HP >= Crt_GetRoundUp(Hero_Info(attacker)->maxHP * 0.05));
}

void WuMing_pay(struct Ability* self, struct Hero* attacker, struct Hero* target)
{
  Hero_Info(attacker)->HP -= Crt_GetRoundUp(Hero_Info(attacker)->maxHP * 0.05);
}

void WuMing_before(struct Ability* self, struct Hero* attacker, struct Hero* target)
{
  Hero_Info(attacker)->attribMZ += 5 + self->master_data_1;
}

void WuMing_after(struct Ability* self, struct Hero* attacker, struct Hero* target)
{
  Hero_Info(attacker)->attribMZ -= 5 + self->master_data_1;
}

float WuMing_damage(struct Ability* self, struct Hero* attacker, struct Hero* target)
{
  return damage_RollAttack(attacker)*(float)(self->level * 0.05 + 1.75);
}

void WuMing_init(struct Ability* self, struct Hero* H)
{
  self->master_data_1 = 0;

  // 精通境
  if (Hero_InfoEx(H)->attribGG - 172 > 0)
  {
    self->master_data_1 += (Hero_InfoEx(H)->attribGG - 172) / 33 * 1;
    if (self->master_data_1 > 5) self->master_data_1 = 5;
  }
}

char WuMing_name[] =  ("无命");
struct Ability_Info abilityinfo_WuMing =
{
  WuMing_name,
  WuMing_init,
  WuMing_check,
  WuMing_pay,
  NULL,
  NULL,
  WuMing_before,
  WuMing_damage,
  WuMing_after,
  NULL,
  NULL,
  1,
};

void WuMing_bind()
{
   Ability_bind(&abilityinfo_WuMing);
}
