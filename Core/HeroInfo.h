#ifndef INCLUDE_HEROINFO
#define INCLUDE_HEROINFO

#include "Config.h"

struct HeroInfo
{
  int minAttack, maxAttack;
  int HP, MP, def;
  int maxHP, maxMP;
  int attribBL, attribSF, attribGG;
  int attribMZ, attribSB, attribBJ, attribPJ;
  int attribKB, attribKP;
  int attribXX, attribFT, attribXN, attribNZ;
  int attribFJ, attribJM, attribZS;
  int attribBS, attribKX, attribXJ, attribBX;
  float speed;

  int m_sum_dot;
  int m_dot_a;
  int m_dot_b;
  int m_mot;

  int dizzy;
};

void HeroInfo_Load(struct HeroInfo* info, ASHANDLE hFile);

#endif
