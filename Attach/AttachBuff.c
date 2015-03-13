#include "AttachBuff.h"

#include "../Core/Config.h"
#include "../Core/Mem.h"
#include "../Core/Hero.h"

#include "../Buff/Buff.h"

typedef struct Buff* (*FuncBuff)(unsigned int level);

struct AttachBuff
{
  int enable;
  unsigned int level;
  FuncBuff buffCreater;
};

struct AttachBuff* AttachBuff_Create()
{
  struct AttachBuff* self = Mem_new(self, struct AttachBuff);

  memset(self, 0, sizeof(struct AttachBuff));

  return self;
}

void AttachBuff_Destroy(struct AttachBuff* self)
{
  Mem_delete(self);
}

void AttachBuff_Run(struct AttachBuff* self, struct Hero* target)
{
  if (self->enable)
  {
    Hero_AddBuff(target, self->buffCreater(self->level));
  }
}

void AttachBuff_Set(struct AttachBuff* self, int lv, void* getBuff)
{
  self->enable = 1;
  self->level = lv;
  self->buffCreater = (FuncBuff)getBuff;
}
