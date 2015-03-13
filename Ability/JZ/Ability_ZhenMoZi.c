#include "../Ability_private.h"

/*+---------------------------------------------
  |   min = lv+9
  |   max = (lv+9)*9
  |   f(x) = 1.1*x^4-1.1*x^3+0.73*x^2+0.27*x
  |
  |   +% ---> min+(max-min)*f(x)
 +---------------------------------------------*/
float ZhenMoZi_get_attackup(int level, struct Hero* attacker)
{
  double x = (double)Hero_Info(attacker)->HP/(double)Hero_Info(attacker)->maxHP;
  double y = (((1.1*x-1.1)*x+0.73)*x+0.27)*x;
  double min = (double)level*0.01 + 0.09;
  double max = (double)level*0.09 + 0.81;
  double attackup = 1.0+min+(max-min)*y;

  return (float)attackup;
}

int ZhenMoZi_cost(struct Ability* self)
{
  return self->level * 3 + 33;
}

float ZhenMoZi_damage(struct Ability* self, struct Hero* attacker, struct Hero* target)
{
  return damage_RollAttack(attacker)*ZhenMoZi_get_attackup(self->level, attacker);
}

char ZhenMoZi_name[] = ("真墨子剑法");
struct Ability_Info abilityinfo_ZhenMoZi =
{
  ZhenMoZi_name,
  NULL,
  NULL,
  NULL,
  ZhenMoZi_cost,
  NULL,
  NULL,
  ZhenMoZi_damage,
  NULL,
  NULL,
  NULL,
  1,
};

void ZhenMoZi_bind()
{
   Ability_bind(&abilityinfo_ZhenMoZi);
}

