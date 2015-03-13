#include "../Buff_private.h"
#include "../BuffList.h"
#include "../../Core/Hero.h"

void DuanChang_Buff_Start(struct Buff* self, struct BuffList* list);
void DuanChang_Buff_Stop(struct Buff* self, struct BuffList* list);

const char DuanChang_startStr[] = ("%s的五脏六腑一阵剧痛，身体中的力气似乎都被抽空了。");
const char DuanChang_stopStr[] = ("剧痛逐渐消失，%s的身体恢复了正常。");

struct Buff DuanChangInfo =
{
  DuanChang_ID,
  BUFF_TYPE_TIME,
  6.0,
  DuanChang_Buff_Start,
  DuanChang_Buff_Stop,
  DuanChang_startStr,
  DuanChang_stopStr
};

int DuanChangBuff_GetDamage(unsigned int level, struct HeroInfo* heroinfo)
{
  double x = 1.0 - (double)heroinfo->HP/(double)heroinfo->maxHP;
  double y = (((1.1*x-1.1)*x+0.73)*x+0.27)*x;
  int min = level*1;
  int max = 30+level*6;
  return (int)(min+(max-min)*y);
}

void DuanChangBuff_SetDot(struct BuffList* list)
{
  if(BuffList_HaveBuff(list, DuanChang_ID))
  {
    list->current->m_dot_a = DuanChangBuff_GetDamage(BuffList_GetBuff(list, DuanChang_ID)->data_1, list->current);
  }
}

void DuanChang_Buff_Start(struct Buff* self, struct BuffList* list)
{
  list->current->m_sum_dot++;
  list->current->m_dot_a = DuanChangBuff_GetDamage(self->data_1, list->current);
}

void DuanChang_Buff_Stop(struct Buff* self, struct BuffList* list)
{
  list->current->m_sum_dot--;
}

struct Buff* DuanChangBuff_Get(unsigned int level)
{
  DuanChangInfo.data_1 = level;
  return &DuanChangInfo;
}

