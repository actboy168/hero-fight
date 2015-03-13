#include "../Ability_private.h"

int MoZiJianFa_cost(struct Ability* self)
{
  return self->level * 2 + 30;
}

float MoZiJianFa_damage(struct Ability* self, struct Hero* attacker, struct Hero* target)
{
  return damage_RollAttack(attacker) + (float)self->data_1;
}

char MoZiJianFa_name[] = ("墨子剑法");
struct Ability_Info abilityinfo_MoZiJianFa =
{
  MoZiJianFa_name,
  NULL,
  NULL,
  NULL,
  MoZiJianFa_cost,
  NULL,
  NULL,
  MoZiJianFa_damage,
  NULL,
  NULL,
  NULL,
  1
};

void MoZiJianFa_bind()
{
   Ability_bind(&abilityinfo_MoZiJianFa);
}
