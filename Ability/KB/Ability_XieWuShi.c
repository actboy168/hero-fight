#include "../Ability_private.h"

int XieWuShi_cost(struct Ability* self)
{
  return self->level * 5 + 70;
}

void XieWuShi_add_buff_to_target(struct Ability* self, struct Hero* attacker, struct Hero* target)
{
  Hero_AddBuff(target, XieWuShiBuff_Get(self->level));
}

void XieWuShi_before(struct Ability* self, struct Hero* attacker, struct Hero* target)
{
  Hero_Info(attacker)->attribMZ += self->master_data_1;
}

void XieWuShi_after(struct Ability* self, struct Hero* attacker, struct Hero* target)
{
  Hero_Info(attacker)->attribMZ -= self->master_data_1;
}

float XieWuShi_damage(struct Ability* self, struct Hero* attacker, struct Hero* target)
{
  return damage_RollAttack(attacker)*(float)((float)self->level*0.01 + 1.08);
}

void XieWuShi_init(struct Ability* self, struct Hero* H)
{
  self->master_data_1 = 0;

  // 精通境
  if (Hero_InfoEx(H)->attribGG - 172 > 0)
  {
    self->master_data_1 += (Hero_InfoEx(H)->attribGG - 172) / 27 * 1;
    if (self->master_data_1 > 8) self->master_data_1 = 8;
  }
}

char XieWuShi_name[] =  ("卸武式");
struct Ability_Info abilityinfo_XieWuShi =
{
  XieWuShi_name,
  XieWuShi_init,
  NULL,
  NULL,
  XieWuShi_cost,
  NULL,
  XieWuShi_before,
  XieWuShi_damage,
  XieWuShi_after,
  NULL,
  XieWuShi_add_buff_to_target,
  1,
};

void XieWuShi_bind()
{
   Ability_bind(&abilityinfo_XieWuShi);
}
