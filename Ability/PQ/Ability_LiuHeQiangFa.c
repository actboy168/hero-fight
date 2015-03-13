#include "../Ability_private.h"

int LiuHeQiangFa_cost(struct Ability* self)
{
  return self->level * 7 + 67;
}

void LiuHeQiangFa_add_buff_to_target(struct Ability* self, struct Hero* attacker, struct Hero* target)
{
  Hero_AddBuff(target, LiuHeQiangFaBuff_Get(self->level));
}

float LiuHeQiangFa_damage(struct Ability* self, struct Hero* attacker, struct Hero* target)
{
  return damage_RollAttack(attacker)+(float)((float)14.0+(float)self->level);
}

char LiuHeQiangFa_name[] =  ("六合枪法");
struct Ability_Info abilityinfo_LiuHeQiangFa =
{
  LiuHeQiangFa_name,
  NULL,
  NULL,
  NULL,
  LiuHeQiangFa_cost,
  NULL,
  NULL,
  LiuHeQiangFa_damage,
  NULL,
  NULL,
  LiuHeQiangFa_add_buff_to_target,
  1,
};

void LiuHeQiangFa_bind()
{
   Ability_bind(&abilityinfo_LiuHeQiangFa);
}
