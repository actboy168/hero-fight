#ifndef INCLUDE_ABILITY_TEMPLATE
#define INCLUDE_ABILITY_TEMPLATE

#include "../Core/Config.h"

struct Ability;
struct Hero;

typedef int (*FuncCheck)(struct Ability* self, struct Hero* attacker);
typedef float (*FuncDamage)(struct Ability* self, struct Hero* attacker, struct Hero* target);
typedef void (*FuncInit)(struct Ability* self, struct Hero* H);
typedef void (*FuncOutput)(struct Ability* self, struct Hero* attacker, struct Hero* target);
typedef void (*FuncBefore)(struct Ability* self, struct Hero* attacker, struct Hero* target);
typedef void (*FuncAfter)(struct Ability* self, struct Hero* attacker, struct Hero* target);
typedef void (*FuncPay)(struct Ability* self, struct Hero* attacker, struct Hero* target);
typedef int (*FuncCost)(struct Ability* self);
typedef void (*FuncAddBuff_A)(struct Ability* self, struct Hero* attacker, struct Hero* target);
typedef void (*FuncAddBuff_T)(struct Ability* self, struct Hero* attacker, struct Hero* target);

struct Ability_Info
{
  char* name;
  FuncInit init;
  FuncCheck check;
  FuncPay pay;
  FuncCost cost;
  FuncOutput output;
  FuncBefore before;
  FuncDamage damage;
  FuncAfter after;
  FuncAddBuff_A add_buff_to_attacker;
  FuncAddBuff_T add_buff_to_target;
  int count;
  int features;
};

extern struct Ability_Info abilityinfo_default;
extern struct Ability ability_default;

int Ability_GetRealCost(struct Ability* self, struct Hero* attacker);
struct Ability_Info* Ability_GetEntry(const char* name);
void Ability_bind(struct Ability_Info* abilityinfo);

void Ability_set_antiFY(struct Ability_Info* abilityinfo);
void Ability_set_antiFT(struct Ability_Info* abilityinfo);
void Ability_set_antiBX(struct Ability_Info* abilityinfo);
void Ability_set_features(struct Ability_Info* abilityinfo, int antiFY, int antiFT, int antiBX);

#endif
