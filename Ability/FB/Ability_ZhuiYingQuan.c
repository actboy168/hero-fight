#include "../Ability_private.h"

void ZhuiYingQuan_add_buff_to_attacker(struct Ability* self, struct Hero* attacker, struct Hero* target)
{
  Hero_AddBuff(attacker, ZhuiYingQuanBuff_Get(self->level));
}

char ZhuiYingQuan_name[] = ("追影拳");
struct Ability_Info abilityinfo_ZhuiYingQuan =
{
  ZhuiYingQuan_name,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  ZhuiYingQuan_add_buff_to_attacker,
  NULL,
  1,
};

void ZhuiYingQuan_bind()
{
   Ability_bind(&abilityinfo_ZhuiYingQuan);
}

