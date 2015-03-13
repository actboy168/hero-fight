#include "../Buff_private.h"

void CuiDuBiShou_Buff_Start(struct Buff* self, struct BuffList* list);
void CuiDuBiShou_Buff_Stop(struct Buff* self, struct BuffList* list);

const char CuiDuBiShou_startStr[] = ("%s感到体内气血急速流失，看来中了很深的毒，偏偏身上没带解药，暗自叫苦。");
const char CuiDuBiShou_stopStr[] = ("毒性渐渐从%s体内散去。");

struct Buff CuiDuBiShouInfo =
{
  CuiDuBiShou_ID,
  BUFF_TYPE_TIME,
  1.0,
  CuiDuBiShou_Buff_Start,
  CuiDuBiShou_Buff_Stop,
  CuiDuBiShou_startStr,
  CuiDuBiShou_stopStr
};

void CuiDuBiShou_Buff_Start(struct Buff* self, struct BuffList* list)
{
  list->current->m_sum_dot++;
  list->current->m_dot_b = self->data_1;
}

void CuiDuBiShou_Buff_Stop(struct Buff* self, struct BuffList* list)
{
  list->current->m_sum_dot--;
}

struct Buff* CuiDuBiShouBuff_Get(unsigned int level)
{
  int time = level/2+1;
  int damage = level/2+1;

  CuiDuBiShouInfo.dur = (float)time;
  CuiDuBiShouInfo.data_1 = damage;

  return &CuiDuBiShouInfo;
}
