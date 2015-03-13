#include "../Ability_private.h"

int HuBenBiFa_check(struct Ability* self, struct Hero* attacker)
{
  return (Hero_checkAbilityRandom(attacker, 30));
}

int HuBenBiFa_cost(struct Ability* self)
{
  return 80;
}

float HuBenBiFa_damage(struct Ability* self, struct Hero* attacker, struct Hero* target)
{
  return damage_RollAttack(attacker)*(float)(1.50);
}

char HuBenBiFa_name[] =  ("虎贲匕法");
struct Ability_Info abilityinfo_HuBenBiFa =
{
  HuBenBiFa_name,
  NULL,
  HuBenBiFa_check,
  NULL,
  HuBenBiFa_cost,
  NULL,
  NULL,
  HuBenBiFa_damage,
  NULL,
  NULL,
  NULL,
  1,
};

void HuBenBiFa_bind()
{
  Ability_bind(&abilityinfo_HuBenBiFa);
}

