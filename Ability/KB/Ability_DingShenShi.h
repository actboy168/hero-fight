﻿/*+---------------------------------------------
  | 定身式 ( 主动技能 )
  | 攻击后附带闪避降低效果
  | 技能消耗：(46+Lv*4) 内息
  | 攻击力 +(见下)
  | 命中率 +(Lv*1)%
  | 技能命中后造成对方【定身】 
  | ( 持续 (见下) 回合 )
  | 躲闪率 -(见下)%
  +---------------------------------------------*/
#ifndef INCLUDE_ABILITY_DINGSHENSHI
#define INCLUDE_ABILITY_DINGSHENSHI

void DingShenShi_bind();

#endif

/*
等级 攻击力	减闪 回合
1	32	1	1
2	35	2	1
3	39	3	1
4	42	5	2
5	45	6	2
6	49	8	2
7	52	9	2
8	56	11	2
9	59	12	2
10	63	14	2
11	67	15	2
12	71	17	2
13	76	18	2
14	80	20	3
15	84	21	3*
16	89	23	3*
17	94	24	3*
18	100	26	3*
19	106	28	3*
20	115	30	3
21	123	31	3
22	132	33	3
23	142	35	3
24	153	36	4
36	523	57	5
*/