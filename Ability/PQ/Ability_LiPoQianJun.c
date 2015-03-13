#include "../Ability_private.h"

int LiPoQianJun_cost(struct Ability* self)
{
  return self->level * 12 + 100;
}

void LiPoQianJun_before(struct Ability* self, struct Hero* attacker, struct Hero* target)
{
  Hero_Info(attacker)->attribBS += self->data_1;
}
void LiPoQianJun_after(struct Ability* self, struct Hero* attacker, struct Hero* target)
{
  Hero_Info(attacker)->attribBS -= self->data_1;
}

float LiPoQianJun_damage(struct Ability* self, struct Hero* attacker, struct Hero* target)
{
  return damage_RollAttack(attacker)*(float)(self->level * 0.01 + 1.21);
}

void LiPoQianJun_init(struct Ability* self, struct Hero* H)
{
  // 力破千钧的暴击伤害加成公式，分为2段；此处为高臂力部分，低臂力由于没什么用处故没有实现。
  if (self->data_1 == 0 && Hero_InfoEx(H)->attribBL != 0)
  {
    float A = 0.016*self->level + 0.607;
    float B =   1.3*self->level + 48.1;

    self->data_1 = (int)(Hero_InfoEx(H)->attribBL * A - B);
    if (self->data_1 > 250)  self->data_1 = 250;
  }
}

char LiPoQianJun_name[] =  ("力破千钧");
struct Ability_Info abilityinfo_LiPoQianJun =
{
  LiPoQianJun_name,
  LiPoQianJun_init,
  NULL,
  NULL,
  LiPoQianJun_cost,
  NULL,
  LiPoQianJun_before,
  LiPoQianJun_damage,
  LiPoQianJun_after,
  NULL,
  NULL,
  1,
};

void LiPoQianJun_bind()
{
   Ability_bind(&abilityinfo_LiPoQianJun);
}

