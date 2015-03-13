#include "HeroInfo.h"

void HeroInfo_Load_ini(struct HeroInfo* info, ASHANDLE hFile)
{
  if (info == NULL) return;

  info->speed = (float)ASIniGetInt(hFile, "基本信息", "出手速度", 10);

  info->minAttack = ASFileGetHeroInfo_ini(hFile, "最小攻击", 0);
  info->maxAttack = ASFileGetHeroInfo_ini(hFile, "最大攻击", 0);

  if (info->minAttack > info->maxAttack)
  {
    int temp = info->maxAttack;
    info->maxAttack = info->minAttack;
    info->minAttack = temp;
  }

  info->attribBL = ASFileGetHeroInfo_ini(hFile, "臂力", 0);
  info->attribSF = ASFileGetHeroInfo_ini(hFile, "身法", 0);
  info->attribGG = ASFileGetHeroInfo_ini(hFile, "根骨", 0);

  info->attribMZ = 95 + ASFileGetHeroInfo_ini(hFile, "命中率", 0);
  info->attribSB = ASFileGetHeroInfo_ini(hFile, "闪避率", 0);
  info->attribBJ = ASFileGetHeroInfo_ini(hFile, "暴击率", 0);
  info->attribPJ = ASFileGetHeroInfo_ini(hFile, "破击率", 0);

  info->attribKB = ASFileGetHeroInfo_ini(hFile, "抗暴击", 0);
  info->attribKP = ASFileGetHeroInfo_ini(hFile, "抗破击", 0);

  info->HP = info->maxHP = ASFileGetHeroInfo_ini(hFile, "气血", 0);
  info->MP = info->maxMP = ASFileGetHeroInfo_ini(hFile, "内息", 0);
  info->def = ASFileGetHeroInfo_ini(hFile, "防御", 0);

  info->attribXX = ASFileGetHeroInfo_ini(hFile, "吸取气血", 0);
  info->attribFT = ASFileGetHeroInfo_ini(hFile, "反弹伤害", 0);
  info->attribXN = ASFileGetHeroInfo_ini(hFile, "吸取内息", 0);
  info->attribNZ = ASFileGetHeroInfo_ini(hFile, "受损气血转内息", 0);

  info->attribFJ = ASFileGetHeroInfo_ini(hFile, "附加伤害", 0);
  info->attribJM = ASFileGetHeroInfo_ini(hFile, "减免伤害", 0);
  info->attribZS = ASFileGetHeroInfo_ini(hFile, "遭受伤害", 0);

  info->attribBS = ASFileGetHeroInfo_ini(hFile, "暴击伤害", 150);
  info->attribKX = ASFileGetHeroInfo_ini(hFile, "负面状态抗性", 0);
  info->attribXJ = ASFileGetHeroInfo_ini(hFile, "减少内息消耗", 0);
  info->attribBX = ASFileGetHeroInfo_ini(hFile, "内息抵消伤害", 0);
}

void HeroInfo_Load_xls(struct HeroInfo* info, ASHANDLE hFile)
{
  if (info == NULL) return;

  info->speed = (float)(ASFileGetHeroInfo_xls(hFile, 'D', 3, 1) * 2 + 8);

  info->minAttack = ASFileGetHeroInfo_xls(hFile, 'G', 19, 0);
  info->maxAttack = ASFileGetHeroInfo_xls(hFile, 'G', 20, 0);

  if (info->minAttack > info->maxAttack)
  {
    int temp = info->maxAttack;
    info->maxAttack = info->minAttack;
    info->minAttack = temp;
  }

  info->attribBL = ASFileGetHeroInfo_xls(hFile, 'C', 19, 0);
  info->attribSF = ASFileGetHeroInfo_xls(hFile, 'C', 20, 0);
  info->attribGG = ASFileGetHeroInfo_xls(hFile, 'C', 21, 0);

  info->attribMZ = 95 + ASFileGetHeroInfo_xls(hFile, 'C', 22, 0);
  info->attribSB = ASFileGetHeroInfo_xls(hFile, 'E', 22, 0);
  info->attribBJ = ASFileGetHeroInfo_xls(hFile, 'C', 23, 0);
  info->attribPJ = ASFileGetHeroInfo_xls(hFile, 'E', 23, 0);

  info->attribKB = ASFileGetHeroInfo_xls(hFile, 'C', 29, 0);
  info->attribKP = ASFileGetHeroInfo_xls(hFile, 'E', 29, 0);

  info->HP = info->maxHP = ASFileGetHeroInfo_xls(hFile, 'C', 17, 0);
  info->MP = info->maxMP = ASFileGetHeroInfo_xls(hFile, 'C', 18, 0);
  info->def = ASFileGetHeroInfo_xls(hFile, 'C', 24, 0);

  info->attribXX = ASFileGetHeroInfo_xls(hFile, 'C', 26, 0);
  info->attribFT = ASFileGetHeroInfo_xls(hFile, 'E', 26, 0);
  info->attribXN = ASFileGetHeroInfo_xls(hFile, 'C', 27, 0);
  info->attribNZ = ASFileGetHeroInfo_xls(hFile, 'E', 27, 0);

  info->attribFJ = ASFileGetHeroInfo_xls(hFile, 'C', 28, 0);
  info->attribJM = ASFileGetHeroInfo_xls(hFile, 'E', 28, 0);
  info->attribZS = 0;   // XLS不支持这个属性

  info->attribBS = 150 + ASFileGetHeroInfo_xls(hFile, 'C', 30, 0);
  info->attribKX = 0;   // XLS不支持这个属性
  info->attribXJ = 0;   // XLS不支持这个属性
  info->attribBX = 0;   // XLS不支持这个属性
}

void HeroInfo_Load(struct HeroInfo* info, ASHANDLE hFile)
{
  PASFile self = (PASFile)hFile;

  if (self == NULL)
  {
    return;
  }

  switch (self->type)
  {
  case ASFILE_TYPE_INI:
    return HeroInfo_Load_ini(info, self->ptr);
  case ASFILE_TYPE_XLS:
    return HeroInfo_Load_xls(info, self->ptr);
  default:
    break;
  }
}
