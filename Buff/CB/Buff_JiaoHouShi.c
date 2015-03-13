#include "../Buff_private.h"

void JiaoHouShi_Buff_Start(struct Buff* self, struct BuffList* list);
void JiaoHouShi_Buff_Stop(struct Buff* self, struct BuffList* list);

const char JiaoHouShi_startStr[] = ("%s的皮肤泛起不健康的红晕。");
const char JiaoHouShi_stopStr[] = ("%s深吸一口气，皮肤恢复了正常。");

struct Buff JiaoHouShiInfo =
{
  JiaoHouShi_ID,
  BUFF_TYPE_TIME,
  10.0,
  JiaoHouShi_Buff_Start,
  JiaoHouShi_Buff_Stop,
  JiaoHouShi_startStr,
  JiaoHouShi_stopStr
};

void JiaoHouShi_Buff_Start(struct Buff* self, struct BuffList* list)
{
  list->current->attribZS += self->data_1;
}

void JiaoHouShi_Buff_Stop(struct Buff* self, struct BuffList* list)
{
  list->current->attribZS -= self->data_1;
}

struct Buff* JiaoHouShiBuff_Get(unsigned int level)
{
  JiaoHouShiInfo.data_1 = 8+level;
  return &JiaoHouShiInfo;
}
