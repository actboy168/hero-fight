#include "../../Ability_private.h"
#include "../../../Core/Output.h"

int HuanQi_KuangNuQiangFa_cost(struct Ability* self)
{
  return 63;
}

void HuanQi_KuangNuQiangFa_add_buff_to_target(struct Ability* self, struct Hero* attacker, struct Hero* target)
{
  Hero_AddBuff(target, HuanQi_KuangNuQiangFaBuff_Get(self->level));
}

void HuanQi_KuangNuQiangFa_output(struct Ability* self, struct Hero* attacker, struct Hero* target)
{
  Output_Damage_name(("狂怒枪法"));
  Output_Damage_push(("%s 攻击 %s。"), Hero_Name(attacker), Hero_Name(target));
}

char HuanQi_KuangNuQiangFa_name[] = ("桓奇-狂怒枪法");
struct Ability_Info abilityinfo_HuanQi_KuangNuQiangFa =
{
  HuanQi_KuangNuQiangFa_name,
  NULL,
  NULL,
  NULL,
  HuanQi_KuangNuQiangFa_cost,
  HuanQi_KuangNuQiangFa_output,
  NULL,
  NULL,
  NULL,
  NULL,
  HuanQi_KuangNuQiangFa_add_buff_to_target,
  1,
};

void HuanQi_KuangNuQiangFa_bind()
{
   Ability_bind(&abilityinfo_HuanQi_KuangNuQiangFa);
}
