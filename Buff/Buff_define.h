#ifndef INCLUDE_BUFF_DEFINE_H
#define INCLUDE_BUFF_DEFINE_H

struct Buff;
struct BuffList;

// CB
struct Buff* FenShenBuff_Get(unsigned int data);
struct Buff* JiaoHouShiBuff_Get(unsigned int level);
struct Buff* ZhuiYingShiBuff_Get(unsigned int level);

// KB
struct Buff* ChuangXinABuff_Get(unsigned int level);
struct Buff* ChuangXinBBuff_Get(unsigned int level);
struct Buff* CuiDuBiShouBuff_Get(unsigned int level);
struct Buff* CuiXinShiBuff_Get(unsigned int level);
struct Buff* DingShenShiBuff_Get(unsigned int level);
struct Buff* DuanChangBuff_Get(unsigned int level);
struct Buff* DuanJinShiBuff_Get(unsigned int level);
struct Buff* JieMaiBuff_Get(unsigned int level);
struct Buff* PoJiaShiBuff_Get(unsigned int level);
struct Buff* XieWuShiBuff_Get(unsigned int level);
struct Buff* ZhuiHunShiBuff_Get(unsigned int level);

void DuanChangBuff_SetDot(struct BuffList* list);

// JZ
struct Buff* BuYiBuff_Get();
struct Buff* MeiYingBuff_Get(unsigned int level, int attacksub);
struct Buff* ZhanXuanJianFaBuff_Get(unsigned int bj, unsigned int pj);
struct Buff* ZhenJiXiaBuff_Get();

// QZ
struct Buff* LieYanJianFaBuff_Get(unsigned int level);
struct Buff* HanBingJianFaBuff_Get(unsigned int level);

// PQ
struct Buff* CanHongYuJinBuff_Get(int min, int max, unsigned int mz);
struct Buff* FuHuShiBuff_Get(unsigned int level);
struct Buff* LieMaShiBuff_Get(unsigned int level);
struct Buff* LiuHeQiangFaBuff_Get(unsigned int level);

void CanHongYuJin_Buff_Set(struct BuffList* list);

// FQ
struct Buff* HuiMaQiangABuff_Get(unsigned int level);
struct Buff* HuiMaQiangBBuff_Get(unsigned int level);
struct Buff* KangLongQiangFaBuff_Get(unsigned int level);
struct Buff* KuangNuQiangFaBuff_Get(unsigned int level);
struct Buff* LongJuanQiangFaBuff_Get(unsigned int level);
struct Buff* PoFengQiangFaBuff_Get(unsigned int level);
struct Buff* YingJiChangKongBuff_Get(unsigned int level);

int HuiMaQiangA_GetID();

// FB
struct Buff* HuanQi_KuangNuQiangFaBuff_Get(unsigned int level);
struct Buff* JiBenBianFaBuff_Get(unsigned int data);
struct Buff* WuLaiGunFaBuff_Get(unsigned int level);
struct Buff* XiuWuDuanHunBuff_Get(unsigned int level);
struct Buff* ZhuiYingQuanBuff_Get(unsigned int level);

int XiuWuDuanHun_GetID();

#endif
