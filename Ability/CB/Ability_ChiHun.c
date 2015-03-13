#include "../Ability_private.h"

/*+---------------------------------------------
  |   Lv attackup
  | >=18 17+Lv*4
  | ==17 86
  | >=12 18+Lv*4
  | <=11 30+Lv*3
 +---------------------------------------------*/
float ChiHun_get_attackup(int level)
{
  if (level >= 18)
    return (float)(1.17+(float)level*0.04);
  else if (level == 17)
    return (float)(1.86);
  else if (level >= 12)
    return (float)(1.18+(float)level*0.04);
  else if (level >= 1)
    return (float)(1.30+(float)level*0.03);

  return 1.00;
}

int ChiHun_cost(struct Ability* self)
{
  return self->level * 3 + 33;
}

void ChiHun_before(struct Ability* self, struct Hero* attacker, struct Hero* target)
{
  Hero_Info(attacker)->attribMZ -= 15;
}
void ChiHun_after(struct Ability* self, struct Hero* attacker, struct Hero* target)
{
  Hero_Info(attacker)->attribMZ += 15;
}

float ChiHun_damage(struct Ability* self, struct Hero* attacker, struct Hero* target)
{
  return damage_RollAttack(attacker)*ChiHun_get_attackup(self->level);
}

char ChiHun_name[] =  ("斥魂");
struct Ability_Info abilityinfo_ChiHun =
{
  ChiHun_name,
  NULL,
  NULL,
  NULL,
  ChiHun_cost,
  NULL,
  ChiHun_before,
  ChiHun_damage,
  ChiHun_after,
  NULL,
  NULL,
  1,
};

void ChiHun_bind()
{
   Ability_bind(&abilityinfo_ChiHun);
}

