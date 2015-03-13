#include "Config.h"
#include "Output.h"
#include "HeroAssist.h"
#include "Hero.h"
#include "HeroWinPer.h"
#include "miniCRT.h"
#include "version.h"

struct Hero* A, *B;

const char* Main_AInput = ("./HeroA.ini");
const char* Main_BInput = ("./HeroB.ini");
const char* Main_Output = ("./Report.txt");
unsigned int Main_N = 1000;
int Main_enableHeroAssist = 0;
int Main_enableHeroWinPerEx = 0;
int Main_isDisplayExInfo = 0;
int Main_ShowAwin = 0;
int Main_ShowBwin = 0;
int Main_isDisplay = 1;
unsigned int Main_time = 360;
int Main_FBmode = 0;
int Main_PKmode = 0;

void Main_Command(int argc, const char* argv[])
{
  int i = 1;

  const char* command[] = {
    "A",
    "B",
    "O",
    "N",
    "time",
    "info",
    "Awin",
    "Bwin",
    "open-ass",
    "open-win",
    "open-FBmode",
    "open-PKmode",
    "close-display",
  };

  while (i < argc)
  {
    if (argv[i][0] == '-')
    {
      if (strcmp(argv[i]+1,command[0]) == 0)
      {
        if (i+1 < argc) Main_AInput = argv[++i];
      }
      else if (strcmp(argv[i]+1,command[1]) == 0)
      {
        if (i+1 < argc) Main_BInput = argv[++i];
      }
      else if (strcmp(argv[i]+1,command[2]) == 0)
      {
        if (i+1 < argc) Main_Output = argv[++i];
      }
      else if (strcmp(argv[i]+1,command[3]) == 0)
      {
        if (i+1 < argc) Main_N = atoi(argv[++i]);
      }
      else if (strcmp(argv[i]+1,command[4]) == 0)
      {
        if (i+1 < argc)
        {
          if (Main_FBmode == 1 || Main_PKmode == 1)
            i++;
          else
            Main_time = atoi(argv[++i]);
        }
      }
      else if (strcmp(argv[i]+1,command[5]) == 0)
      {
        Main_isDisplayExInfo = 1;
      }
      else if (strcmp(argv[i]+1,command[6]) == 0)
      {
        Main_ShowAwin = 1;
      }
      else if (strcmp(argv[i]+1,command[7]) == 0)
      {
        Main_ShowBwin = 1;
      }
      else if (strcmp(argv[i]+1,command[8]) == 0)
      {
        Main_enableHeroAssist = 1;
      }
      else if (strcmp(argv[i]+1,command[9]) == 0)
      {
        Main_enableHeroWinPerEx = 1;
      }
      else if (strcmp(argv[i]+1,command[10]) == 0)
      {
        Main_FBmode = 1;
        Main_PKmode = 0;
        Main_time = 1800;
      }
      else if (strcmp(argv[i]+1,command[11]) == 0)
      {
        Main_PKmode = 1;
        Main_FBmode = 0;
        Main_time = 720;
      }
      else if (strcmp(argv[i]+1,command[12]) == 0)
      {
        Main_isDisplay = 0;
      }
    }

    i++;
  }

  HeroWinPer_SetEnable(Main_enableHeroWinPerEx);
  HeroAssist_SetEnable(Main_enableHeroAssist);
}

void Main_DisplayInfo()
{
  Output_print(("HeroHelper版本: %s\n\n"), VERSION_STR);
  Output_print(("%s\n"), Output_ConvertEnc("", "UTF-8", Main_AInput));
  Output_print(("%s\n"), Output_ConvertEnc("", "UTF-8", Main_BInput));
  Output_print(("\n"));

  if (Main_isDisplayExInfo)
  {
    Output_print(("模式：                 %s\n"), Main_FBmode?("副本"):Main_PKmode?("武林大会"):("正常"));
    Output_print(("最大战斗时间：         %d\n"), Main_time);
    Output_print(("详细统计系统：         %s\n"), Main_enableHeroAssist?("开启"):("关闭"));
    Output_print(("更多胜率统计：         %s\n"), Main_enableHeroWinPerEx?("开启"):("关闭"));
    Output_print(("胜率统计模拟次数：     %d\n"), Main_N);
    Output_print(("指定胜负显示：         %s\n"), Main_ShowAwin?("A"):(Main_ShowBwin?("B"):("关闭")));

    Output_print(("\n\n"));
  }
}

void Main_init()
{
  Crt_init();
  Hero_init();
}

void Main_Run(unsigned int n, int isDisplay)
{
  HeroWinPer_Main(n);

  if (isDisplay)
  {
    int k = 0, curpos;
    if (Main_ShowAwin)
    {
      while(1)
      {
        curpos = Output_tell();
        if ((1 == Hero_Fight(A, B)) || (k >= 1000))
          break;
        Output_seek(curpos);
        k++;
      }
    }
    else if (Main_ShowBwin)
    {
      while(1)
      {
        curpos = Output_tell();
        if ((1 != Hero_Fight(A, B)) || (k >= 1000))
          break;
        Output_seek(curpos);
        k++;
      }
    }
    else
    {
      Hero_Fight(A, B);
    }

    HeroAssist_Display();
  }
}

void Main_Begin(const char* pHeroA, const char* pHeroB, const char* pOut)
{
  A = Hero_Create(pHeroA);
  B = Hero_Create(pHeroB);

  HeroAssist_SetHero(A, B);

  Output_open(pOut);
}

void Main_End()
{
  Hero_Destroy(A);
  Hero_Destroy(B);
  Output_close();
}

int main(int argc, const char* argv[])
{
  Main_Command(argc, argv);

  Main_init();
  Main_Begin(Main_AInput, Main_BInput, Main_Output);

  Main_DisplayInfo();

  Main_Run(Main_N, Main_isDisplay);
  Main_End();
  return 0;
}
