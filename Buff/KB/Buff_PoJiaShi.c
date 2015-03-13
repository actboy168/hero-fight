#include "../Buff_private.h"

void PoJiaShi_Buff_Start(struct Buff* self, struct BuffList* list);
void PoJiaShi_Buff_Stop(struct Buff* self, struct BuffList* list);

const char PoJiaShi_startStr[] = ("%s的护甲被降低了。");
const char PoJiaShi_stopStr[] = ("%s的护甲恢复了正常。");

struct Buff PoJiaShiInfo =
{
  PoJiaShi_ID,
  BUFF_TYPE_TURN,
  1.0,
  PoJiaShi_Buff_Start,
  PoJiaShi_Buff_Stop,
  PoJiaShi_startStr,
  PoJiaShi_stopStr
};

void PoJiaShi_Buff_Start(struct Buff* self, struct BuffList* list)
{
  BuffList_Apply_Defend(list, self->data_1, 0);
}

void PoJiaShi_Buff_Stop(struct Buff* self, struct BuffList* list)
{
  BuffList_Apply_Defend(list, -self->data_1, 0);
}

struct Buff* PoJiaShiBuff_Get(unsigned int level)
{
  PoJiaShiInfo.data_1 = (-1)*(level*2+20);

  return &PoJiaShiInfo;
}
