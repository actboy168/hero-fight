#include "../Buff_private.h"

void PoFengQiangFa_Buff_Start(struct Buff* self, struct BuffList* list);
void PoFengQiangFa_Buff_Stop(struct Buff* self, struct BuffList* list);

struct Buff PoFengQiangFaInfo =
{
  PoFengQiangFa_ID,
  BUFF_TYPE_TURN,
  1.0,
  PoFengQiangFa_Buff_Start,
  PoFengQiangFa_Buff_Stop,
  NULL,
  NULL
};

void PoFengQiangFa_Buff_Start(struct Buff* self, struct BuffList* list)
{
  BuffList_Apply_Speed(list,  self->data_1, 1);
  BuffList_Apply_Defend(list, 0, -self->data_1*20);
}

void PoFengQiangFa_Buff_Stop(struct Buff* self, struct BuffList* list)
{
  BuffList_Apply_Speed(list, -self->data_1, 0);
  BuffList_Apply_Defend(list, 0, self->data_1*20);
}

struct Buff* PoFengQiangFaBuff_Get(unsigned int level)
{
  PoFengQiangFaInfo.data_1 = level;
  return &PoFengQiangFaInfo;
}
