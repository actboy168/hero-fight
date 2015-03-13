#include "../Ability_private.h"

int ZhuiYingShi_cost(struct Ability* self)
{
  return self->level + 22;
}

void ZhuiYingShi_add_buff_to_attacker(struct Ability* self, struct Hero* attacker, struct Hero* target)
{
  Hero_AddBuff(attacker, ZhuiYingShiBuff_Get(12 + self->level + self->master_data_1));
}

void ZhuiYingShi_init(struct Ability* self, struct Hero* H)
{
  self->master_data_1 = 0;

  // 精通境
  if (Hero_InfoEx(H)->attribSF - 220 > 0)
  {
    self->master_data_1 += (Hero_InfoEx(H)->attribSF - 220) / 6 * 1;
    if (self->master_data_1 > 96) self->master_data_1 = 96;
  }
}

char ZhuiYingShi_name[] =  ("追影式");
struct Ability_Info abilityinfo_ZhuiYingShi =
{
  ZhuiYingShi_name,
  ZhuiYingShi_init,
  NULL,
  NULL,
  ZhuiYingShi_cost,
  NULL,
  NULL,
  NULL,
  NULL,
  ZhuiYingShi_add_buff_to_attacker,
  NULL,
  1,
};

void ZhuiYingShi_bind()
{
   Ability_bind(&abilityinfo_ZhuiYingShi);
}
