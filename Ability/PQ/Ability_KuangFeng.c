#include "../Ability_private.h"

int KuangFeng_cost(struct Ability* self)
{
  return self->level * 6 + 54;
}

void KuangFeng_before(struct Ability* self, struct Hero* attacker, struct Hero* target)
{
  Hero_Info(attacker)->attribMZ -= 12;
}
void KuangFeng_after(struct Ability* self, struct Hero* attacker, struct Hero* target)
{
  Hero_Info(attacker)->attribMZ += 12;
}

float KuangFeng_damage(struct Ability* self, struct Hero* attacker, struct Hero* target)
{
  return ((damage_RollAttack(attacker) + (float)self->master_data_1))*(float)(self->level * 0.01 + 0.44);
}

void KuangFeng_init(struct Ability* self, struct Hero* H)
{
  self->master_data_1 = 0;

  // 精通境
  if (Hero_InfoEx(H)->def - 1700 > 0)
  {
    self->master_data_1 += (Hero_InfoEx(H)->def - 1700) / 10 * 1;
    if (self->master_data_1 > 183) self->master_data_1 = 183;
  }
}

char KuangFeng_name[] =  ("狂风枪法");
struct Ability_Info abilityinfo_KuangFeng =
{
  KuangFeng_name,
  KuangFeng_init,
  NULL,
  NULL,
  KuangFeng_cost,
  NULL,
  KuangFeng_before,
  KuangFeng_damage,
  KuangFeng_after,
  NULL,
  NULL,
  3,
};

void KuangFeng_bind()
{
   Ability_bind(&abilityinfo_KuangFeng);
}

