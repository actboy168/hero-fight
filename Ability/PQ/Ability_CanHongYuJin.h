﻿/*+---------------------------------------------
  | 残红欲尽 ( 主动技能 )
  | 以攻击激发自己的求生意志，在自己气血越低时，爆发出越强悍的攻击力
  | 发动几率：100%
  | 技能消耗：(48+Lv*12) 内息
  | 施展后进入【残红欲尽】 ( 持续 1 回合 )
  | 攻击力 (1+[(Lv+1)/2]) ~ (60+Lv*18)%
  +---------------------------------------------*/
#ifndef INCLUDE_ABILITY_CANHONGYUJIN
#define INCLUDE_ABILITY_CANHONGYUJIN

void CanHongYuJin_bind();

#endif

//注：
//残红欲尽现在的计算方式和真墨子一样(但实际公式如何我不确定)，也没有使用buff，只是个暂时方案。