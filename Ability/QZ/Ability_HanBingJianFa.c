#include "../Ability_private.h"

int HanBingJianFa_cost(struct Ability* self)
{
  return ((self->level < 14)?(140 - self->level * 10):0);
}

void HanBingJianFa_add_buff_to_target(struct Ability* self, struct Hero* attacker, struct Hero* target)
{
  Hero_AddBuff(target, HanBingJianFaBuff_Get(self->level));
}

float HanBingJianFa_damage(struct Ability* self, struct Hero* attacker, struct Hero* target)
{
  return damage_RollAttack(attacker)+(float)((float)self->level*7 + 25);
}

char HanBingJianFa_name[] = ("寒冰剑法");
struct Ability_Info abilityinfo_HanBingJianFa =
{
  HanBingJianFa_name,
  NULL,
  NULL,
  NULL,
  HanBingJianFa_cost,
  NULL,
  NULL,
  HanBingJianFa_damage,
  NULL,
  NULL,
  HanBingJianFa_add_buff_to_target,
  1,
};

void HanBingJianFa_bind()
{
   Ability_bind(&abilityinfo_HanBingJianFa);
}
