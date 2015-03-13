#include "../Buff_private.h"

void LiuHeQiangFa_Buff_Start(struct Buff* self, struct BuffList* list);
void LiuHeQiangFa_Buff_Stop(struct Buff* self, struct BuffList* list);

struct Buff LiuHeQiangFaInfo =
{
  LiuHeQiangFa_ID,
  BUFF_TYPE_TIME,
  1.0,
  LiuHeQiangFa_Buff_Start,
  LiuHeQiangFa_Buff_Stop,
  NULL,
  NULL
};

void LiuHeQiangFa_Buff_Start(struct Buff* self, struct BuffList* list)
{
  list->current->m_mot += self->data_1;
}

void LiuHeQiangFa_Buff_Stop(struct Buff* self, struct BuffList* list)
{
  list->current->m_mot -= self->data_1;
}

struct Buff* LiuHeQiangFaBuff_Get(unsigned int level)
{
  LiuHeQiangFaInfo.data_1 = level*2;

  return &LiuHeQiangFaInfo;
}
