#include "../Ability_private.h"

#include "../../Core/miniCRT.h"

int ZhenWuWoJianQi_cost(struct Ability* self)
{
  return 200;
}

float ZhenWuWoJianQi_damage(struct Ability* self, struct Hero* attacker, struct Hero* target)
{
  return Crt_GetRandomInt(585, 640);
}

char ZhenWuWoJianQi_name[] = ("真无我剑气");
struct Ability_Info abilityinfo_ZhenWuWoJianQi =
{
  ZhenWuWoJianQi_name,
  NULL,
  NULL,
  NULL,
  ZhenWuWoJianQi_cost,
  NULL,
  NULL,
  ZhenWuWoJianQi_damage,
  NULL,
  NULL,
  NULL,
  1
};

void ZhenWuWoJianQi_bind()
{
  // 无视防御和反弹
  Ability_set_antiFY(&abilityinfo_ZhenWuWoJianQi);
  Ability_set_antiFT(&abilityinfo_ZhenWuWoJianQi);
  Ability_bind(&abilityinfo_ZhenWuWoJianQi);
}
