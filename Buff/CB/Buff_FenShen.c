#include "../Buff_private.h"

void FenShen_Buff_Start(struct Buff* self, struct BuffList* list);
void FenShen_Buff_Stop(struct Buff* self, struct BuffList* list);

const char FenShen_startStr[] = ("%s的身影彷佛变成了三个，让人分不清真身所在。");
const char FenShen_stopStr[] = ("%s的身影慢了下来。");

struct Buff FenShenInfo =
{
  FenShen_ID,
  BUFF_TYPE_TIME,
  15.0,
  FenShen_Buff_Start,
  FenShen_Buff_Stop,
  FenShen_startStr,
  FenShen_stopStr
};

void FenShen_Buff_Start(struct Buff* self, struct BuffList* list)
{
  list->current->attribJM += self->data_1;
}

void FenShen_Buff_Stop(struct Buff* self, struct BuffList* list)
{
  list->current->attribJM -= self->data_1;
}

struct Buff* FenShenBuff_Get(unsigned int level)
{
  FenShenInfo.data_1 = 16+level*2;
  return &FenShenInfo;
}
