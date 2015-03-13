#include "../Ability_private.h"

int JiXiaJianFa_cost(struct Ability* self)
{
  return self->level * 2 + 30;
}

float JiXiaJianFa_damage(struct Ability* self, struct Hero* attacker, struct Hero* target)
{
  return damage_RollAttack(attacker) + (float)self->data_1;
}

char JiXiaJianFa_name[] = ("稷下剑法");
struct Ability_Info abilityinfo_JiXiaJianFa =
{
  JiXiaJianFa_name,
  NULL,
  NULL,
  NULL,
  JiXiaJianFa_cost,
  NULL,
  NULL,
  JiXiaJianFa_damage,
  NULL,
  NULL,
  NULL,
  1
};

void JiXiaJianFa_bind()
{
   Ability_bind(&abilityinfo_JiXiaJianFa);
}
