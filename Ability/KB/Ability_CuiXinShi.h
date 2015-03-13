/*+---------------------------------------------
  | 摧心式 ( 主动技能 )
  | 割破敌人气门，使其内息持续降低
  | 技能消耗：(41+Lv*2) 内息
  | 攻击力 +(4+Lv*2)%
  | 技能命中后造成对方【摧心】
  | ( 持续 (Lv) 秒 )
  | 每秒内息损失 +(Lv>=14?2:1)%
  +---------------------------------------------*/
#ifndef INCLUDE_ABILITY_CUIXINSHI
#define INCLUDE_ABILITY_CUIXINSHI

void CuiXinShi_bind();

#endif