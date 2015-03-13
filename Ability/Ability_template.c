#include "Ability_template.h"
#include "Ability_private.h"
#include "../Core/Output.h"

struct Ability_Info abilityinfo_default =
{
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  0
};

struct Ability ability_default =
{
  0,
  0,
  0,
  0,
  0,
  &abilityinfo_default
};

void init_default(struct Ability* self, struct Hero* H)
{
  //do nothing
}

int Ability_GetRealCost(struct Ability* self, struct Hero* attacker)
{
  int cost = self->info->cost(self);
  int attribXJ = Hero_Info(attacker)->attribXJ;
  if (attribXJ == 0)
  {
    return cost;
  }
  else if (attribXJ >= 100)
  {
    return 0;
  }
  else
  {
    float k = (float)1.0-(float)attribXJ/(float)100.0;

    return (int) (cost*k+0.5);
  }
}

int check_default(struct Ability* self, struct Hero* attacker)
{
  return (Hero_Info(attacker)->MP >= Ability_GetRealCost(self, attacker));
}

void pay_default(struct Ability* self, struct Hero* attacker, struct Hero* target)
{
  Hero_Info(attacker)->MP -= Ability_GetRealCost(self, attacker);
}

int cost_default(struct Ability* self)
{
  return 0;
}

void output_default(struct Ability* self, struct Hero* attacker, struct Hero* target)
{
  Output_Damage_name(self->info->name);
  Output_Damage_push(("%s 攻击 %s。"), Hero_Name(attacker), Hero_Name(target));
}

void before_default(struct Ability* self, struct Hero* attacker, struct Hero* target)
{
  //do nothing
}

float damage_default(struct Ability* self, struct Hero* attacker, struct Hero* target)
{
  return damage_RollAttack(attacker);
}

void after_default(struct Ability* self, struct Hero* attacker, struct Hero* target)
{
  //do nothing
}

void add_buff_to_attacker_default(struct Ability* self, struct Hero* attacker, struct Hero* target)
{
  //do nothing
}

void add_buff_to_target_default(struct Ability* self, struct Hero* attacker, struct Hero* target)
{
  //do nothing
}

struct Ability_Info* info[256];
unsigned int infotop = 0;

struct Ability_Info* Ability_GetEntry(const char* name)
{
  unsigned int i = 1;
  while (i < infotop)
  {
    if (0 == strcmp(name, info[i]->name))
    {
      return info[i];
    }

    i++;
  }

  //default
  return &abilityinfo_default;
}


void Ability_set_antiFY(struct Ability_Info* abilityinfo)
{
  abilityinfo->features |= 0x04;
}

void Ability_set_antiFT(struct Ability_Info* abilityinfo)
{
  abilityinfo->features |= 0x02;
}

void Ability_set_antiBX(struct Ability_Info* abilityinfo)
{
  abilityinfo->features |= 0x01;
}

void Ability_set_features(struct Ability_Info* abilityinfo, int antiFY, int antiFT, int antiBX)
{
  abilityinfo->features = ((antiFY&0x01)<<2)|((antiFT&0x01)<<1)|((antiBX&0x01)<<0);
}

void Ability_bind(struct Ability_Info* abilityinfo)
{
#define SET_DEFAULT(func) \
  do { \
    if (abilityinfo->func == NULL) \
      abilityinfo->func = func##_default;\
  } while(0)

  SET_DEFAULT(init);
  SET_DEFAULT(check);
  SET_DEFAULT(cost);
  SET_DEFAULT(pay);
  SET_DEFAULT(output);
  SET_DEFAULT(before);
  SET_DEFAULT(damage);
  SET_DEFAULT(after);
  SET_DEFAULT(add_buff_to_attacker);
  SET_DEFAULT(add_buff_to_target);

  if (abilityinfo->count == 0) abilityinfo->count = 1;

  info[infotop++] = abilityinfo;

#undef SET_DEFAULT
}
