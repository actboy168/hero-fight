#include "../Buff_private.h"

void DuanJinShi_Buff_Start(struct Buff* self, struct BuffList* list);
void DuanJinShi_Buff_Stop(struct Buff* self, struct BuffList* list);

const char DuanJinShi_startStr[] = ("%s的速度被降低了。");
const char DuanJinShi_stopStr[] = ("%s的速度恢复了正常。");

struct Buff DuanJinShiInfo =
{
  DuanJinShi_ID,
  BUFF_TYPE_TIME,
  10.0,
  DuanJinShi_Buff_Start,
  DuanJinShi_Buff_Stop,
  DuanJinShi_startStr,
  DuanJinShi_stopStr
};

void DuanJinShi_Buff_Start(struct Buff* self, struct BuffList* list)
{
  BuffList_Apply_Speed(list, -self->data_1, 1);
}

void DuanJinShi_Buff_Stop(struct Buff* self, struct BuffList* list)
{
  BuffList_Apply_Speed(list,  self->data_1, 0);
}

struct Buff* DuanJinShiBuff_Get(unsigned int level)
{
  DuanJinShiInfo.data_1 = 7+level;
  return &DuanJinShiInfo;
}
