#include "../Ability_private.h"

int XiuWuDuanHun_check(struct Ability* self, struct Hero* attacker)
{
  return (Hero_checkAbilityRandom(attacker, 20));
}

int XiuWuDuanHun_cost(struct Ability* self)
{
  return 80;
}

void XiuWuDuanHun_add_buff_to_target(struct Ability* self, struct Hero* attacker, struct Hero* target)
{
  Hero_AddBuff(target, XiuWuDuanHunBuff_Get(self->level));
}

char XiuWuDuanHun_name[] =  ("袖舞断魂");
struct Ability_Info abilityinfo_XiuWuDuanHun =
{
  XiuWuDuanHun_name,
  NULL,
  XiuWuDuanHun_check,
  NULL,
  XiuWuDuanHun_cost,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  XiuWuDuanHun_add_buff_to_target,
  1,
};

void XiuWuDuanHun_bind()
{
   Ability_bind(&abilityinfo_XiuWuDuanHun);
}
