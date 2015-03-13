#include "../Ability_private.h"

int JiBenQiangFa_cost(struct Ability* self)
{
  return self->level*3 + 37;
}

float JiBenQiangFa_damage(struct Ability* self, struct Hero* attacker, struct Hero* target)
{
  return damage_RollAttack(attacker) + (float)(self->level*2 + 2);
}

char JiBenQiangFa_name[] =  ("基本枪法");
struct Ability_Info abilityinfo_JiBenQiangFa =
{
  JiBenQiangFa_name,
  NULL,
  NULL,
  NULL,
  JiBenQiangFa_cost,
  NULL,
  NULL,
  JiBenQiangFa_damage,
  NULL,
  NULL,
  NULL,
  1,
};

void JiBenQiangFa_bind()
{
   Ability_bind(&abilityinfo_JiBenQiangFa);
}

