#include "../Buff_private.h"

void ZhenJiXia_Buff_Start(struct Buff* self, struct BuffList* list);
void ZhenJiXia_Buff_Stop(struct Buff* self, struct BuffList* list);

struct Buff ZhenJiXiaInfo =
{
  ZhenJiXia_ID,
  BUFF_TYPE_TIME,
  32,
  ZhenJiXia_Buff_Start,
  ZhenJiXia_Buff_Stop,
  NULL,
  NULL
};

void ZhenJiXia_Buff_Start(struct Buff* self, struct BuffList* list)
{
  list->current->attribSB -= 50;
}

void ZhenJiXia_Buff_Stop(struct Buff* self, struct BuffList* list)
{
  list->current->attribSB += 50;
}

struct Buff* ZhenJiXiaBuff_Get()
{
  return &ZhenJiXiaInfo;
}
