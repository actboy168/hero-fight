#include "../Buff_private.h"

void HanBingJianFa_Buff_Start(struct Buff* self, struct BuffList* list);
void HanBingJianFa_Buff_Stop(struct Buff* self, struct BuffList* list);

const char HanBingJianFa_startStr[] = ("%s的速度被降低了。");
const char HanBingJianFa_stopStr[] = ("%s的速度恢复了正常。");

struct Buff HanBingJianFaInfo =
{
  HanBingJianFa_ID,
  BUFF_TYPE_TIME,
  15.0,
  HanBingJianFa_Buff_Start,
  HanBingJianFa_Buff_Stop,
  HanBingJianFa_startStr,
  HanBingJianFa_stopStr
};

void HanBingJianFa_Buff_Start(struct Buff* self, struct BuffList* list)
{
  BuffList_Apply_Speed(list, -20, 1);
}

void HanBingJianFa_Buff_Stop(struct Buff* self, struct BuffList* list)
{
  BuffList_Apply_Speed(list,  20, 0);
}

struct Buff* HanBingJianFaBuff_Get(unsigned int level)
{
  return &HanBingJianFaInfo;
}
