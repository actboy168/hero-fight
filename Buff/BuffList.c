#include "BuffList.h"
#include "Buff_private.h"
#include "Buff.h"

#include "../Core/Mem.h"
#include "../Core/Output.h"


int BuffList_HaveBuff_inStart(struct BuffList* self, int id)
{
  return (self->entry[id].state == 3);
}

int BuffList_HaveBuff_inStable(struct BuffList* self, int id)
{
  return (self->entry[id].state == 1);
}

int BuffList_HaveBuff(struct BuffList* self, int id)
{
  return ((self->entry[id].state == 1) || (self->entry[id].state == 3));
}

struct Buff* BuffList_GetBuff(struct BuffList* self, int id)
{
  return (&self->entry[id].buff);
}

void BuffList_waitTurn(struct BuffList* self)
{
  self->nextTurn += 1.0;
  self->currTurn += 1.0;
}

void BuffList_setTurn(struct BuffList* self, float turn)
{
  self->nextTurn = turn;
  self->currTurn = 0.0;
}

int BuffList_Turn(struct BuffList* self, int time)
{
  self->time = time;

  if (self->nextTurn <= (float)time)
  {
    self->currTurn = self->nextTurn;
    self->nextTurn += self->current->speed;
    return 1;
  }
  else
  {
    return 0;
  }
}

int BuffList_Add(struct BuffList* self, struct Buff* buff)
{
  struct BuffNode* p;

  if (buff == NULL) return 0;

  if (buff->id < 0 || buff->id >= BUFF_MAX_NUM) return 0;

  p = &self->entry[buff->id];

  if (p->state == 0)
  {
    memcpy(&p->buff, buff, sizeof(struct Buff));
    p->state = 3;
    p->next = self->head.next;
    self->head.next = p;
    p->buff.start(&p->buff, self);
  }
  else if (p->state == 2)
  {
    memcpy(&p->buff, buff, sizeof(struct Buff));
    p->state = 1;
    p->buff.start(&p->buff, self);
  }
  else if (p->state == 1)
  {
    p->buff.stop(&p->buff, self);
    memcpy(&p->buff, buff, sizeof(struct Buff));
    p->buff.start(&p->buff, self);
  }
  else
  {
    memcpy(&p->buff, buff, sizeof(struct Buff));
  }

  return 1;
}

int buff_timeout(float* dur, int KangXing)
{
  if (KangXing>=100)
  {
    *dur = 0.0;
  }
  else if (*dur >= 0.0)
  {
    *dur -= (float)(1.0/(1.0-(float)KangXing/(float)100.0));
  }

  if (*dur < 0.0)
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

void BuffList_Timeout(struct BuffList* self)
{
  struct BuffNode* par = &self->head;
  struct BuffNode* son = par->next;

  while (son != 0)
  {
    if (BUFF_TYPE_TIME == son->buff.type && son->state == 1)
    {
      if (buff_timeout(&son->buff.dur, self->current->attribKX))
      {
        son->state = 2;
        son->buff.stop(&son->buff, self);
      }
    }

    par = son;
    son = par->next;
  }
}

void BuffList_Turnout(struct BuffList* self)
{
  struct BuffNode* par = &self->head;
  struct BuffNode* son = par->next;

  while (son != 0)
  {
    if (BUFF_TYPE_TURN == son->buff.type)
    {
      if (son->buff.dur <= 0.0)
      {
        son->state = 2;
        son->buff.stop(&son->buff, self);
      }
      else
      {
        son->buff.dur -= 1.0;
      }
    }

    par = son;
    son = par->next;
  }
}

void BuffList_OutStartString(struct BuffList* self)
{
  struct BuffNode* par = &self->head;
  struct BuffNode* son = par->next;

  while (son != 0)
  {
    if (son->state == 3)
    {
      son->state = 1;

      if (son->buff.startStr != NULL)
      {
        Output_BuffInfo(son->buff.startStr, self->name);
      }
    }

    par = son;
    son = par->next;
  }
}

void BuffList_Clear(struct BuffList* self)
{
  struct BuffNode* par = &self->head;
  struct BuffNode* son = par->next;

  while (son != 0)
  {
    if (son->state == 2)
    {
      par->next = son->next;
      son->state = 0;

      if (son->buff.stopStr != NULL)
      {
        Output_BuffInfo(son->buff.stopStr, self->name);
      }

      son = par->next;
    }
    else
    {
      par = son;
      son = par->next;
    }
  }
}

int BuffList_needClear(struct BuffList* self)
{
  struct BuffNode* par = &self->head;
  struct BuffNode* son = par->next;

  while (son != 0)
  {
    if ((son->state == 2) && (son->buff.stopStr != NULL))
    {
      return 1;
    }
    else
    {
      par = son;
      son = par->next;
    }
  }

  return 0;
}

struct BuffList* BuffList_Create(const char* name, struct HeroInfo* info, struct HeroInfo* current)
{
  struct BuffList* self = Mem_new(self, struct BuffList);

  memset(self, 0, sizeof(struct BuffList));

  self->name = name;
  self->info = info;
  self->current = current;

  return self;
}

void BuffList_Destroy(struct BuffList* self)
{
  Mem_delete(self);
}

void BuffList_Reset(struct BuffList* self)
{
  struct HeroInfo* bak_info, *bak_current;
  const char* bak_name;

  bak_name = self->name;
  bak_info = self->info;
  bak_current = self->current;


  memset(self, 0, sizeof(struct BuffList));

  self->name = bak_name;
  self->info = bak_info;
  self->current = bak_current;
}

void BuffList_Apply_Attack(struct BuffList* list, int abilityChangeValue, int buffChangeValue)
{
  list->ability_attack_mul += abilityChangeValue;
  list->buff_attack_mul += buffChangeValue;
  list->current->minAttack = (int)((float)list->info->minAttack * (1.0+(float)list->ability_attack_mul/(float)100.0) * (1.0+(float)list->buff_attack_mul/(float)100.0));
  list->current->maxAttack = (int)((float)list->info->maxAttack * (1.0+(float)list->ability_attack_mul/(float)100.0) * (1.0+(float)list->buff_attack_mul/(float)100.0));
}

void BuffList_Apply_Defend(struct BuffList* list, int mulChangeValue, int addChangeValue)
{
  list->defend_mul += mulChangeValue;
  list->defend_add += addChangeValue;
  list->current->def = (int)((float)(list->info->def + list->defend_add) * (1.0+(float)list->defend_mul/(float)100.0));
}

void BuffList_Apply_Speed(struct BuffList* list, int mulChangeValue, int isStart)
{
  list->speed_mul += mulChangeValue;
  list->current->speed = list->info->speed / ((float)1.0 + (float)list->speed_mul/(float)100.0);

  if (isStart)
  {
    float remain = ((float)1.0 - ((float)list->time - list->currTurn) / (list->nextTurn - list->currTurn));

    list->nextTurn = (float)list->time + list->current->speed * remain;
  }
}

void BuffList_SetDuanChangDot(struct BuffList* self)
{
  DuanChangBuff_SetDot(self);
}
