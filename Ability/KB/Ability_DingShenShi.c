#include "../Ability_private.h"

int DingShenShi_add_attack(int level)
{
  int attack = 0;
  switch(level)
  {
  case  0:attack = 0;break;
  case  1:attack = 32;break;
  case  2:attack = 35;break;
  case  3:attack = 39;break;
  case  4:attack = 42;break;
  case  5:attack = 45;break;
  case  6:attack = 49;break;
  case  7:attack = 52;break;
  case  8:attack = 56;break;
  case  9:attack = 59;break;
  case 10:attack = 63;break;
  case 11:attack = 67;break;
  case 12:attack = 71;break;
  case 13:attack = 76;break;
  case 14:attack = 80;break;
  case 15:attack = 84;break;
  case 16:attack = 89;break;
  case 17:attack = 94;break;
  case 18:attack = 100;break;
  case 19:attack = 106;break;
  case 20:attack = 115;break;
  case 21:attack = 123;break;
  case 22:attack = 132;break;
  case 23:attack = 142;break;
  case 24:attack = 153;break;
  case 36:attack = 523;break;
  default:
    attack = (int)(0.00064*(level*level-42.8*level+747.0)*(level*level+7.43*level+64.0));
    break;
  }
  return attack;
}

int DingShenShi_cost(struct Ability* self)
{
  return self->level * 4 + 46;
}

void DingShenShi_add_buff_to_target(struct Ability* self, struct Hero* attacker, struct Hero* target)
{
  Hero_AddBuff(target, DingShenShiBuff_Get(self->level));
}

void DingShenShi_before(struct Ability* self, struct Hero* attacker, struct Hero* target)
{
  Hero_Info(attacker)->attribMZ += self->level;
}
void DingShenShi_after(struct Ability* self, struct Hero* attacker, struct Hero* target)
{
  Hero_Info(attacker)->attribMZ -= self->level;
}

float DingShenShi_damage(struct Ability* self, struct Hero* attacker, struct Hero* target)
{
  return damage_RollAttack(attacker) + (float)(DingShenShi_add_attack(self->level));
}

char DingShenShi_name[] =  ("定身式");
struct Ability_Info abilityinfo_DingShenShi =
{
  DingShenShi_name,
  NULL,
  NULL,
  NULL,
  DingShenShi_cost,
  NULL,
  DingShenShi_before,
  DingShenShi_damage,
  DingShenShi_after,
  NULL,
  DingShenShi_add_buff_to_target,
  1,
};

void DingShenShi_bind()
{
   Ability_bind(&abilityinfo_DingShenShi);
}
