#include "HeroWinPer.h"

#include "Hero.h"
#include "HeroHelper.h"
#include "HeroInfo.h"
#include "HeroAssist.h"
#include "Output.h"

extern struct Hero* A;
extern struct Hero* B;

int WinPer_enable = 0;

int HeroWinPer_SetEnable(int e)
{
  return (WinPer_enable = e);
}

unsigned int HeroWinPer_GetWinCount(unsigned int n)
{
  unsigned int i = 0;
  unsigned int Count = 0;

  for (i = 0; i < n; i++)
  {
    if (1 == Hero_Fight(A, B)) Count++;
  }

  return Count;
}

float HeroWinPer_WinPerAndDeviation(unsigned int n, unsigned int m)
{
  unsigned int i;
  float x;
  float s1 = 0.0, s2 = 0.0;

  int e = Output_SetEnable(0);
  if (m <= 1) m = 10;

  for (i = 0; i < m; i++)
  {
    x = (float)HeroWinPer_GetWinCount(n)/(float)n;
    s1 += x;
    s2 += x*x;
  }

  Output_SetEnable(e);
  Output_print("胜率：%.2f%% 平均误差：%.2f%%\n\n", s1/m*(float)100.0, (float)sqrt(fabs((s2-s1*s1/m)/(m-1)/m))*(float)100.0);

  return s1/m;
}

void HeroWinPer_WinPerAndMark(unsigned int n, float WinPer_Base)
{
  float WinPer;

  int e = Output_SetEnable(0);
  WinPer = (float)HeroWinPer_GetWinCount(n) / (float)n;
  Output_SetEnable(e);
  Output_print("胜率：%.2f%% 评分：%.2f\n", WinPer*(float)100.0, (log((WinPer+(float)0.01)/(WinPer_Base+(float)0.01)))*(float)100.0);
}

void HeroWinPer_Main(unsigned int n)
{
  float WinPer_Base = HeroWinPer_WinPerAndDeviation(n, 10);


  if (WinPer_enable)
  {
    HeroAssist_SetEnable(0);
    //--------------------------------------------------------------------------------------
    Hero_InfoEx(A)->attribBJ += 6;
    Output_print("暴击+ 6%% ");HeroWinPer_WinPerAndMark(n, WinPer_Base);
    Hero_InfoEx(A)->attribBJ -= 6;
    //--------------------------------------------------------------------------------------

    //--------------------------------------------------------------------------------------
    Hero_InfoEx(A)->attribPJ += 6;
    Output_print("破击+ 6%% ");HeroWinPer_WinPerAndMark(n, WinPer_Base);
    Hero_InfoEx(A)->attribPJ -= 6;
    //--------------------------------------------------------------------------------------

    //--------------------------------------------------------------------------------------
    Hero_InfoEx(A)->attribSB += 6;
    Output_print("闪避+ 6%% ");HeroWinPer_WinPerAndMark(n, WinPer_Base);
    Hero_InfoEx(A)->attribSB -= 6;
    //--------------------------------------------------------------------------------------

    //--------------------------------------------------------------------------------------
    Hero_InfoEx(A)->attribMZ += 6;
    Output_print("命中+ 6%% ");HeroWinPer_WinPerAndMark(n, WinPer_Base);
    Hero_InfoEx(A)->attribMZ -= 6;
    //--------------------------------------------------------------------------------------

    //--------------------------------------------------------------------------------------
    Hero_InfoEx(A)->attribXX += 4;
    Output_print("吸血+ 4%% ");HeroWinPer_WinPerAndMark(n, WinPer_Base);
    Hero_InfoEx(A)->attribXX -= 4;
    //--------------------------------------------------------------------------------------

    //--------------------------------------------------------------------------------------
    Hero_InfoEx(A)->attribFT += 5;
    Output_print("反弹+ 5%% ");HeroWinPer_WinPerAndMark(n, WinPer_Base);
    Hero_InfoEx(A)->attribFT -= 5;
    //--------------------------------------------------------------------------------------

    //--------------------------------------------------------------------------------------
    Hero_InfoEx(A)->minAttack += 24;
    Hero_InfoEx(A)->maxAttack += 24;
    Output_print("攻击+ 24 ");HeroWinPer_WinPerAndMark(n, WinPer_Base);
    Hero_InfoEx(A)->minAttack -= 24;
    Hero_InfoEx(A)->maxAttack -= 24;
    //--------------------------------------------------------------------------------------

    //--------------------------------------------------------------------------------------
    Hero_InfoEx(A)->maxHP += 276;
    Hero_InfoEx(A)->HP += 276;
    Output_print("气血+216 ");HeroWinPer_WinPerAndMark(n, WinPer_Base);
    Hero_InfoEx(A)->maxHP -= 276;
    Hero_InfoEx(A)->HP -= 276;
    //--------------------------------------------------------------------------------------

    //--------------------------------------------------------------------------------------
    Hero_InfoEx(A)->def += 240;
    Output_print("防御+240 ");HeroWinPer_WinPerAndMark(n, WinPer_Base);
    Hero_InfoEx(A)->def -= 240;
    //--------------------------------------------------------------------------------------

    Output_print("\n");

    HeroAssist_SetEnable(Main_enableHeroAssist);
  }

  Output_print("\n");

}
