#include "../../Ability_private.h"

#include "../../../Core/Output.h"

int ChangWenJun_LongJuanQiangFa_cost(struct Ability* self)
{
  return 165;
}

void ChangWenJun_LongJuanQiangFa_add_buff_to_target(struct Ability* self, struct Hero* attacker, struct Hero* target)
{
  Hero_AddBuff(target, LongJuanQiangFaBuff_Get(10));
}

float ChangWenJun_LongJuanQiangFa_damage(struct Ability* self, struct Hero* attacker, struct Hero* target)
{
  return damage_RollAttack(attacker)*(float)(1.5);
}

void ChangWenJun_LongJuanQiangFa_output(struct Ability* self, struct Hero* attacker, struct Hero* target)
{
  Output_Damage_name(("龙卷枪法"));
  Output_Damage_push(("%s 攻击 %s。"), Hero_Name(attacker), Hero_Name(target));
}

char ChangWenJun_LongJuanQiangFa_name[] = ("昌文君-龙卷枪法");
struct Ability_Info abilityinfo_ChangWenJun_LongJuanQiangFa =
{
  ChangWenJun_LongJuanQiangFa_name,
  NULL,
  NULL,
  NULL,
  ChangWenJun_LongJuanQiangFa_cost,
  ChangWenJun_LongJuanQiangFa_output,
  NULL,
  ChangWenJun_LongJuanQiangFa_damage,
  NULL,
  NULL,
  ChangWenJun_LongJuanQiangFa_add_buff_to_target,
  1,
};

void ChangWenJun_LongJuanQiangFa_bind()
{
   Ability_bind(&abilityinfo_ChangWenJun_LongJuanQiangFa);
}
