#include "../Buff_private.h"

void LongJuanQiangFa_Buff_Start(struct Buff* self, struct BuffList* list);
void LongJuanQiangFa_Buff_Stop(struct Buff* self, struct BuffList* list);

const char LongJuanQiangFa_startStr[] = ("%s只觉手臂肌肉抽痛，虎口发麻，使不上力。");
const char LongJuanQiangFa_stopStr[] = ("%s活动活动手腕，又恢复了力量。");

struct Buff LongJuanQiangFaInfo =
{
  LongJuanQiangFa_ID,
  BUFF_TYPE_TURN,
  1.0,
  LongJuanQiangFa_Buff_Start,
  LongJuanQiangFa_Buff_Stop,
  LongJuanQiangFa_startStr,
  LongJuanQiangFa_stopStr
};

void LongJuanQiangFa_Buff_Start(struct Buff* self, struct BuffList* list)
{
  BuffList_Apply_Attack(list, 0, self->data_1);
}

void LongJuanQiangFa_Buff_Stop(struct Buff* self, struct BuffList* list)
{
  BuffList_Apply_Attack(list, 0, -self->data_1);
}

struct Buff* LongJuanQiangFaBuff_Get(unsigned int level)
{
  int deattack = 0;

  if (level <= 8)
    deattack = -9 - level * 1;
  else if (level <= 11)
    deattack = -6 - level * 2;
  else if (level == 12)
    deattack = -30;
  else if (level == 13)
    deattack = -33;
  else if (level == 14)
    deattack = -36;
  else if (level == 15)
    deattack = -40;
  else if (level == 16)
    deattack = -45;
  else if (level >= 17)
    deattack = -52;

  LongJuanQiangFaInfo.data_1 = deattack;

  return &LongJuanQiangFaInfo;
}
