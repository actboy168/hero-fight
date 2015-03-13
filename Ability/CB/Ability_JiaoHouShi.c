#include "../Ability_private.h"

int JiaoHouShi_cost(struct Ability* self)
{
  return self->level * 2 + 26;
}

void JiaoHouShi_add_buff_to_target(struct Ability* self, struct Hero* attacker, struct Hero* target)
{
  Hero_AddBuff(target, JiaoHouShiBuff_Get(self->level));
}

char JiaoHouShi_name[] = ("绞喉式");
struct Ability_Info abilityinfo_JiaoHouShi =
{
  JiaoHouShi_name,
  NULL,
  NULL,
  NULL,
  JiaoHouShi_cost,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  JiaoHouShi_add_buff_to_target,
  1,
};

void JiaoHouShi_bind()
{
   Ability_bind(&abilityinfo_JiaoHouShi);
}
