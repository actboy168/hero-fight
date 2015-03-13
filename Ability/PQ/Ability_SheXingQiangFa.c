#include "../Ability_private.h"

int SheXingQiangFa_check(struct Ability* self, struct Hero* attacker)
{
  return (Hero_Info(attacker)->HP >= (self->level + 5));
}

void SheXingQiangFa_pay(struct Ability* self, struct Hero* attacker, struct Hero* target)
{
  Hero_Info(attacker)->HP -= (self->level + 5);
}

float SheXingQiangFa_damage(struct Ability* self, struct Hero* attacker, struct Hero* target)
{
  return damage_RollAttack(attacker) + (float)(self->level * 6 + 24);
}

char SheXingQiangFa_name[] =  ("蛇形枪法");
struct Ability_Info abilityinfo_SheXingQiangFa =
{
  SheXingQiangFa_name,
  NULL,
  SheXingQiangFa_check,
  SheXingQiangFa_pay,
  NULL,
  NULL,
  NULL,
  SheXingQiangFa_damage,
  NULL,
  NULL,
  NULL,
  1,
};

void SheXingQiangFa_bind()
{
   Ability_bind(&abilityinfo_SheXingQiangFa);
}
