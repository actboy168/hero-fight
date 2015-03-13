#include "../Ability_private.h"


int CanHongYuJin_cost(struct Ability* self)
{
  return self->level * 12 + 48;
}

void CanHongYuJin_add_buff_to_attacker(struct Ability* self, struct Hero* attacker, struct Hero* target)
{
  int min = (self->level+1)/2 +  1 + self->master_data_1;
  int max =  self->level * 18 + 60 + self->master_data_1;

  Hero_AddBuff(attacker, CanHongYuJinBuff_Get(min, max, self->master_data_2));
}

void CanHongYuJin_init(struct Ability* self, struct Hero* H)
{
  self->master_data_1 = 0;
  self->master_data_2 = 0;

  // 精通境
  if (Hero_InfoEx(H)->attribBL - 190 > 0)
  {
    self->master_data_1 += (Hero_InfoEx(H)->attribBL - 190) / 7 * 1;
    if (self->master_data_1 > 37) self->master_data_1 = 37;

    self->master_data_2 += (Hero_InfoEx(H)->attribBL - 190) / 37 * 1;
    if (self->master_data_2 > 7) self->master_data_2 = 7;
  }
}

char CanHongYuJin_name[] = ("残红欲尽");
struct Ability_Info abilityinfo_CanHongYuJin =
{
  CanHongYuJin_name,
  CanHongYuJin_init,
  NULL,
  NULL,
  CanHongYuJin_cost,
  NULL,
  NULL,
  NULL,
  NULL,
  CanHongYuJin_add_buff_to_attacker,
  NULL,
  1,
};

void CanHongYuJin_bind()
{
   Ability_bind(&abilityinfo_CanHongYuJin);
}

