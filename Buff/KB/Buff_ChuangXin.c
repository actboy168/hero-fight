#include "../Buff_private.h"

#include "../BuffList.h"

//=======================================================================
// 眩晕
//=======================================================================
void ChuangXinA_Buff_Start(struct Buff* self, struct BuffList* list);
void ChuangXinA_Buff_Stop(struct Buff* self, struct BuffList* list);

const char ChuangXinA_startStr[] = ("%s头昏脑涨，已不辨东西南北。");
const char ChuangXinA_stopStr[] = ("%s头脑逐渐清醒了过来。");

struct Buff ChuangXinAInfo =
{
  ChuangXinA_ID,
  BUFF_TYPE_TIME,
  10.0,
  ChuangXinA_Buff_Start,
  ChuangXinA_Buff_Stop,
  ChuangXinA_startStr,
  ChuangXinA_stopStr
};

void ChuangXinA_Buff_Start(struct Buff* self, struct BuffList* list)
{
  list->current->dizzy |= 3;
  BuffList_waitTurn(list);
}

void ChuangXinA_Buff_Stop(struct Buff* self, struct BuffList* list)
{
  list->current->dizzy &= ~1;
}

struct Buff* ChuangXinABuff_Get(unsigned int level)
{
  return &ChuangXinAInfo;
}

//=======================================================================
// 加闪
//=======================================================================
void ChuangXinB_Buff_Start(struct Buff* self, struct BuffList* list);
void ChuangXinB_Buff_Stop(struct Buff* self, struct BuffList* list);

const char ChuangXinB_startStr[] = ("%s的速度提高了");
const char ChuangXinB_stopStr[] = ("%s的速度恢复了正常。");

struct Buff ChuangXinBInfo =
{
  ChuangXinB_ID,
  BUFF_TYPE_TURN,
  1.0,
  ChuangXinB_Buff_Start,
  ChuangXinB_Buff_Stop,
  ChuangXinB_startStr,
  ChuangXinB_stopStr
};

void ChuangXinB_Buff_Start(struct Buff* self, struct BuffList* list)
{
  list->current->attribSB += self->data_1;
}

void ChuangXinB_Buff_Stop(struct Buff* self, struct BuffList* list)
{
  list->current->attribSB -= self->data_1;
}

struct Buff* ChuangXinBBuff_Get(unsigned int level)
{
  ChuangXinBInfo.data_1 = level;
  return &ChuangXinBInfo;
}
