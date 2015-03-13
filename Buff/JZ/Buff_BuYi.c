#include "../Buff_private.h"

void BuYi_Buff_Start(struct Buff* self, struct BuffList* list);
void BuYi_Buff_Stop(struct Buff* self, struct BuffList* list);

const char BuYi_startStr[] = ("%s暗运一口内息护住全身，罡气四散，凛然不侵！");
const char BuYi_stopStr[] = ("%s内息在全身流传一周天后沉入丹田。");

struct Buff BuYiInfo =
{
  BuYi_ID,
  BUFF_TYPE_TURN,
  1,
  BuYi_Buff_Start,
  BuYi_Buff_Stop,
  BuYi_startStr,
  BuYi_stopStr
};

void BuYi_Buff_Start(struct Buff* self, struct BuffList* list)
{
  list->current->attribFT += 15;
}

void BuYi_Buff_Stop(struct Buff* self, struct BuffList* list)
{
  list->current->attribFT -= 15;
}

struct Buff* BuYiBuff_Get()
{
  return &BuYiInfo;
}
