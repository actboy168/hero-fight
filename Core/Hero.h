#ifndef INCLUDE_HERO
#define INCLUDE_HERO

struct Hero;
struct Buff;

int Hero_init();

struct Hero* Hero_Create(const char* pInputFileName);
void Hero_Destroy(struct Hero* self);
void Hero_Reset(struct Hero* self);

int Hero_Fight(struct Hero* A, struct Hero* B);

//===================================================================
int Hero_AddBuff(struct Hero* self, struct Buff* buff);
int Hero_isMingZhong(struct Hero* attacker, struct Hero* target, int flag);
int Hero_isBJAndPJ(struct Hero* attacker, struct Hero* target, int flag);
int Hero_GetCS(struct Hero* self);
int Hero_GetMZ(struct Hero* self);
int Hero_GetBJ(struct Hero* self);
int Hero_GetPJ(struct Hero* self);
int Hero_GetBP(struct Hero* self);
int Hero_GetAbilityCount(struct Hero* self);
void Hero_AttachBuff(struct Hero* attacker, struct Hero* target);
void Hero_SetAttachBuff(struct Hero* self, int lv, void* getBuff);
int Hero_HaveBuff(struct Hero* self, int id);
int Hero_HaveBuff_inStable(struct Hero* self, int id);
int Hero_HaveBuff_inStart(struct Hero* self, int id);
char* Hero_GetAbilityName(struct Hero* self);
int Hero_checkAbilityRandom(struct Hero* self, int n);
const char* Hero_Name(struct Hero* self);
struct HeroInfo* Hero_Info(struct Hero* self);
struct HeroInfo* Hero_InfoEx(struct Hero* self);
struct BuffList* Hero_BuffList(struct Hero* self);

int Hero_GetAbility_AntiBX(struct Hero* self);
int Hero_GetAbility_AntiFT(struct Hero* self);
int Hero_GetAbility_AntiFY(struct Hero* self);

#endif
