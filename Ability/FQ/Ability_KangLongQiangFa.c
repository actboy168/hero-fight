#include "../Ability_private.h"

int KangLongQiangFa_cost(struct Ability* self)
{
  return self->level * 7 + 63;
}

void KangLongQiangFa_add_buff_to_attacker(struct Ability* self, struct Hero* attacker, struct Hero* target)
{
  Hero_AddBuff(attacker, KangLongQiangFaBuff_Get(self->level));
}

char KangLongQiangFa_name[] = ("亢龙枪法");
struct Ability_Info abilityinfo_KangLongQiangFa =
{
  KangLongQiangFa_name,
  NULL,
  NULL,
  NULL,
  KangLongQiangFa_cost,
  NULL,
  NULL,
  NULL,
  NULL,
  KangLongQiangFa_add_buff_to_attacker,
  NULL,
  1,
};

void KangLongQiangFa_bind()
{
   Ability_bind(&abilityinfo_KangLongQiangFa);
}
