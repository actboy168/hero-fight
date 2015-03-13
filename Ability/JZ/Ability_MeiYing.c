#include "../Ability_private.h"

int MeiYing_cost(struct Ability* self)
{
  return self->level * 5 + 50;
}

void MeiYing_add_buff_to_target(struct Ability* self, struct Hero* attacker, struct Hero* target)
{
  Hero_AddBuff(target, MeiYingBuff_Get(self->level, self->data_1));
}

char MeiYing_name[] =  ("魅影剑法");
struct Ability_Info abilityinfo_MeiYing =
{
  MeiYing_name,
  NULL,
  NULL,
  NULL,
  MeiYing_cost,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  MeiYing_add_buff_to_target,
  1,
};

void MeiYing_bind()
{
   Ability_bind(&abilityinfo_MeiYing);
}
