#include "../Buff_private.h"

void DingShenShi_Buff_Start(struct Buff* self, struct BuffList* list);
void DingShenShi_Buff_Stop(struct Buff* self, struct BuffList* list);

const char DingShenShi_startStr[] = ("%s感觉身体似乎不受控制般，再也不复先前的灵活。");
const char DingShenShi_stopStr[] = ("%s的身体恢复了正常，灵活依旧。");

struct Buff DingShenShiInfo =
{
  DingShenShi_ID,
  BUFF_TYPE_TURN,
  1.0,
  DingShenShi_Buff_Start,
  DingShenShi_Buff_Stop,
  DingShenShi_startStr,
  DingShenShi_stopStr
};

void DingShenShi_Buff_Start(struct Buff* self, struct BuffList* list)
{
  list->current->attribSB -= self->data_1;
}

void DingShenShi_Buff_Stop(struct Buff* self, struct BuffList* list)
{
  list->current->attribSB += self->data_1;
}

int DingShenShi_sub_ShanBi(int level)
{
  int shanbi = 0;
  switch(level)
  {
  case  0:shanbi = 0;break;
  case  1:shanbi = 1;break;
  case  2:shanbi = 2;break;
  case  3:shanbi = 3;break;
  case  4:shanbi = 5;break;
  case  5:shanbi = 6;break;
  case  6:shanbi = 8;break;
  case  7:shanbi = 9;break;
  case  8:shanbi = 11;break;
  case  9:shanbi = 12;break;
  case 10:shanbi = 14;break;
  case 11:shanbi = 15;break;
  case 12:shanbi = 17;break;
  case 13:shanbi = 18;break;
  case 14:shanbi = 20;break;
  case 15:shanbi = 21;break;
  case 16:shanbi = 23;break;
  case 17:shanbi = 24;break;
  case 18:shanbi = 26;break;
  case 19:shanbi = 28;break;
  case 20:shanbi = 30;break;
  case 21:shanbi = 31;break;
  case 22:shanbi = 33;break;
  case 23:shanbi = 35;break;
  case 24:shanbi = 36;break;
  case 36:shanbi = 57;break;
  default:
    shanbi = (int)(1.75*level-6.0);
    break;
  }
  return shanbi;
}

struct Buff* DingShenShiBuff_Get(unsigned int level)
{
  DingShenShiInfo.data_1 = DingShenShi_sub_ShanBi(level);
  DingShenShiInfo.dur = (float)(1+(level+6)/10);

  return &DingShenShiInfo;
}
