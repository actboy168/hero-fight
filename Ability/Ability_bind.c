#include "Ability.h"
#include "Ability_private.h"


//=======================================================
//
// 刺杀系
//
//=======================================================
#include "CB/Ability_ChiHun.h"
#include "CB/Ability_FenShen.h"
#include "CB/Ability_JiaoHouShi.h"
#include "CB/Ability_ShiPo.h"
#include "CB/Ability_WuMing.h"
#include "CB/Ability_YouMingShi.h"
#include "CB/Ability_ZhuiYingShi.h"

void CB_Ability_init()
{
  ChiHun_bind();
  FenShen_bind();
  JiaoHouShi_bind();
  ShiPo_bind();
  WuMing_bind();
  YouMingShi_bind();
  ZhuiYingShi_bind();
}
//=======================================================
//
// 控制系
//
//=======================================================
#include "KB/Ability_ChuangXin.h"
#include "KB/Ability_CuiXinShi.h"
#include "KB/Ability_DingShenShi.h"
#include "KB/Ability_DuanChang.h"
#include "KB/Ability_DuanJinShi.h"
#include "KB/Ability_JieMai.h"
#include "KB/Ability_PoJiaShi.h"
#include "KB/Ability_XieWuShi.h"
#include "KB/Ability_ZhuiHunShi.h"

void KB_Ability_init()
{
  ChuangXin_bind();
  CuiXinShi_bind();
  DingShenShi_bind();
  DuanChang_bind();
  DuanJinShi_bind();
  JieMai_bind();
  PoJiaShi_bind();
  XieWuShi_bind();
  ZhuiHunShi_bind();
}
//=======================================================
//
// 剑宗系
//
//=======================================================
#include "JZ/Ability_BuYi.h"
#include "JZ/Ability_JiXiaJianFa.h"
#include "JZ/Ability_MeiYing.h"
#include "JZ/Ability_MoZiJianFa.h"
#include "JZ/Ability_SouXin.h"
#include "JZ/Ability_ZhanXuan.h"
#include "JZ/Ability_ZhenJiXia.h"
#include "JZ/Ability_ZhenMoZi.h"

void JZ_Ability_init()
{
  BuYi_bind();
  JiXiaJianFa_bind();
  MeiYing_bind();
  MoZiJianFa_bind();
  SouXin_bind();
  ZhanXuan_bind();
  ZhenJiXia_bind();
  ZhenMoZi_bind();
}
//=======================================================
//
// 气宗系
//
//=======================================================
#include "QZ/Ability_HanBingJianFa.h"
#include "QZ/Ability_HuoYanJianFa.h"
#include "QZ/Ability_LieYanJianFa.h"
#include "QZ/Ability_LiuShuiJianFa.h"
#include "QZ/Ability_WuWoJianQi.h"
#include "QZ/Ability_XuanYinJianQi.h"

void QZ_Ability_init()
{
  HanBingJianFa_bind();
  HuoYanJianFa_bind();
  LieYanJianFa_bind();
  LiuShuiJianFa_bind();
  WuWoJianQi_bind();
  XuanYinJianQi_bind();
}
//=======================================================
//
// 破坏系
//
//=======================================================
#include "PQ/Ability_CanHongYuJin.h"
#include "PQ/Ability_FeiLong.h"
#include "PQ/Ability_KuangFeng.h"
#include "PQ/Ability_LiPoQianJun.h"
#include "PQ/Ability_LiuHeQiangFa.h"
#include "PQ/Ability_SheXingQiangFa.h"

void PQ_Ability_init()
{
  CanHongYuJin_bind();
  FeiLong_bind();
  KuangFeng_bind();
  LiPoQianJun_bind();
  LiuHeQiangFa_bind();
  SheXingQiangFa_bind();
}
//=======================================================
//
// 防护系
//
//=======================================================
#include "FQ/Ability_HuiMaQiang.h"
#include "FQ/Ability_LongJuanQiangFa.h"
#include "FQ/Ability_KangLongQiangFa.h"
#include "FQ/Ability_KuangNuQiangFa.h"
#include "FQ/Ability_NuJiaoQiangFa.h"
#include "FQ/Ability_PoFengQiangFa.h"
#include "FQ/Ability_YingJiChangKong.h"

void FQ_Ability_init()
{
  HuiMaQiang_bind();
  KangLongQiangFa_bind();
  KuangNuQiangFa_bind();
  LongJuanQiangFa_bind();
  NuJiaoQiangFa_bind();
  PoFengQiangFa_bind();
  YingJiChangKong_bind();
}
//=======================================================
//
// 副本的技能
//
//=======================================================
#include "FB/Special/Ability_ChangPingJun_WuMing.h"
#include "FB/Special/Ability_ChangWenJun_LongJuanQiangFa.h"
#include "FB/Special/Ability_LaoAi_XieWuShi.h"
#include "FB/Special/Ability_HuanQi_KuangNuQiangFa.h"

#include "FB/Ability_ZhongXieJianFa.h"
#include "FB/Ability_HuBenBiFa.h"
#include "FB/Ability_QinJunQiangFa.h"
#include "FB/Ability_ZhuiYingQuan.h"
#include "FB/Ability_WuLaiGunFa.h"
#include "FB/Ability_XiuWuDuanHun.h"
#include "FB/Ability_ZhenWuWoJianQi.h"

#include "FB/Ability_JiBenBianFa.h"

void FB_Ability_init()
{
  ChangPingJun_WuMing_bind();
  ChangWenJun_LongJuanQiangFa_bind();
  LaoAi_XieWuShi_bind();
  HuanQi_KuangNuQiangFa_bind();

  ZhongXieJianFa_bind();
  HuBenBiFa_bind();
  QinJunQiangFa_bind();
  ZhuiYingQuan_bind();
  WuLaiGunFa_bind();
  XiuWuDuanHun_bind();
  ZhenWuWoJianQi_bind();

  JiBenBianFa_bind();
}

#include "Common/Ability_JiBenBiFa.h"
#include "Common/Ability_JiBenJianFa.h"
#include "Common/Ability_JiBenQiangFa.h"
int Ability_init()
{
  Ability_bind(&abilityinfo_default);

  //Common
  JiBenBiFa_bind();
  JiBenJianFa_bind();
  JiBenQiangFa_bind();

  CB_Ability_init();
  KB_Ability_init();
  JZ_Ability_init();
  QZ_Ability_init();
  PQ_Ability_init();
  FQ_Ability_init();

  FB_Ability_init();

  return 1;
}
