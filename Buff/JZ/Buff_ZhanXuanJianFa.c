#include "../Buff_private.h"

void ZhanXuanJianFa_Buff_Start(struct Buff* self, struct BuffList* list);
void ZhanXuanJianFa_Buff_Stop(struct Buff* self, struct BuffList* list);

struct Buff ZhanXuanJianFaInfo =
{
  ZhanXuanJianFa_ID,
  BUFF_TYPE_TURN,
  2.0,
  ZhanXuanJianFa_Buff_Start,
  ZhanXuanJianFa_Buff_Stop,
  NULL,
  NULL
};

void ZhanXuanJianFa_Buff_Start(struct Buff* self, struct BuffList* list)
{
  list->current->attribBJ += self->data_1;
  list->current->attribPJ += self->data_2;
}

void ZhanXuanJianFa_Buff_Stop(struct Buff* self, struct BuffList* list)
{
  list->current->attribBJ -= self->data_1;
  list->current->attribPJ -= self->data_2;
}

struct Buff* ZhanXuanJianFaBuff_Get(unsigned int bj, unsigned int pj)
{
  ZhanXuanJianFaInfo.data_1 = bj;
  ZhanXuanJianFaInfo.data_2 = pj;

  return &ZhanXuanJianFaInfo;
}
