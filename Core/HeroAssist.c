#include "HeroAssist.h"

#include "Hero.h"
#include "HeroInfo.h"
#include "Output.h"
#include "Mem.h"

struct HeroAssist
{
  struct Hero* hero;

  int totalCS;
  int totalMZ;
  int totalBJ;
  int totalPJ;
  int totalBP;

  //攻击溢出
  int overflowAtk;
  int overflowAtk_last;
  int overflowAtk_n;
  //气血溢出
  int overflowHP;
  int overflowHP_n;
};

struct HeroAssist HA;
struct HeroAssist HB;

int Assist_enable = 1;

#define CHECK do { if (!Assist_enable) return;} while(0)

int HeroAssist_SetEnable(int e)
{
  return (Assist_enable = e);
}

void HeroAssist_SetHero(struct Hero* A, struct Hero* B)
{
  CHECK;

  memset(&HA, 0, sizeof(struct HeroAssist));
  memset(&HB, 0, sizeof(struct HeroAssist));

  HA.hero = A;
  HB.hero = B;
}

void HeroAssist_Display_One(struct HeroAssist* H)
{
  Output_print(("\n"));
  Output_print(("%8s 平均命中率: %0.2f%%\n"), Hero_Name(H->hero), (H->totalCS==0?(float)0.0:H->totalMZ/(float)H->totalCS*(float)100.0));
  Output_print(("%8s 平均暴击率: %0.2f%%\n"), Hero_Name(H->hero), (H->totalMZ==0?(float)0.0:H->totalBJ/(float)H->totalMZ*(float)100.0));
  Output_print(("%8s 平均破击率: %0.2f%%\n"), Hero_Name(H->hero), (H->totalMZ==0?(float)0.0:H->totalPJ/(float)H->totalMZ*(float)100.0));
  Output_print(("%8s 平均暴破率: %0.2f%%\n"), Hero_Name(H->hero), (H->totalMZ==0?(float)0.0:H->totalBP/(float)H->totalMZ*(float)100.0));

  Output_print(("%8s 平均攻击溢出量: %4.2f\n"), Hero_Name(H->hero), (H->overflowAtk_n==0?(float)0.0:H->overflowAtk/(float)H->overflowAtk_n));
  Output_print(("%8s 本次攻击溢出量: %d\n"), Hero_Name(H->hero), H->overflowAtk_last);
  Output_print(("%8s 平均气血溢出量: %4.2f\n"), Hero_Name(H->hero), (H->overflowHP_n==0?(float)0.0:H->overflowHP/(float)H->overflowHP_n));

  if (Hero_GetAbilityCount(H->hero) != 0)
  {
    Output_print(("%8s %s发动次数: %d\n"), Hero_Name(H->hero), Hero_GetAbilityName(H->hero), Hero_GetAbilityCount(H->hero));
  }
}

void HeroAssist_Display()
{
  CHECK;

  Output_print(("\n\n"));
  Output_print(("【详细战斗统计】:\n"));
  HeroAssist_Display_One(&HA);
  HeroAssist_Display_One(&HB);
}

void HeroAssist_SetOverflow(struct Hero* loser, int overflow)
{
  CHECK;

  if (loser == HB.hero)
  {
    HA.overflowAtk_n++;
    HA.overflowAtk += overflow;
    HA.overflowAtk_last = overflow;
    HB.overflowAtk_last = 0;

    HA.overflowHP_n++;
  }
  else if (loser == HA.hero)
  {
    HB.overflowAtk_n++;
    HB.overflowAtk += overflow;
    HB.overflowAtk_last = overflow;
    HA.overflowAtk_last = 0;

    HB.overflowHP_n++;
  }
  else
  {
    HA.overflowHP_n++;
    HB.overflowHP_n++;
  }

  HA.overflowHP += Hero_Info(HA.hero)->HP;
  HA.totalCS += Hero_GetCS(HA.hero);
  HA.totalMZ += Hero_GetMZ(HA.hero);
  HA.totalBJ += Hero_GetBJ(HA.hero);
  HA.totalPJ += Hero_GetPJ(HA.hero);
  HA.totalBP += Hero_GetBP(HA.hero);

  HB.overflowHP += Hero_Info(HB.hero)->HP;
  HB.totalCS += Hero_GetCS(HB.hero);
  HB.totalMZ += Hero_GetMZ(HB.hero);
  HB.totalBJ += Hero_GetBJ(HB.hero);
  HB.totalPJ += Hero_GetPJ(HB.hero);
  HB.totalBP += Hero_GetBP(HB.hero);
}

#undef CHECK
