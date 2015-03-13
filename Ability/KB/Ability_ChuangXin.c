#include "../Ability_private.h"

int ChuangXin_cost(struct Ability* self)
{
  return self->level * 12 + 123;
}

void ChuangXin_add_buff_to_attacker(struct Ability* self, struct Hero* attacker, struct Hero* target)
{
  Hero_AddBuff(attacker, ChuangXinBBuff_Get(self->master_data_2));
}

void ChuangXin_add_buff_to_target(struct Ability* self, struct Hero* attacker, struct Hero* target)
{
  if (Hero_checkAbilityRandom(attacker, self->level*2 + 36))
    Hero_AddBuff(target, ChuangXinABuff_Get(self->level));
}

float ChuangXin_damage(struct Ability* self, struct Hero* attacker, struct Hero* target)
{
  return damage_RollAttack(attacker) + (float)(self->level*4 + 20 + self->master_data_1);
}

void ChuangXin_init(struct Ability* self, struct Hero* H)
{
  int addupA1 = 0, addupA2 = 0, addupB1 = 0, addupB2 = 0;

  self->master_data_1 = 0;
  self->master_data_2 = 0;

  // 精通境
  if (Hero_InfoEx(H)->attribGG - 172 > 0)
  {
    addupA1 = (Hero_InfoEx(H)->attribGG - 172) / 5 * 1;
    addupA2 = (Hero_InfoEx(H)->attribGG - 172) / 27 * 1;
  }

  if (Hero_InfoEx(H)->attribSF - 354 > 0)
  {
    addupB1 = (Hero_InfoEx(H)->attribSF - 354) / 3 * 1;
    addupB2 = (Hero_InfoEx(H)->attribSF - 354) / 20 * 1;
  }

  if (addupA1 > addupB1)
  {
    self->master_data_1 = addupA1;
  }
  else
  {
    self->master_data_1 = addupB1;
  }

  if (addupA2 > addupB2)
  {
    self->master_data_2 = addupA2;
  }
  else
  {
    self->master_data_2 = addupB2;
  }

  if (self->master_data_1 > 35) self->master_data_1 = 35;
  if (self->master_data_2 > 7) self->master_data_2 = 7;
}

char ChuangXin_name[] =  ("穿心");
struct Ability_Info abilityinfo_ChuangXin =
{
  ChuangXin_name,
  ChuangXin_init,
  NULL,
  NULL,
  ChuangXin_cost,
  NULL,
  NULL,
  ChuangXin_damage,
  NULL,
  ChuangXin_add_buff_to_attacker,
  ChuangXin_add_buff_to_target,
  1,
};

void ChuangXin_bind()
{
   Ability_bind(&abilityinfo_ChuangXin);
}
