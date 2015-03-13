#include "../Buff_private.h"

void JieMai_Buff_Start(struct Buff* self, struct BuffList* list);
void JieMai_Buff_Stop(struct Buff* self, struct BuffList* list);

struct Buff JieMaiInfo =
{
  JieMai_ID,
  BUFF_TYPE_TURN,
  1.0,
  JieMai_Buff_Start,
  JieMai_Buff_Stop,
  NULL,
  NULL
};

void JieMai_Buff_Start(struct Buff* self, struct BuffList* list)
{
  list->current->attribKX += self->data_1;
}

void JieMai_Buff_Stop(struct Buff* self, struct BuffList* list)
{
  list->current->attribKX -= self->data_1;
}

struct Buff* JieMaiBuff_Get(unsigned int level)
{
  JieMaiInfo.data_1 = ((level<9)? level*10: 90);

  return &JieMaiInfo;
}
