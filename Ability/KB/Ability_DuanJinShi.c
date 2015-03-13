#include "../Ability_private.h"

int DuanJinShi_cost(struct Ability* self)
{
  return 28 + self->level*2;
}

void DuanJinShi_add_buff_to_target(struct Ability* self, struct Hero* attacker, struct Hero* target)
{
  Hero_AddBuff(target, DuanJinShiBuff_Get(self->level));
}

float DuanJinShi_damage(struct Ability* self, struct Hero* attacker, struct Hero* target)
{
  return damage_RollAttack(attacker)+(float)((float)self->level*2 + 4);
}

char DuanJinShi_name[] = ("断筋式");
struct Ability_Info abilityinfo_DuanJinShi =
{
  DuanJinShi_name,
  NULL,
  NULL,
  NULL,
  DuanJinShi_cost,
  NULL,
  NULL,
  DuanJinShi_damage,
  NULL,
  NULL,
  DuanJinShi_add_buff_to_target,
  1,
};

void DuanJinShi_bind()
{
   Ability_bind(&abilityinfo_DuanJinShi);
}
