#include "../Buff_private.h"

void CuiXinShi_Buff_Start(struct Buff* self, struct BuffList* list);
void CuiXinShi_Buff_Stop(struct Buff* self, struct BuffList* list);

const char CuiXinShi_startStr[] = ("%s被彻底激怒了！");
const char CuiXinShi_stopStr[] = ("%s沉心静气，将呼吸频率调整到最佳，抑制住了心口的剧痛。");

struct Buff CuiXinShiInfo =
{
  CuiXinShi_ID,
  BUFF_TYPE_TIME,
  0.0,
  CuiXinShi_Buff_Start,
  CuiXinShi_Buff_Stop,
  CuiXinShi_startStr,
  CuiXinShi_stopStr
};

void CuiXinShi_Buff_Start(struct Buff* self, struct BuffList* list)
{
  list->current->m_mot += self->data_1;
}

void CuiXinShi_Buff_Stop(struct Buff* self, struct BuffList* list)
{
  list->current->m_mot -= self->data_1;
}

struct Buff* CuiXinShiBuff_Get(unsigned int level)
{
  CuiXinShiInfo.dur = (float)level;

  CuiXinShiInfo.data_1 = ((level>=14)? 2:1);

  return &CuiXinShiInfo;
}
