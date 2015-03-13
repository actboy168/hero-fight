#include "../Buff_private.h"

void ZhuiYingShi_Buff_Start(struct Buff* self, struct BuffList* list);
void ZhuiYingShi_Buff_Stop(struct Buff* self, struct BuffList* list);

const char ZhuiYingShi_startStr[] = ("%s脚下生风，忽的加速，四周仿佛充斥着%s的影子。");
const char ZhuiYingShi_stopStr[] = ("%s的脚步逐渐慢了下来。");

struct Buff ZhuiYingShiInfo =
{
  ZhuiYingShi_ID,
  BUFF_TYPE_TURN,
  1.0,
  ZhuiYingShi_Buff_Start,
  ZhuiYingShi_Buff_Stop,
  ZhuiYingShi_startStr,
  ZhuiYingShi_stopStr
};

void ZhuiYingShi_Buff_Start(struct Buff* self, struct BuffList* list)
{
  BuffList_Apply_Speed(list,  self->data_1, 1);
}

void ZhuiYingShi_Buff_Stop(struct Buff* self, struct BuffList* list)
{
  BuffList_Apply_Speed(list, -self->data_1, 0);
}

struct Buff* ZhuiYingShiBuff_Get(unsigned int data)
{
  ZhuiYingShiInfo.data_1 = data;
  return &ZhuiYingShiInfo;
}
