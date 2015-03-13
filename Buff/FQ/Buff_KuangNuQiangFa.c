#include "../Buff_private.h"

void KuangNuQiangFa_Buff_Start(struct Buff* self, struct BuffList* list);
void KuangNuQiangFa_Buff_Stop(struct Buff* self, struct BuffList* list);

const char KuangNuQiangFa_startStr[] = ("%s的皮肤泛起不健康的红晕。");
const char KuangNuQiangFa_stopStr[] = ("%s深吸一口气，皮肤恢复了正常。");

struct Buff KuangNuQiangFaInfo =
{
  KuangNuQiangFa_ID,
  BUFF_TYPE_TIME,
  30.0,
  KuangNuQiangFa_Buff_Start,
  KuangNuQiangFa_Buff_Stop,
  KuangNuQiangFa_startStr,
  KuangNuQiangFa_stopStr
};

void KuangNuQiangFa_Buff_Start(struct Buff* self, struct BuffList* list)
{
  list->current->attribZS += self->data_1;
}

void KuangNuQiangFa_Buff_Stop(struct Buff* self, struct BuffList* list)
{
  list->current->attribZS -= self->data_1;
}

struct Buff* KuangNuQiangFaBuff_Get(unsigned int level)
{
  KuangNuQiangFaInfo.data_1 = 2+level*2;
  return &KuangNuQiangFaInfo;
}
