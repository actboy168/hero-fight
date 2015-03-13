#include "../Ability_private.h"

int HuiMaQiang_cost(struct Ability* self)
{
  return self->level * 18 + 161;
}

int HuiMaQiang_check(struct Ability* self, struct Hero* attacker)
{
  return (!Hero_HaveBuff(attacker, HuiMaQiangA_GetID()) && (Hero_Info(attacker)->MP >= Ability_GetRealCost(self, attacker)));
}

void HuiMaQiang_add_buff_to_attacker(struct Ability* self, struct Hero* attacker, struct Hero* target)
{
  Hero_AddBuff(attacker, HuiMaQiangABuff_Get(self->level));
  Hero_AddBuff(attacker, HuiMaQiangBBuff_Get(self->level));
}

float HuiMaQiang_damage(struct Ability* self, struct Hero* attacker, struct Hero* target)
{
  return 0;
}

char HuiMaQiang_name[] = ("回马枪");
struct Ability_Info abilityinfo_HuiMaQiang =
{
  HuiMaQiang_name,
  NULL,
  HuiMaQiang_check,
  NULL,
  HuiMaQiang_cost,
  NULL,
  NULL,
  HuiMaQiang_damage,
  NULL,
  HuiMaQiang_add_buff_to_attacker,
  NULL,
  1,
};

void HuiMaQiang_bind()
{
   Ability_bind(&abilityinfo_HuiMaQiang);
}
