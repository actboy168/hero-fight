#include "../Buff_private.h"

//=======================================================================
// 加攻
//=======================================================================
void HuiMaQiangA_Buff_Start(struct Buff* self, struct BuffList* list);
void HuiMaQiangA_Buff_Stop(struct Buff* self, struct BuffList* list);

struct Buff HuiMaQiangAInfo =
{
  HuiMaQiangA_ID,
  BUFF_TYPE_TURN,
  1.0,
  HuiMaQiangA_Buff_Start,
  HuiMaQiangA_Buff_Stop,
  NULL,
  NULL
};

void HuiMaQiangA_Buff_Start(struct Buff* self, struct BuffList* list)
{
  BuffList_Apply_Attack(list, self->data_1, 0);
}

void HuiMaQiangA_Buff_Stop(struct Buff* self, struct BuffList* list)
{
  BuffList_Apply_Attack(list, -self->data_1, 0);
}

struct Buff* HuiMaQiangABuff_Get(unsigned int level)
{
  HuiMaQiangAInfo.data_1 = level * 14 + 128;

  return &HuiMaQiangAInfo;
}

int HuiMaQiangA_GetID()
{
  return HuiMaQiangA_ID;
}

//=======================================================================
// 减防
//=======================================================================
void HuiMaQiangB_Buff_Start(struct Buff* self, struct BuffList* list);
void HuiMaQiangB_Buff_Stop(struct Buff* self, struct BuffList* list);

struct Buff HuiMaQiangBInfo =
{
  HuiMaQiangB_ID,
  BUFF_TYPE_TURN,
  2.0,
  HuiMaQiangB_Buff_Start,
  HuiMaQiangB_Buff_Stop,
  NULL,
  NULL
};

void HuiMaQiangB_Buff_Start(struct Buff* self, struct BuffList* list)
{
  BuffList_Apply_Defend(list, 0, self->data_1);
}

void HuiMaQiangB_Buff_Stop(struct Buff* self, struct BuffList* list)
{
  BuffList_Apply_Defend(list, 0, -self->data_1);
}

struct Buff* HuiMaQiangBBuff_Get(unsigned int level)
{
  HuiMaQiangBInfo.data_1 = (-1)*(level*45+450);

  return &HuiMaQiangBInfo;
}
