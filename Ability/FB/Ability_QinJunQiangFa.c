#include "../Ability_private.h"

int QinJunQiangFa_check(struct Ability* self, struct Hero* attacker)
{
  return (Hero_checkAbilityRandom(attacker, 30));
}

int QinJunQiangFa_cost(struct Ability* self)
{
  return 135;
}

float QinJunQiangFa_damage(struct Ability* self, struct Hero* attacker, struct Hero* target)
{
  return damage_RollAttack(attacker)*(float)(1.50);
}


char QinJunQiangFa_name[] =  ("秦军枪法");
struct Ability_Info abilityinfo_QinJunQiangFa =
{
  QinJunQiangFa_name,
  NULL,
  QinJunQiangFa_check,
  NULL,
  QinJunQiangFa_cost,
  NULL,
  NULL,
  QinJunQiangFa_damage,
  NULL,
  NULL,
  NULL,
  1,
};

void QinJunQiangFa_bind()
{
   Ability_bind(&abilityinfo_QinJunQiangFa);
}

