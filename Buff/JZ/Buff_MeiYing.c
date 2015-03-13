#include "../Buff_private.h"

void MeiYing_Buff_Start(struct Buff* self, struct BuffList* list);
void MeiYing_Buff_Stop(struct Buff* self, struct BuffList* list);

const char MeiYing_startStr[] = ("%s眼前冒出了金星，仿佛看不清对手的所在。");
const char MeiYing_stopStr[] = ("%s摇摇晕沉沉的脑袋，终于恢复了正常。");

struct Buff MeiYingInfo =
{
  MeiYing_ID,
  BUFF_TYPE_TURN,
  1,
  MeiYing_Buff_Start,
  MeiYing_Buff_Stop,
  MeiYing_startStr,
  MeiYing_stopStr
};

void MeiYing_Buff_Start(struct Buff* self, struct BuffList* list)
{
  BuffList_Apply_Attack(list, 0, self->data_2);
  list->current->attribMZ -= self->data_1;
}

void MeiYing_Buff_Stop(struct Buff* self, struct BuffList* list)
{
  BuffList_Apply_Attack(list, 0, -self->data_2);
  list->current->attribMZ += self->data_1;
}

struct Buff* MeiYingBuff_Get(unsigned int level, int attacksub)
{
  MeiYingInfo.data_1 = 3+level;
  MeiYingInfo.data_2 = attacksub;

  return &MeiYingInfo;
}
