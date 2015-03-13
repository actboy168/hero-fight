#include "../Ability_private.h"

int KuangNuQiangFa_cost(struct Ability* self)
{
  return self->level * 4 + 59;
}

void KuangNuQiangFa_add_buff_to_target(struct Ability* self, struct Hero* attacker, struct Hero* target)
{
  Hero_AddBuff(target, KuangNuQiangFaBuff_Get(self->level));
}

char KuangNuQiangFa_name[] = ("狂怒枪法");
struct Ability_Info abilityinfo_KuangNuQiangFa =
{
  KuangNuQiangFa_name,
  NULL,
  NULL,
  NULL,
  KuangNuQiangFa_cost,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  KuangNuQiangFa_add_buff_to_target,
  1,
};

void KuangNuQiangFa_bind()
{
   Ability_bind(&abilityinfo_KuangNuQiangFa);
}
