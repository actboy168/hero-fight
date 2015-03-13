#include "../Ability_private.h"

int XuanYinJianQi_cost(struct Ability* self)
{
  return 60;
}

void XuanYinJianQi_before(struct Ability* self, struct Hero* attacker, struct Hero* target)
{
  Hero_Info(attacker)->attribMZ -= 20;
}
void XuanYinJianQi_after(struct Ability* self, struct Hero* attacker, struct Hero* target)
{
  Hero_Info(attacker)->attribMZ += 20;
}

float XuanYinJianQi_damage(struct Ability* self, struct Hero* attacker, struct Hero* target)
{
  return damage_RollAttack(attacker)*(float)(self->level * 0.05 + 1.95);
}

char XuanYinJianQi_name[] =  ("玄阴剑气");
struct Ability_Info abilityinfo_XuanYinJianQi =
{
  XuanYinJianQi_name,
  NULL,
  NULL,
  NULL,
  XuanYinJianQi_cost,
  NULL,
  XuanYinJianQi_before,
  XuanYinJianQi_damage,
  XuanYinJianQi_after,
  NULL,
  NULL,
  1,
};

void XuanYinJianQi_bind()
{
   Ability_bind(&abilityinfo_XuanYinJianQi);
}

