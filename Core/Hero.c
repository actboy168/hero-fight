#include "Hero.h"

#include "Config.h"
#include "Mem.h"
#include "HeroHelper.h"
#include "HeroInfo.h"
#include "HeroState.h"
#include "HeroAssist.h"
#include "Output.h"
#include "miniCRT.h"
#include "../Ability/Ability.h"
#include "../Buff/BuffList.h"
#include "../Buff/Buff.h"
#include "../Attach/AttachBuff.h"
#include "../Attach/AttachAbility.h"

struct Hero
{
  ASHANDLE hFile;

  int Lv;
  const char* name;

  struct Ability* ability;
  struct BuffList* buff_list;
  struct AttachBuff* attachBuff;
  struct HeroState* state;
  struct HeroInfo info;
  struct HeroInfo current;
};

struct Hero* Hero_Create(const char* pInputFileName)
{
  struct Hero* self = Mem_new(self, struct Hero);
  memset(self, 0, sizeof(struct Hero));

  self->hFile = ASFileOpen(pInputFileName);

  //读取英雄名字、武器名字和等级
  self->name   = ASFileGetHeroName(self->hFile);
  self->Lv     = ASFileGetHeroLevel(self->hFile);

  //读取属性信息
  HeroInfo_Load(&self->info, self->hFile);
  memcpy(&self->current, &self->info, sizeof(struct HeroInfo));

  //读取主动技能
  self->ability = Ability_Create(self, self->hFile);

  //初始化附加buff系统（“淬毒匕首”“伏虎势”“裂马势”等）
  self->attachBuff = AttachBuff_Create();

  //初始化buff系统
  self->buff_list = BuffList_Create(self->name, &self->info, &self->current);

  //初始化状态参数
  self->state = HeroState_Create();

  //读取辅助技能和被动技能
  AttachAbility_Load(self, self->hFile);

  return self;
}

void Hero_Destroy(struct Hero* self)
{
  Ability_Destroy(self->ability);
  HeroState_Destroy(self->state);
  BuffList_Destroy(self->buff_list);
  ASFileClose(self->hFile);
  Mem_delete(self);
}

void Hero_Reset(struct Hero* self)
{
  HeroState_Reset(self->state);
  BuffList_Reset(self->buff_list);

  memcpy(&self->current, &self->info, sizeof(struct HeroInfo));
}

int Hero_Turn(struct Hero* self, int time)
{
  if(self->current.dizzy & 1)
  {
    self->current.dizzy |= 2;
    BuffList_waitTurn(self->buff_list);
    return 0;
  }
  else
  {
    self->current.dizzy &= ~2;
    return BuffList_Turn(self->buff_list, time);
  }
}

static void Hero_OutputResult(struct Hero* winner, struct Hero* loser)
{
  Output_result(winner->name, winner->current.HP, winner->info.HP, loser->name, loser->current.HP, loser->info.HP);
}

static void Hero_Statistics(struct Hero* A, struct Hero* B)
{
  Output_print(("\n"));
  Output_print(("< %s >     战斗统计     < %s >\n"), A->name, B->name);
  Output_print(("攻击[ %2d ]  命中[ %2d ]   [ %2d ]攻击  [ %2d ]命中\n"), HeroState_GetCS(A->state), HeroState_GetMZ(A->state), HeroState_GetCS(B->state), HeroState_GetMZ(B->state));
  Output_print(("暴击[ %2d ]  破击[ %2d ]   [ %2d ]暴击  [ %2d ]破击\n"), HeroState_GetBJ(A->state), HeroState_GetPJ(A->state), HeroState_GetBJ(B->state), HeroState_GetPJ(B->state));
}

static void Hero_OutputState(struct Hero* self)
{
  Output_print(("\n"));
  Output_print(("%s Lv.%d\n"), self->name, self->Lv);
  Output_print(("技能： %s Lv.%d\n"), Ability_GetName(self->ability), Ability_GetLevel(self->ability));
  Output_print(("气血： %4d / %4d\n"), self->current.HP, self->current.maxHP);
  Output_print(("内息： %4d / %4d\n"), self->current.MP, self->current.maxMP);
  Output_print(("命中  +%2d%% 躲闪 %2d%%\n"), self->info.attribMZ-95, self->info.attribSB);
  Output_print(("暴击   %2d%% 破击 %2d%%\n"), self->info.attribBJ, self->info.attribPJ);
  Output_print(("攻击： %3d - %3d\n"), self->info.minAttack, self->info.maxAttack);
  Output_print(("防御： %d\n"), self->info.def);
}

int Hero_Timer(struct Hero* self)
{
  if (self->current.HP <= 0) return 0;

  //持续掉血
  if (self->current.m_sum_dot > 0)
  {
    int dot = self->current.m_dot_a + self->current.m_dot_b;
    if (self->current.HP > dot)
    {
      self->current.HP -= dot;
    }
    else
    {
      if (self->current.HP != 0)
      {
        int overflow = dot - self->current.HP;
        self->current.HP = 0;
        HeroAssist_SetOverflow(self, overflow);
      }

      return 0;
    }
  }

  //持续扣魔(百分比)
  if (self->current.m_mot > 0)
  {
    int mp = (self->current.m_mot * self->info.MP / 100);

    if (self->current.MP > mp)
    {
      self->current.MP -= mp;
    }
    else
    {
      self->current.MP = 0;
    }
  }

  return 1;
}

int Hero_Attack(struct Hero* attacker, struct Hero* target)
{
  unsigned int nRet = 0;

  if (attacker->current.HP <= 0)
  {
    nRet = 0x02;
  }
  else if (target->current.HP <= 0)
  {
    return 0;
  }
  else
  {
    BuffList_Turnout(attacker->buff_list);
    BuffList_Clear(attacker->buff_list);
    Output_Damage_begin();

    nRet |= Ability_Attack(attacker->ability, attacker, target);

    Output_Damage_end();

    BuffList_OutStartString(attacker->buff_list);
    BuffList_OutStartString(target->buff_list);
  }

  if (nRet & 0x02)
  {
    Output_print(("\n%s受伤过重，已经奄奄一息，命在旦夕了。\n\n"), attacker->name);
  }

  if (nRet & 0x01)
  {
    Output_print(("\n%s受伤过重，已经奄奄一息，命在旦夕了。\n\n"), target->name);
  }

  if (nRet == 0x03)
  {
    return 1;
  }
  else
  {
    return nRet;
  }
}

void Hero_StartFight(struct Hero* A, struct Hero* B)
{
  // 设置等级压制修正系数
  HeroState_setFix(A->state, A->Lv - B->Lv);
  HeroState_setFix(B->state, B->Lv - A->Lv);

  // 初始化下次出手时间
  BuffList_setTurn(A->buff_list, A->current.speed);
  BuffList_setTurn(B->buff_list, B->current.speed);
}

void Hero_showInDizzy(struct Hero* H, int time)
{
  if ((H->current.dizzy & 2) && BuffList_needClear(H->buff_list))
  {
    Output_print(("第 %d 秒\n"), time);
    BuffList_Clear(H->buff_list);
  }
}

int Hero_Fight(struct Hero* A, struct Hero* B)
{
  int nRet = 0;

  unsigned int time;
  int booA, booB;

  Hero_Reset(A);
  Hero_Reset(B);

  Hero_StartFight(A, B);

  Output_print(("%s vs %s\n\n"), A->name, B->name);

  for (time = 1; time <= Main_time; time++)
  {
    BuffList_Timeout(A->buff_list);
    BuffList_Timeout(B->buff_list);

    if (time % 10 == 1)
    {
      BuffList_SetDuanChangDot(A->buff_list);
      BuffList_SetDuanChangDot(B->buff_list);
    }

    Hero_Timer(A);
    Hero_Timer(B);

    Hero_showInDizzy(A, time);
    Hero_showInDizzy(B, time);

    booA = Hero_Turn(A, time);
    booB = Hero_Turn(B, time);

    if (booA || booB)
    {
      Output_print(("第 %d 秒\n"), time);
      if (booA&&booB)
      {
        if (Crt_GetRandomPercent(50))
        {
          if (0 != (nRet = Hero_Attack(A, B))) break;
          if (0 != (nRet = Hero_Attack(B, A))) { nRet = 3 - nRet; break;}
        }
        else
        {
          if (0 != (nRet = Hero_Attack(B, A))) { nRet = 3 - nRet; break;}
          if (0 != (nRet = Hero_Attack(A, B))) break;
        }
      }
      else if (booA)
      {
        if (0 != (nRet = Hero_Attack(A, B))) break;
      }
      else if (booB)
      {
        if (0 != (nRet = Hero_Attack(B, A))) { nRet = 3 - nRet; break;}
      }
    }
  }

  if (time == Main_time+1)
  {
    HeroAssist_SetOverflow(NULL, 0);

    Output_print(("第 %d 秒\n"), Main_time+1);
    Output_print(("双方体力不济，都没有了再战的欲望。\n"));

    if (Main_FBmode == 1)
    {
      nRet = 2;
    }
    else if ((A->current.HP*B->info.HP) > (B->current.HP*A->info.HP))
    {
      nRet = 1;
    }
    else
    {
      nRet = 2;
    }
  }
  else
  {
    Output_print(("\n\n"));
    Output_print(("%s已没有了再战之力。\n"), ((nRet == 2)? A->name: B->name));
  }

  if (nRet == 1)
  {
    if (Output_IsEnable())
    {
      Hero_OutputResult(A, B);
      Hero_Statistics(A, B);
      Hero_OutputState(A);
      Hero_OutputState(B);
    }
    return 1;
  }
  else if (nRet == 2)
  {
    if (Output_IsEnable())
    {
      Hero_OutputResult(B, A);
      Hero_Statistics(A, B);
      Hero_OutputState(A);
      Hero_OutputState(B);
    }
    return 2;
  }

  return 0;
}

int Hero_init()
{
  return Ability_init();
}

int Hero_AddBuff(struct Hero* self, struct Buff* buff)
{
  return BuffList_Add(self->buff_list, buff);
}

int Hero_isMingZhong(struct Hero* attacker, struct Hero* target, int flag)
{
  return HeroState_isMingZhong(attacker->state, attacker->current.attribMZ,  target->current.attribSB, flag, !BuffList_HaveBuff_inStart(attacker->buff_list, HuiMaQiangA_GetID()));
}

int Hero_isBJAndPJ(struct Hero* attacker, struct Hero* target, int flag)
{
  return HeroState_isBJAndPJ(attacker->state, attacker->current.attribBJ, target->current.attribKB, attacker->current.attribPJ, target->current.attribKP, flag, !BuffList_HaveBuff_inStart(attacker->buff_list, HuiMaQiangA_GetID()));
}

int Hero_checkAbilityRandom(struct Hero* attacker, int AR)
{
  return HeroState_checkAbilityRandom(attacker->state, AR, 0, !BuffList_HaveBuff_inStart(attacker->buff_list, HuiMaQiangA_GetID()));
}

int Hero_GetCS(struct Hero* self)
{
  return HeroState_GetCS(self->state);
}

int Hero_GetMZ(struct Hero* self)
{
  return HeroState_GetMZ(self->state);
}

int Hero_GetBJ(struct Hero* self)
{
  return HeroState_GetBJ(self->state);
}

int Hero_GetPJ(struct Hero* self)
{
  return HeroState_GetPJ(self->state);
}

int Hero_GetBP(struct Hero* self)
{
  return HeroState_GetBP(self->state);
}

int Hero_GetAbilityCount(struct Hero* self)
{
  return HeroState_GetAbilityCount(self->state);
}

void Hero_AttachBuff(struct Hero* attacker, struct Hero* target)
{
  AttachBuff_Run(attacker->attachBuff, target);
}

void Hero_SetAttachBuff(struct Hero* self, int lv, void* getBuff)
{
  AttachBuff_Set(self->attachBuff, lv, getBuff);
}

int Hero_HaveBuff(struct Hero* self, int id)
{
  return BuffList_HaveBuff(self->buff_list, id);
}

int Hero_HaveBuff_inStable(struct Hero* self, int id)
{
  return BuffList_HaveBuff_inStable(self->buff_list, id);
}

int Hero_HaveBuff_inStart(struct Hero* self, int id)
{
  return BuffList_HaveBuff_inStart(self->buff_list, id);
}

char* Hero_GetAbilityName(struct Hero* self)
{
  return Ability_GetName(self->ability);
}

const char* Hero_Name(struct Hero* self)
{
  return self->name;
}

struct HeroInfo* Hero_Info(struct Hero* self)
{
  return &self->current;
}

struct HeroInfo* Hero_InfoEx(struct Hero* self)
{
  return &self->info;
}

struct BuffList* Hero_BuffList(struct Hero* self)
{
  return self->buff_list;
}

int Hero_GetAbility_AntiBX(struct Hero* self)
{
  return Ability_GetFeatures(self->ability, ABILITY_FEATURES_ANTIBX);
}

int Hero_GetAbility_AntiFT(struct Hero* self)
{
  return Ability_GetFeatures(self->ability, ABILITY_FEATURES_ANTIFT);
}

int Hero_GetAbility_AntiFY(struct Hero* self)
{
  return Ability_GetFeatures(self->ability, ABILITY_FEATURES_ANTIFY);
}


