#ifndef INCLUDE_BUFF_PRIVATE
#define INCLUDE_BUFF_PRIVATE

#include "../Core/Config.h"
#include "../Core/HeroInfo.h"

#define BUFF_TYPE_TURN 0
#define BUFF_TYPE_TIME 1

struct Buff;
struct BuffList;

enum BuffID
{
  //CB
  FenShen_ID, JiaoHouShi_ID, ZhuiYingShi_ID,
  //KB
  ChuangXinA_ID, ChuangXinB_ID, CuiDuBiShou_ID, CuiXinShi_ID, DingShenShi_ID,
  DuanChang_ID, DuanJinShi_ID, JieMai_ID, PoJiaShi_ID, XieWuShi_ID, ZhuiHunShi_ID,
  //JZ
  BuYi_ID, MeiYing_ID, ZhenJiXia_ID, ZhanXuanJianFa_ID,
  //QZ
  LieYanJianFa_ID, HanBingJianFa_ID,
  //PQ
  CanHongYuJin_ID, FuHuShi_ID, LieMaShi_ID, LiuHeQiangFa_ID,
  //FQ
  HuiMaQiangA_ID, HuiMaQiangB_ID, KangLongQiangFa_ID, KuangNuQiangFa_ID, LongJuanQiangFa_ID, PoFengQiangFa_ID, YingJiChangKong_ID,
  //FB
  HuanQi_KuangNuQiangFa_ID, JiBenBianFa_ID, WuLaiGunFa_ID, XiuWuDuanHun_ID, ZhuiYingQuan_ID,
};

typedef void (*FuncApply)(struct Buff* self, struct BuffList* list);

struct Buff
{
  enum BuffID id;  //确保buff不会重复
  int type;        //0为以回合为单位，1为以时间为单位
  float dur;       //持续时间
  FuncApply start; //开始函数
  FuncApply stop;  //结束函数
  const char* startStr;
  const char* stopStr;
  int data_1;
  int data_2;
  int data_3;
  int data_4;
};

struct BuffNode
{
  //-------------------
  // 0 未启用
  // 1 启用中
  // 2 等待清理
  // 3 准备显示开始语句
  //
  // 0->3->1->2
  //-------------------
  int state;
  struct Buff buff;
  struct BuffNode* next;
};

struct BuffList
{
  struct HeroInfo* info;
  struct HeroInfo* current;
  const char* name;

  //=====================
  int time;
  float currTurn;
  float nextTurn;
  //=====================

  //=====================
  int ability_attack_mul;
  int buff_attack_mul;
  int defend_mul;
  int defend_add;
  int speed_mul;
  //=====================

  struct BuffNode head;
  struct BuffNode entry[BUFF_MAX_NUM];
};

void BuffList_Apply_Attack(struct BuffList* list, int abilityChangeValue, int buffChangeValue);
void BuffList_Apply_Defend(struct BuffList* list, int mulChangeValue, int addChangeValue);
void BuffList_Apply_Speed(struct BuffList* list, int mulChangeValue, int isStart);

#endif
