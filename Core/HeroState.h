#ifndef INCLUDE_HEROSTATE
#define INCLUDE_HEROSTATE

struct HeroState;

struct HeroState* HeroState_Create();
void HeroState_Destroy(struct HeroState* self);
void HeroState_Reset(struct HeroState* self);

void HeroState_setFix(struct HeroState* self, int LvSub);

int HeroState_isMingZhong(struct HeroState* self, int attribMZ,  int attribSB, int flag, int isStat);
int HeroState_isBJAndPJ(struct HeroState* self, int attribBJ, int attribKB, int attribPJ, int attribKP, int flag, int isStats);

int HeroState_checkAbilityRandom(struct HeroState* self, int AR, int flag, int isStat);

int HeroState_GetCS(struct HeroState* self);
int HeroState_GetMZ(struct HeroState* self);
int HeroState_GetBJ(struct HeroState* self);
int HeroState_GetPJ(struct HeroState* self);
int HeroState_GetBP(struct HeroState* self);
int HeroState_GetAbilityCount(struct HeroState* self);

#endif
