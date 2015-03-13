#ifndef INCLUDE_ATACHBUFF
#define INCLUDE_ATACHBUFF

struct Hero;
struct AttachBuff;

struct AttachBuff* AttachBuff_Create();
void AttachBuff_Destroy(struct AttachBuff* self);
void AttachBuff_Run(struct AttachBuff* self, struct Hero* target);
void AttachBuff_Set(struct AttachBuff* self, int lv, void* getBuff);

#endif
