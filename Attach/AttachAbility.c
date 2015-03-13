#include "AttachAbility.h"
#include "AttachAbility_private.h"

void AttachAbility_LoadByIndex(struct Hero* H, ASHANDLE hFile, unsigned int index)
{
  const char* name = ASFileGetAttachAbilityNameByIndex(hFile, index);
  int         lv   = ASFileGetAttachAbilityLevelByIndex(hFile, index);

  if (name == NULL || *name == '\0' || lv <= 0)
  {
    return ;
  }

  if (0 == strcmp(("绝情战意"), name))
  {
    JueQingZhanYi_Attach(H, lv);
  }
  else if (0 == strcmp(("淬毒匕首"), name))
  {
    CuiDuBiShou_Attach(H, lv);
  }
  else if (0 == strcmp(("冰心剑诀"), name))
  {
    BingXinJianJue_Attach(H, lv);
  }
  else if (0 == strcmp(("焚心剑意"), name))
  {
    FenXinJianYi_Attach(H, lv);
  }
  else if (0 == strcmp(("心静通灵"), name))
  {
    XinJingTongLing_Attach(H, lv);
  }
  else if (0 == strcmp(("伏虎势"), name))
  {
    FuHuShi_Attach(H, lv);
  }
  else if (0 == strcmp(("裂马势"), name))
  {
    LieMaShi_Attach(H, lv);
  }
  else if (0 == strcmp(("混元势"), name))
  {
    HunYuanShi_Attach(H, lv);
  }
}

void AttachAbility_Load(struct Hero* H, ASHANDLE hFile)
{
  AttachAbility_LoadByIndex(H, hFile, 0);
  AttachAbility_LoadByIndex(H, hFile, 1);
}
