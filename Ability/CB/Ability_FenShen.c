#include "../Ability_private.h"

int FenShen_cost(struct Ability* self)
{
  return self->level * 5 + 55;
}

float FenShen_damage(struct Ability* self, struct Hero* attacker, struct Hero* target)
{
  return damage_RollAttack(attacker)*(float)(1.0 - 0.62);
}

void FenShen_add_buff_to_attacker(struct Ability* self, struct Hero* attacker, struct Hero* target)
{
  Hero_AddBuff(attacker, FenShenBuff_Get(self->level));
}

char FenShen_name[] =  ("分身");
struct Ability_Info abilityinfo_FenShen =
{
  FenShen_name,
  NULL,
  NULL,
  NULL,
  FenShen_cost,
  NULL,
  NULL,
  FenShen_damage,
  NULL,
  FenShen_add_buff_to_attacker,
  NULL,
  3,
};

void FenShen_bind()
{
   Ability_bind(&abilityinfo_FenShen);
}
