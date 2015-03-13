#ifndef INCLUDE_CONFIG
#define INCLUDE_CONFIG

//最小命中,最大命中
#define CONST_MIN_MZ 5
#define CONST_MAX_MZ 100
//最小暴击,最大暴击
#define CONST_MIN_BJ 0
#define CONST_MAX_BJ 100
//最小破击,最大破击
#define CONST_MIN_PJ 0
#define CONST_MAX_PJ 100

//buff最大数目
#define BUFF_MAX_NUM 256

//防御的减伤系数
#define CONST_DEFEND (0.000215)
//最大防御的减伤
#define CONST_MAX_DEFEND_PERCENT (0.95)
//伤害减免公式
#define GET_DEFEND(d) ((float)(1.0-((((d)*CONST_DEFEND)>CONST_MAX_DEFEND_PERCENT)?CONST_MAX_DEFEND_PERCENT:((d)*CONST_DEFEND))))

#ifndef NULL
#define NULL 0
#endif

#include "../ASLib/ASLib.h"
#include <string.h>
#include <stdlib.h>
#include <math.h>

#endif
