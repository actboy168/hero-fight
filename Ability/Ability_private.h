#ifndef INCLUDE_ABILITY_PRIVATE
#define INCLUDE_ABILITY_PRIVATE

#include "Ability_template.h"
#include "../Core/Hero.h"
#include "../Core/HeroInfo.h"
#include "../Buff/Buff.h"

struct Ability
{
  int level;
  int data_1;
  int master_data_1;
  int master_data_2;
  int master_data_3;
  struct Ability_Info* info;
};

float damage_RollAttack(struct Hero* attacker);

#endif
