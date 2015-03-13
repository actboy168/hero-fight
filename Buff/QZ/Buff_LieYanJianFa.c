#include "../Buff_private.h"

void LieYanJianFa_Buff_Start(struct Buff* self, struct BuffList* list);
void LieYanJianFa_Buff_Stop(struct Buff* self, struct BuffList* list);

const char LieYanJianFa_startStr[] = ("%s的身体被烈焰缠绕，痛不欲生！");
const char LieYanJianFa_stopStr[] = ("烈焰逐渐从%s的身体内消散，灼热的痛苦终于退却。");

struct Buff LieYanJianFaInfo =
{
  LieYanJianFa_ID,
  BUFF_TYPE_TIME,
  10.0,
  LieYanJianFa_Buff_Start,
  LieYanJianFa_Buff_Stop,
  LieYanJianFa_startStr,
  LieYanJianFa_stopStr
};

void LieYanJianFa_Buff_Start(struct Buff* self, struct BuffList* list)
{
  list->current->m_sum_dot++;
  list->current->m_dot_a = self->data_1;
}

void LieYanJianFa_Buff_Stop(struct Buff* self, struct BuffList* list)
{
  list->current->m_sum_dot--;
}

struct Buff* LieYanJianFaBuff_Get(unsigned int level)
{
  LieYanJianFaInfo.data_1 = level * 2 + 2;
  return &LieYanJianFaInfo;
}
