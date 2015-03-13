#include "../Buff_private.h"

void KangLongQiangFa_Buff_Start(struct Buff* self, struct BuffList* list);
void KangLongQiangFa_Buff_Stop(struct Buff* self, struct BuffList* list);

const char KangLongQiangFa_startStr[] = ("%s将一杆枪舞的滴水不漏，似乎任何攻击都难以攻破！");
const char KangLongQiangFa_stopStr[] = ("%s枪法逐渐散乱，不再那么无懈可击。");

struct Buff KangLongQiangFaInfo =
{
  KangLongQiangFa_ID,
  BUFF_TYPE_TURN,
  1.0,
  KangLongQiangFa_Buff_Start,
  KangLongQiangFa_Buff_Stop,
  KangLongQiangFa_startStr,
  KangLongQiangFa_stopStr
};

void KangLongQiangFa_Buff_Start(struct Buff* self, struct BuffList* list)
{
  BuffList_Apply_Defend(list, 0, self->data_1);
}

void KangLongQiangFa_Buff_Stop(struct Buff* self, struct BuffList* list)
{
  BuffList_Apply_Defend(list, 0, -self->data_1);
}

struct Buff* KangLongQiangFaBuff_Get(unsigned int level)
{
  KangLongQiangFaInfo.data_1 = level*28+270;

  return &KangLongQiangFaInfo;
}
