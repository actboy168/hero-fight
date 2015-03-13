#ifndef INCLUDE_ABILITY
#define INCLUDE_ABILITY

#include "../Core/Config.h"

struct Ability;
struct Hero;

int Ability_init();

struct Ability* Ability_Create(struct Hero* H, ASHANDLE hFile);
void Ability_Destroy(struct Ability* self);
unsigned int Ability_Attack(struct Ability* self, struct Hero* attacker, struct Hero* target);

char* Ability_GetName(struct Ability* self);
int   Ability_GetLevel(struct Ability* self);

#define ABILITY_FEATURES_ANTIBX 0
#define ABILITY_FEATURES_ANTIFT 1
#define ABILITY_FEATURES_ANTIFY 2
int   Ability_GetFeatures(struct Ability* self, int type);

#endif

