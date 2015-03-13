#include "../Buff_private.h"

void JiBenBianFa_Buff_Start(struct Buff* self, struct BuffList* list);
void JiBenBianFa_Buff_Stop(struct Buff* self, struct BuffList* list);

const char JiBenBianFa_startStr[] = ("%s的鞭法已入化理之境界，身形不动，出鞭速度却越来越快，将云天遮蔽，方圆几里石木碎无原形。");

struct Buff JiBenBianFaInfo =
{
  JiBenBianFa_ID,
  BUFF_TYPE_TIME,
  15.0,
  JiBenBianFa_Buff_Start,
  JiBenBianFa_Buff_Stop,
  JiBenBianFa_startStr,
  NULL,
};

void JiBenBianFa_Buff_Start(struct Buff* self, struct BuffList* list)
{
  BuffList_Apply_Speed(list,  self->data_1, 1);
}

void JiBenBianFa_Buff_Stop(struct Buff* self, struct BuffList* list)
{
  BuffList_Apply_Speed(list, -self->data_1, 0);
}

struct Buff* JiBenBianFaBuff_Get(unsigned int data)
{
  JiBenBianFaInfo.data_1 = data;
  return &JiBenBianFaInfo;
}
