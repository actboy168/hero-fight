#include "../Ability_private.h"

float LongJuanQiangFa_get_attackup(int level)
{
  if (level <= 8)
    return (float)(1.06);
  else if (level <= 11)
    return (float)(1.07);
  else if (level == 12)
    return (float)(1.08);
  else if (level == 13)
    return (float)(1.09);
  else if (level == 14)
    return (float)(1.10);
  else if (level == 15)
    return (float)(1.13);
  else if (level >= 16)
    return (float)(1.23);

  return 1.00;
}

int LongJuanQiangFa_cost(struct Ability* self)
{
  return self->level * 8 + 85;
}

void LongJuanQiangFa_add_buff_to_target(struct Ability* self, struct Hero* attacker, struct Hero* target)
{
  Hero_AddBuff(target, LongJuanQiangFaBuff_Get(self->level));
}

float LongJuanQiangFa_damage(struct Ability* self, struct Hero* attacker, struct Hero* target)
{
  return damage_RollAttack(attacker)*LongJuanQiangFa_get_attackup(self->level);
}

char LongJuanQiangFa_name[] = ("龙卷枪法");
struct Ability_Info abilityinfo_LongJuanQiangFa =
{
  LongJuanQiangFa_name,
  NULL,
  NULL,
  NULL,
  LongJuanQiangFa_cost,
  NULL,
  NULL,
  LongJuanQiangFa_damage,
  NULL,
  NULL,
  LongJuanQiangFa_add_buff_to_target,
  1,
};

void LongJuanQiangFa_bind()
{
   Ability_bind(&abilityinfo_LongJuanQiangFa);
}
