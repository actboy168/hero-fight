#include "../Buff_private.h"

void XiuWuDuanHun_Buff_Start(struct Buff* self, struct BuffList* list);
void XiuWuDuanHun_Buff_Stop(struct Buff* self, struct BuffList* list);

const char XiuWuDuanHun_startStr[] = ("%s的武器被挑飞，一时间不知所措。");
const char XiuWuDuanHun_stopStr[] = ("%s看准空隙，拿回了自己的武器。");

struct Buff XiuWuDuanHunInfo =
{
  XiuWuDuanHun_ID,
  BUFF_TYPE_TURN,
  1.0,
  XiuWuDuanHun_Buff_Start,
  XiuWuDuanHun_Buff_Stop,
  XiuWuDuanHun_startStr,
  XiuWuDuanHun_stopStr
};

void XiuWuDuanHun_Buff_Start(struct Buff* self, struct BuffList* list)
{
}

void XiuWuDuanHun_Buff_Stop(struct Buff* self, struct BuffList* list)
{
}

struct Buff* XiuWuDuanHunBuff_Get(unsigned int level)
{
  return &XiuWuDuanHunInfo;
}

int XiuWuDuanHun_GetID()
{
  return XiuWuDuanHun_ID;
}
