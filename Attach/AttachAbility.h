﻿#ifndef INCLUDE_ATACHABILITY
#define INCLUDE_ATACHABILITY

#include "../Core/Config.h"

struct Hero;

void AttachAbility_Load(struct Hero* H, ASHANDLE hFile);

/*+---------------------------------------------
  | 绝情战意 ( 辅助技能  )
  | 使绝情的战意充盈自身，加大暴击后所造成的伤害
  | 暴击造成的伤害 +(Lv*5)%
  +---------------------------------------------*/
void JueQingZhanYi_Attach(struct Hero* H, int lv);

/*+---------------------------------------------
  | 淬毒匕首 ( 被动技能 )
  | 将匕首淬毒，每次攻击命中后都可使对方中毒
  | 战斗时命中后造成对方【中毒】
  | ( 持续 ([Lv/2]+1) 秒 )
  | 每秒造成伤害 +(Lv/2+1)
  +---------------------------------------------*/
void CuiDuBiShou_Attach(struct Hero* H, int lv);

/*+---------------------------------------------
  | 冰心剑诀 ( 辅助技能  )
  | 以内息抵抗遭受的伤害，每 2 点内息可抵消 1 点气血伤害，不可与焚心剑意和圣灵剑诀同时使用
  | 内息可抵消伤害 +(Lv*3)%
  +---------------------------------------------*/
void BingXinJianJue_Attach(struct Hero* H, int lv);

/*+---------------------------------------------
  | 焚心剑意 ( 辅助技能  )
  | 受到伤害后，将受到的伤害转换为内息提升量，不可与冰心剑诀和圣灵剑诀同时使用
  | +(Lv*5)% 受损气血转内息
  +---------------------------------------------*/
void FenXinJianYi_Attach(struct Hero* H, int lv);

/*+---------------------------------------------
  | 心静通灵 ( 辅助技能  )
  | 减少使用技能所消耗的内息量，不可与剑气纵横同时使用
  | 减少内息消耗 +(Lv*4)%
  +---------------------------------------------*/
void XinJingTongLing_Attach(struct Hero* H, int lv);

/*+---------------------------------------------
  | 伏虎势 ( 辅助技能 )
  | 以伏虎之势在每次命中对手后都使对方流血
  | 命中后造成对方【流血】
  | ( 持续 ([Lv/2]+1) 秒 )
  | 每秒造成伤害 +([(Lv+1)/2])
  +---------------------------------------------*/
void FuHuShi_Attach(struct Hero* H, int lv);

/*+---------------------------------------------
  | 裂马势 ( 辅助技能 )
  | 以裂马之势在每次命中对手后都使对方命中降低，与“伏虎势”不可同时使用
  | 命中后造成对方【分心】
  | ( 持续 54 秒 )
  | 命中率 -(Lv*2)%
  +---------------------------------------------*/
void LieMaShi_Attach(struct Hero* H, int lv);

/*+---------------------------------------------
  | 混元势 ( 被动技能 )
  | 以混元之势降低自身负面效果的持续时间
  | 负面状态持续时间 -(Lv*5)%
  +---------------------------------------------*/
void HunYuanShi_Attach(struct Hero* H, int lv);

#endif
