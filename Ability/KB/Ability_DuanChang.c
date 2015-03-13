#include "../Ability_private.h"

int DuanChang_cost(struct Ability* self)
{
  return self->level * 8 + 82;
}

void DuanChang_add_buff_to_target(struct Ability* self, struct Hero* attacker, struct Hero* target)
{
  Hero_AddBuff(target, DuanChangBuff_Get(self->level));
}

char DuanChang_name[] = ("断肠");
struct Ability_Info abilityinfo_DuanChang =
{
  DuanChang_name,
  NULL,
  NULL,
  NULL,
  DuanChang_cost,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  DuanChang_add_buff_to_target,
  1,
};

void DuanChang_bind()
{
   Ability_bind(&abilityinfo_DuanChang);
}
