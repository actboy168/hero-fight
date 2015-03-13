#include "../Ability_private.h"

int ZhanXuan_cost(struct Ability* self)
{
  return self->level * 5 + 49;
}

void ZhanXuan_before(struct Ability* self, struct Hero* attacker, struct Hero* target)
{
  Hero_Info(attacker)->attribMZ -= 12;
}
void ZhanXuan_after(struct Ability* self, struct Hero* attacker, struct Hero* target)
{
  Hero_Info(attacker)->attribMZ += 12;
}

void ZhanXuan_add_buff_to_attacker(struct Ability* self, struct Hero* attacker, struct Hero* target)
{
  Hero_AddBuff(attacker, ZhanXuanJianFaBuff_Get(self->master_data_2, self->master_data_3));
}

float ZhanXuan_damage(struct Ability* self, struct Hero* attacker, struct Hero* target)
{
  return damage_RollAttack(attacker)*(float)((float)(self->data_1+self->master_data_1)/(float)100.0 + 1.00);
}

void ZhanXuan_init(struct Ability* self, struct Hero* H)
{
  self->master_data_1 = 0;
  self->master_data_2 = 0;
  self->master_data_3 = 0;

  if (self->data_1 == 0 && Hero_InfoEx(H)->attribBL != 0)
  {
    float A = 0.013*self->level - 0.001;
    float B =   0.8*self->level + 22.7;

    self->data_1 = (int)(Hero_InfoEx(H)->attribBL * A + B);
  }

  // 精通境
  if (Hero_InfoEx(H)->attribBL - 148 > 0)
  {
    self->master_data_1 += (Hero_InfoEx(H)->attribBL - 148) / 3 * 1;
    if (self->master_data_1 > 90) self->master_data_1 = 90;

    self->master_data_2 += (Hero_InfoEx(H)->attribBL - 148) / 10 * 1;
    if (self->master_data_2 > 24) self->master_data_2 = 24;

    self->master_data_3 += (Hero_InfoEx(H)->attribBL - 148) / 20 * 1;
    if (self->master_data_3 > 12) self->master_data_3 = 12;
  }
}

char ZhanXuan_name[] = ("斩玄剑法");
struct Ability_Info abilityinfo_ZhanXuan =
{
  ZhanXuan_name,
  ZhanXuan_init,
  NULL,
  NULL,
  ZhanXuan_cost,
  NULL,
  ZhanXuan_before,
  ZhanXuan_damage,
  ZhanXuan_after,
  ZhanXuan_add_buff_to_attacker,
  NULL,
  1
};

void ZhanXuan_bind()
{
   Ability_bind(&abilityinfo_ZhanXuan);
}
