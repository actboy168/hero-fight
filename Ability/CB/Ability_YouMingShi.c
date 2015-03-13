#include "../Ability_private.h"

int YouMingShi_cost(struct Ability* self)
{
  return self->level * 2 + 33;
}

void YouMingShi_before(struct Ability* self, struct Hero* attacker, struct Hero* target)
{
  Hero_Info(attacker)->attribMZ -= 10;
}

void YouMingShi_after(struct Ability* self, struct Hero* attacker, struct Hero* target)
{
  Hero_Info(attacker)->attribMZ += 10;
}

float YouMingShi_damage(struct Ability* self, struct Hero* attacker, struct Hero* target)
{
  return damage_RollAttack(attacker) + (float)(self->level * 5 + 15);
}

char YouMingShi_name[] =  ("幽冥式");
struct Ability_Info abilityinfo_YouMingShi =
{
  YouMingShi_name,
  NULL,
  NULL,
  NULL,
  YouMingShi_cost,
  NULL,
  YouMingShi_before,
  YouMingShi_damage,
  YouMingShi_after,
  NULL,
  NULL,
  1,
};

void YouMingShi_bind()
{
   Ability_bind(&abilityinfo_YouMingShi);
}

