#ifndef INCLUDE_BUFFLIST
#define INCLUDE_BUFFLIST

struct Buff;
struct BuffList;
struct HeroInfo;

struct BuffList* BuffList_Create(const char* name, struct HeroInfo* info, struct HeroInfo* current);
void BuffList_Destroy(struct BuffList* self);
void BuffList_Reset(struct BuffList* self);

int BuffList_Turn(struct BuffList* self, int time);
void BuffList_waitTurn(struct BuffList* self);
void BuffList_setTurn(struct BuffList* self, float turn);
int BuffList_HaveBuff_inStable(struct BuffList* self, int id);
int BuffList_HaveBuff_inStart(struct BuffList* self, int id);
int BuffList_HaveBuff(struct BuffList* self, int id);
struct Buff* BuffList_GetBuff(struct BuffList* self, int id);
int BuffList_Add(struct BuffList* self, struct Buff* buff);
void BuffList_OutStartString(struct BuffList* self);
void BuffList_Clear(struct BuffList* self);
int BuffList_needClear(struct BuffList* self);
void BuffList_Timeout(struct BuffList* self);
void BuffList_Turnout(struct BuffList* self);
void BuffList_SetDuanChangDot(struct BuffList* self);

#endif
