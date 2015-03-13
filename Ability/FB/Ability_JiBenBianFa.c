#include "../Ability_private.h"

int JiBenBianFa_cost(struct Ability* self)
{
  return 0;
}

void JiBenBianFa_add_buff_to_attacker(struct Ability* self, struct Hero* attacker, struct Hero* target)
{
  Hero_AddBuff(attacker, JiBenBianFaBuff_Get(99));
}

float JiBenBianFa_damage(struct Ability* self, struct Hero* attacker, struct Hero* target)
{
  return (damage_RollAttack(attacker)+(float)102.0)*1.74;
}

char JiBenBianFa_name[] =  ("基本鞭法");
struct Ability_Info abilityinfo_JiBenBianFa =
{
  JiBenBianFa_name,
  NULL,
  NULL,
  NULL,
  JiBenBianFa_cost,
  NULL,
  NULL,
  JiBenBianFa_damage,
  NULL,
  JiBenBianFa_add_buff_to_attacker,
  NULL,
  1,
};

void JiBenBianFa_bind()
{
   Ability_bind(&abilityinfo_JiBenBianFa);
}
