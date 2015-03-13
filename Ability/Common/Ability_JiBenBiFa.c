#include "../Ability_private.h"

int JiBenBiFa_cost(struct Ability* self)
{
  return self->level + 23;
}

float JiBenBiFa_damage(struct Ability* self, struct Hero* attacker, struct Hero* target)
{
  return damage_RollAttack(attacker) + (float)self->level;
}

char JiBenBiFa_name[] =  ("基本匕法");
struct Ability_Info abilityinfo_JiBenBiFa =
{
  JiBenBiFa_name,
  NULL,
  NULL,
  NULL,
  JiBenBiFa_cost,
  NULL,
  NULL,
  JiBenBiFa_damage,
  NULL,
  NULL,
  NULL,
  1,
};

void JiBenBiFa_bind()
{
   Ability_bind(&abilityinfo_JiBenBiFa);
}

