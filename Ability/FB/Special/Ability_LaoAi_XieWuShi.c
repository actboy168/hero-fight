#include "../../Ability_private.h"
#include "../../../Core/Output.h"

int LaoAi_XieWuShi_check(struct Ability* self, struct Hero* attacker)
{
  return (Hero_checkAbilityRandom(attacker, 25));
}

int LaoAi_XieWuShi_cost(struct Ability* self)
{
  return 125;
}

void LaoAi_XieWuShi_add_buff_to_target(struct Ability* self, struct Hero* attacker, struct Hero* target)
{
  Hero_AddBuff(target, XiuWuDuanHunBuff_Get(self->level));
}

void LaoAi_XieWuShi_WuMing_output(struct Ability* self, struct Hero* attacker, struct Hero* target)
{
  Output_Damage_name(("卸武式"));
  Output_Damage_push(("%s 攻击 %s。"), Hero_Name(attacker), Hero_Name(target));
}

char LaoAi_XieWuShi_name[] =  ("嫪毐-卸武式");
struct Ability_Info abilityinfo_LaoAi_XieWuShi =
{
  LaoAi_XieWuShi_name,
  NULL,
  LaoAi_XieWuShi_check,
  NULL,
  LaoAi_XieWuShi_cost,
  LaoAi_XieWuShi_WuMing_output,
  NULL,
  NULL,
  NULL,
  NULL,
  LaoAi_XieWuShi_add_buff_to_target,
  1,
};

void LaoAi_XieWuShi_bind()
{
   Ability_bind(&abilityinfo_LaoAi_XieWuShi);
}
