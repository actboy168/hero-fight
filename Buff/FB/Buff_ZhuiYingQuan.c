#include "../Buff_private.h"

void ZhuiYingQuan_Buff_Start(struct Buff* self, struct BuffList* list);
void ZhuiYingQuan_Buff_Stop(struct Buff* self, struct BuffList* list);

struct Buff ZhuiYingQuanInfo =
{
  ZhuiYingQuan_ID,
  BUFF_TYPE_TURN,
  2.0,
  ZhuiYingQuan_Buff_Start,
  ZhuiYingQuan_Buff_Stop,
  NULL,
  NULL
};

void ZhuiYingQuan_Buff_Start(struct Buff* self, struct BuffList* list)
{
  BuffList_Apply_Speed(list,  100, 1);
}

void ZhuiYingQuan_Buff_Stop(struct Buff* self, struct BuffList* list)
{
  BuffList_Apply_Speed(list, -100, 0);
}

struct Buff* ZhuiYingQuanBuff_Get(unsigned int level)
{
  return &ZhuiYingQuanInfo;
}
