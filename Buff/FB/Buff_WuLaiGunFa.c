#include "../Buff_private.h"

void WuLaiGunFa_Buff_Start(struct Buff* self, struct BuffList* list);
void WuLaiGunFa_Buff_Stop(struct Buff* self, struct BuffList* list);

struct Buff WuLaiGunFaInfo =
{
  WuLaiGunFa_ID,
  BUFF_TYPE_TIME,
  10.0,
  WuLaiGunFa_Buff_Start,
  WuLaiGunFa_Buff_Stop,
  NULL,
  NULL
};

void WuLaiGunFa_Buff_Start(struct Buff* self, struct BuffList* list)
{
  list->current->m_mot += 2;
}

void WuLaiGunFa_Buff_Stop(struct Buff* self, struct BuffList* list)
{
  list->current->m_mot -= 2;
}

struct Buff* WuLaiGunFaBuff_Get(unsigned int level)
{
  return &WuLaiGunFaInfo;
}
