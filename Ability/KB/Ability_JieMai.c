#include "../Ability_private.h"

int JieMai_cost(struct Ability* self)
{
  return self->level * 10 + 60;
}

void JieMai_before(struct Ability* self, struct Hero* attacker, struct Hero* target)
{
  Hero_Info(attacker)->attribXN += self->level*2;
}
void JieMai_after(struct Ability* self, struct Hero* attacker, struct Hero* target)
{
  Hero_Info(attacker)->attribXN -= self->level*2;
}

float JieMai_damage(struct Ability* self, struct Hero* attacker, struct Hero* target)
{
  return damage_RollAttack(attacker)*(float)((float)self->level*0.04 + 1.54);
}

void JieMai_add_buff_to_attacker(struct Ability* self, struct Hero* attacker, struct Hero* target)
{
  Hero_AddBuff(attacker, JieMaiBuff_Get(self->level));
}


char JieMai_name[] =  ("截脉");
struct Ability_Info abilityinfo_JieMai =
{
  JieMai_name,
  NULL,
  NULL,
  NULL,
  JieMai_cost,
  NULL,
  JieMai_before,
  JieMai_damage,
  JieMai_after,
  JieMai_add_buff_to_attacker,
  NULL,
  1,
};

void JieMai_bind()
{
   Ability_bind(&abilityinfo_JieMai);
}
