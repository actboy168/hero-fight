#include "../Buff_private.h"

void FuHuShi_Buff_Start(struct Buff* self, struct BuffList* list);
void FuHuShi_Buff_Stop(struct Buff* self, struct BuffList* list);

const char FuHuShi_startStr[] = ("%s的伤口破裂，鲜血不断涌出。");
const char FuHuShi_stopStr[] = ("%s按住伤口，暂时止住了不断涌出的鲜血。");

struct Buff FuHuShiInfo =
{
  FuHuShi_ID,
  BUFF_TYPE_TIME,
  1.0,
  FuHuShi_Buff_Start,
  FuHuShi_Buff_Stop,
  FuHuShi_startStr,
  FuHuShi_stopStr
};

void FuHuShi_Buff_Start(struct Buff* self, struct BuffList* list)
{
  list->current->m_sum_dot++;
  list->current->m_dot_b = self->data_1;
}

void FuHuShi_Buff_Stop(struct Buff* self, struct BuffList* list)
{
  list->current->m_sum_dot--;
}

struct Buff* FuHuShiBuff_Get(unsigned int level)
{
  FuHuShiInfo.dur = (float)(level/2+1);
  FuHuShiInfo.data_1 = (level+1)/2;//damage

  return &FuHuShiInfo;
}
