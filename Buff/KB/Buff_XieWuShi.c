#include "../Buff_private.h"

void XieWuShi_Buff_Start(struct Buff* self, struct BuffList* list);
void XieWuShi_Buff_Stop(struct Buff* self, struct BuffList* list);

const char XieWuShi_startStr[] = ("%s只觉手臂肌肉抽痛，虎口发麻，使不上力。");
const char XieWuShi_stopStr[] = ("%s活动活动手腕，又恢复了力量。");

struct Buff XieWuShiInfo =
{
  XieWuShi_ID,
  BUFF_TYPE_TURN,
  1.0,
  XieWuShi_Buff_Start,
  XieWuShi_Buff_Stop,
  XieWuShi_startStr,
  XieWuShi_stopStr
};

void XieWuShi_Buff_Start(struct Buff* self, struct BuffList* list)
{
  BuffList_Apply_Attack(list, 0, self->data_1);
}

void XieWuShi_Buff_Stop(struct Buff* self, struct BuffList* list)
{
  BuffList_Apply_Attack(list, 0, -self->data_1);
}

struct Buff* XieWuShiBuff_Get(unsigned int level)
{
  if (level <= 12)
    XieWuShiInfo.data_1 = (-1)*(level*2+12);
  else
    XieWuShiInfo.data_1 = (-1)*((int)(level*2.5)+6);

  return &XieWuShiInfo;
}
