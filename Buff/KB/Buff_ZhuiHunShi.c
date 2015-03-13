#include "../Buff_private.h"

void ZhuiHunShi_Buff_Start(struct Buff* self, struct BuffList* list);
void ZhuiHunShi_Buff_Stop(struct Buff* self, struct BuffList* list);

const char ZhuiHunShi_startStr[] = ("%s的伤口破裂，鲜血不断涌出。");
const char ZhuiHunShi_stopStr[] = ("%s按住伤口，暂时止住了不断涌出的鲜血。");

struct Buff ZhuiHunShiInfo =
{
  ZhuiHunShi_ID,
  BUFF_TYPE_TIME,
  1.0,
  ZhuiHunShi_Buff_Start,
  ZhuiHunShi_Buff_Stop,
  ZhuiHunShi_startStr,
  ZhuiHunShi_stopStr
};

void ZhuiHunShi_Buff_Start(struct Buff* self, struct BuffList* list)
{
  list->current->m_sum_dot++;
  list->current->m_dot_a = self->data_1;
}

void ZhuiHunShi_Buff_Stop(struct Buff* self, struct BuffList* list)
{
  list->current->m_sum_dot--;
}

struct Buff* ZhuiHunShiBuff_Get(unsigned int level)
{
  ZhuiHunShiInfo.dur = (float)((level+1)/2+1);
  ZhuiHunShiInfo.data_1 = level/2+1;//damage

  return &ZhuiHunShiInfo;
}
