#include "../Ability_private.h"

int LiuShuiJianFa_cost(struct Ability* self)
{
  return 60;
}

float LiuShuiJianFa_damage(struct Ability* self, struct Hero* attacker, struct Hero* target)
{
  return damage_RollAttack(attacker) + (float)(self->level * 3 + 9);
}

char LiuShuiJianFa_name[] =  ("流水剑法");
struct Ability_Info abilityinfo_LiuShuiJianFa =
{
  LiuShuiJianFa_name,
  NULL,
  NULL,
  NULL,
  LiuShuiJianFa_cost,
  NULL,
  NULL,
  LiuShuiJianFa_damage,
  NULL,
  NULL,
  NULL,
  1,
};

void LiuShuiJianFa_bind()
{
   Ability_bind(&abilityinfo_LiuShuiJianFa);
}

