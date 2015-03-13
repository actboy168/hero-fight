#include "../Buff_private.h"

void LieMaShi_Buff_Start(struct Buff* self, struct BuffList* list);
void LieMaShi_Buff_Stop(struct Buff* self, struct BuffList* list);

const char LieMaShi_startStr[] = ("%s眼前冒出了金星，仿佛看不清对手的所在。");
const char LieMaShi_stopStr[] = ("%s摇摇晕沉沉的脑袋，终于恢复了正常。");

struct Buff LieMaShiInfo =
{
  LieMaShi_ID,
  BUFF_TYPE_TIME,
  54.0,
  LieMaShi_Buff_Start,
  LieMaShi_Buff_Stop,
  LieMaShi_startStr,
  LieMaShi_stopStr
};

void LieMaShi_Buff_Start(struct Buff* self, struct BuffList* list)
{
  list->current->attribMZ -= self->data_1;
}

void LieMaShi_Buff_Stop(struct Buff* self, struct BuffList* list)
{
  list->current->attribMZ += self->data_1;
}

struct Buff* LieMaShiBuff_Get(unsigned int level)
{
  LieMaShiInfo.data_1 = level*2;
  return &LieMaShiInfo;
}
