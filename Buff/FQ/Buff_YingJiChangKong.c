#include "../Buff_private.h"

void YingJiChangKong_Buff_Start(struct Buff* self, struct BuffList* list);
void YingJiChangKong_Buff_Stop(struct Buff* self, struct BuffList* list);

const char YingJiChangKong_startStr[] = ("%s的伤口破裂，鲜血不断涌出。");
const char YingJiChangKong_stopStr[] = ("%s按住伤口，暂时止住了不断涌出的鲜血。");

struct Buff YingJiChangKongInfo =
{
  YingJiChangKong_ID,
  BUFF_TYPE_TIME,
  20.0,
  YingJiChangKong_Buff_Start,
  YingJiChangKong_Buff_Stop,
  YingJiChangKong_startStr,
  YingJiChangKong_stopStr
};

void YingJiChangKong_Buff_Start(struct Buff* self, struct BuffList* list)
{
  list->current->m_sum_dot++;
  list->current->m_dot_a = self->data_1;
}

void YingJiChangKong_Buff_Stop(struct Buff* self, struct BuffList* list)
{
  list->current->m_sum_dot--;
}

struct Buff* YingJiChangKongBuff_Get(unsigned int level)
{
  YingJiChangKongInfo.dur = (float)(level*5+15);
  YingJiChangKongInfo.data_1 = 9;
  return &YingJiChangKongInfo;
}
