#include "../Ability_private.h"

/*+---------------------------------------------
  |   Lv mingzhongup
  | >=23 39
  | >=13 16+Lv*1
  | <=12 3+Lv*2
 +---------------------------------------------*/
int get_mingzhongup(int level)
{
  if (level >= 23)
    return 39;
  else if (level >= 13)
    return 16+level*1;
  else if (level >= 1)
    return 3+level*2;

  return 0;
}

int FeiLong_cost(struct Ability* self)
{
  return self->level * 3 + 27;
}

void FeiLong_before(struct Ability* self, struct Hero* attacker, struct Hero* target)
{
  Hero_Info(attacker)->attribMZ += get_mingzhongup(self->level) + self->master_data_2;
}

void FeiLong_after(struct Ability* self, struct Hero* attacker, struct Hero* target)
{
  Hero_Info(attacker)->attribMZ -= get_mingzhongup(self->level) + self->master_data_2;
}

float FeiLong_damage(struct Ability* self, struct Hero* attacker, struct Hero* target)
{
  return damage_RollAttack(attacker)*((float)1.12 + (float)self->master_data_1/(float)100.0);
}

void FeiLong_init(struct Ability* self, struct Hero* H)
{
  self->master_data_1 = 0;
  self->master_data_2 = 0;

  // 精通境
  if (Hero_InfoEx(H)->attribGG - 230 > 0)
  {
    self->master_data_1 += (Hero_InfoEx(H)->attribGG - 230) / 9 * 1;
    if (self->master_data_1 > 23) self->master_data_1 = 23;

    self->master_data_2 += (Hero_InfoEx(H)->attribGG - 230) / 17 * 1;
    if (self->master_data_2 > 12) self->master_data_2 = 12;
  }
}

char FeiLong_name[] =  ("飞龙枪法");
struct Ability_Info abilityinfo_FeiLong =
{
  FeiLong_name,
  FeiLong_init,
  NULL,
  NULL,
  FeiLong_cost,
  NULL,
  FeiLong_before,
  FeiLong_damage,
  FeiLong_after,
  NULL,
  NULL,
  1,
};

void FeiLong_bind()
{
   Ability_bind(&abilityinfo_FeiLong);
}


