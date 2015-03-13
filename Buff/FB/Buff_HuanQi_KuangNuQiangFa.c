#include "../Buff_private.h"

void HuanQi_KuangNuQiangFa_Buff_Start(struct Buff* self, struct BuffList* list);
void HuanQi_KuangNuQiangFa_Buff_Stop(struct Buff* self, struct BuffList* list);

struct Buff HuanQi_KuangNuQiangFaInfo =
{
  HuanQi_KuangNuQiangFa_ID,
  BUFF_TYPE_TIME,
  40.0,
  HuanQi_KuangNuQiangFa_Buff_Start,
  HuanQi_KuangNuQiangFa_Buff_Stop,
  NULL,
  NULL
};

void HuanQi_KuangNuQiangFa_Buff_Start(struct Buff* self, struct BuffList* list)
{
  list->current->attribZS += 200;
}

void HuanQi_KuangNuQiangFa_Buff_Stop(struct Buff* self, struct BuffList* list)
{
  list->current->attribZS -= 200;
}

struct Buff* HuanQi_KuangNuQiangFaBuff_Get(unsigned int level)
{
  return &HuanQi_KuangNuQiangFaInfo;
}
