#include "../../Ability_private.h"

#include "../../../Core/Output.h"

int ChangPingJun_WuMing_check(struct Ability* self, struct Hero* attacker)
{
  return (Hero_Info(attacker)->HP >= (int)(Hero_Info(attacker)->maxHP * 0.01));
}

void ChangPingJun_WuMing_pay(struct Ability* self, struct Hero* attacker, struct Hero* target)
{
  Hero_Info(attacker)->HP -= (int)(Hero_Info(attacker)->maxHP * 0.01);
}

void ChangPingJun_WuMing_before(struct Ability* self, struct Hero* attacker, struct Hero* target)
{
  Hero_Info(attacker)->attribMZ += 10;
}

void ChangPingJun_WuMing_after(struct Ability* self, struct Hero* attacker, struct Hero* target)
{
  Hero_Info(attacker)->attribMZ -= 10;
}

float ChangPingJun_WuMing_damage(struct Ability* self, struct Hero* attacker, struct Hero* target)
{
  return damage_RollAttack(attacker)*(float)(2.0);
}

void ChangPingJun_WuMing_add_buff_to_attacker(struct Ability* self, struct Hero* attacker, struct Hero* target)
{
  Hero_AddBuff(attacker, ZhuiYingShiBuff_Get(20));
}

void ChangPingJun_WuMing_output(struct Ability* self, struct Hero* attacker, struct Hero* target)
{
  Output_Damage_name(("无命"));
  Output_Damage_push(("%s 攻击 %s。"), Hero_Name(attacker), Hero_Name(target));
}

char ChangPingJun_WuMing_name[] = ("昌平君-无命");
struct Ability_Info abilityinfo_ChangPingJun_WuMing =
{
  ChangPingJun_WuMing_name,
  NULL,
  ChangPingJun_WuMing_check,
  ChangPingJun_WuMing_pay,
  NULL,
  ChangPingJun_WuMing_output,
  ChangPingJun_WuMing_before,
  ChangPingJun_WuMing_damage,
  ChangPingJun_WuMing_after,
  ChangPingJun_WuMing_add_buff_to_attacker,
  NULL,
  1,
};

void ChangPingJun_WuMing_bind()
{
   Ability_bind(&abilityinfo_ChangPingJun_WuMing);
}
