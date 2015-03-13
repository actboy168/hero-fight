#include "Ability.h"
#include "Ability_private.h"

#include "../Core/Hero.h"
#include "../Core/Output.h"
#include "../Core/Mem.h"
#include "../Core/miniCRT.h"
#include "../Core/HeroAssist.h"
#include "../Core/HeroHelper.h"

int Ability_GetFeatures(struct Ability* self, int type)
{
  return (((self->info->features) & (1<<type))? 1:0);
}

char* Ability_GetName(struct Ability* self)
{
  return self->info->name;
}

int Ability_GetLevel(struct Ability* self)
{
  return self->level;
}

float damage_RollAttack(struct Hero* attacker)
{
  struct HeroInfo* info = Hero_Info(attacker);
  return (float)Crt_GetRandomInt(info->minAttack, info->maxAttack);
}

int damage_DeathCheck(int dam, struct Hero* target)
{
  if (Hero_Info(target)->HP > dam)
  {
    Hero_Info(target)->HP -= dam;
    return 1;
  }
  else
  {
    int overflow = dam - Hero_Info(target)->HP;
    Hero_Info(target)->HP = 0;
    HeroAssist_SetOverflow(target, overflow);
    return 0;
  }

  return 1;
}

unsigned int damage_Now(float attack, struct Hero* attackerHero, struct Hero* targetHero, int bj, int pj)
{
#define PERCENT(n) ((float)(n)/(float)100.0)

  unsigned int nRet = 0;

  struct HeroInfo* attacker = Hero_Info(attackerHero);
  struct HeroInfo* target = Hero_Info(targetHero);

  float dam = attack;
  int int_dam;
  int real_dam;
  int de_dam = 0;

  //暴击
  if (bj) dam *= PERCENT(attacker->attribBS);

  // "真无我剑气"无视防御
  if (!Hero_GetAbility_AntiFY(attackerHero))
  {
    //破击
    if (!pj) dam *= GET_DEFEND(target->def);
  }

  //附加伤害
  dam += attacker->attribFJ;
  //遭受伤害
  dam += target->attribZS;
  //伤害减免
  dam -= target->attribJM;
  //避免负伤害
  if (dam < 0.0) dam = 0.0;

  int_dam = (int)dam;

  real_dam = int_dam;

  //冰心
  if (target->attribBX > 0)
  {
    // 噬魄无视冰心
    if (!Hero_GetAbility_AntiBX(attackerHero))
    {
      de_dam = (int)(int_dam * PERCENT(target->attribBX));

      if (target->MP/2 < de_dam)
        de_dam = target->MP/2;
      target->MP -= de_dam * 2;

      real_dam = int_dam - de_dam;
    }
  }

  //扣除伤害
  damage_DeathCheck(real_dam, targetHero);

  Output_Damage_dam(real_dam, bj, pj);
  Output_Damage_bingxin(Hero_Name(targetHero), de_dam);

  //确保被攻击者未死
  if (target->HP > 0)
  {
    //受损气血转内息
    if (target->attribNZ > 0)
    {
      int nizhuan = (int)(real_dam * PERCENT(target->attribNZ));

      if (nizhuan + target->MP > target->maxMP)
        nizhuan = target->maxMP - target->MP;

      target->MP += nizhuan;
      Output_Damage_nizhuan(Hero_Name(targetHero), nizhuan);
    }
  }

  //确保攻击者未死
  if (attacker->HP > 0)
  {
    //吸血
    if (attacker->attribXX > 0)
    {
      int xixue = (int)(int_dam * PERCENT(attacker->attribXX));

      if (xixue + attacker->HP > attacker->maxHP)
        xixue = attacker->maxHP - attacker->HP;

      attacker->HP += xixue;
      Output_Damage_xixue(Hero_Name(attackerHero), xixue);
    }

    //吸内
    if (attacker->attribXN > 0)
    {
      int xinei = (int)(int_dam * PERCENT(attacker->attribXN));

      if (xinei + attacker->MP > attacker->maxMP)
        xinei = attacker->maxMP - attacker->MP;

      if (target->MP < xinei)
        xinei = target->MP;

      attacker->MP += xinei;
      target->MP -= xinei;
      Output_Damage_xinei(Hero_Name(attackerHero), xinei);
    }
  }

  //确保被攻击者未死
  if (target->HP > 0)
  {
    //反弹
    if (target->attribFT > 0)
    {
      // "真无我剑气"无视反弹
      if (!Hero_GetAbility_AntiFT(attackerHero))
      {
        float fantan = (float)Crt_GetRoundUp(int_dam * PERCENT(target->attribFT));
        int real_fantan;

        //防御减伤
        fantan *= GET_DEFEND(attacker->def);
        //遭受伤害
        fantan += attacker->attribZS;
        //伤害减免
        fantan -= attacker->attribJM;
        //避免负伤害
        if (fantan < 0.0) fantan = 0.0;

        //向上取整
        real_fantan = Crt_GetRoundUp(fantan);

        //扣除伤害
        damage_DeathCheck(real_fantan, attackerHero);

        Output_Damage_fantan(Hero_Name(attackerHero), real_fantan);
      }
    }
  }

  if (attacker->HP <= 0) nRet |= 0x02;
  if (target->HP <= 0) nRet |= 0x01;

  return nRet;

#undef PERCENT
}

unsigned int Ability_AttackEx(struct Ability* self, struct Hero* attacker, struct Hero* target)
{
  struct Ability_Info* info = self->info;
  unsigned int nRet = 0;
  int n = 0;
  int flag = ((!((Main_FBmode) && (self == &ability_default))) && (!Main_PKmode));
  info->pay(self, attacker, target);
  info->before(self, attacker, target);

  do
  {
    info->add_buff_to_attacker(self, attacker, target);
    info->output(self, attacker, target);
    if (Hero_isMingZhong(attacker, target, flag))
    {
      int bp = 0;
      info->add_buff_to_target(self, attacker, target);
      Hero_AttachBuff(attacker, target);
      bp = Hero_isBJAndPJ(attacker, target, (!Main_FBmode) && (!Main_PKmode));
      nRet |= damage_Now(info->damage(self, attacker, target), attacker, target, ((bp>>1)&1), (bp&1));
    }
    else
    {
      if (!Hero_HaveBuff_inStart(attacker, HuiMaQiangA_GetID()))
      {
        Output_Damage_miss(Hero_Name(target));
      }
    }

    Output_Damage_newline();
  }
  while((++n < info->count) && ((nRet&0x03) == 0));

  info->after(self, attacker, target);

  return nRet;
}

unsigned int Ability_Attack(struct Ability* self, struct Hero* attacker, struct Hero* target)
{
  // 残红欲尽
  CanHongYuJin_Buff_Set(Hero_BuffList(attacker));

  // 袖舞断魂 挑飞武器的效果
  if (Hero_HaveBuff(attacker, XiuWuDuanHun_GetID()))
  {
    unsigned int ret = 0;
    int min = Hero_Info(attacker)->minAttack;
    int max = Hero_Info(attacker)->maxAttack;

    Hero_Info(attacker)->minAttack = 5;
    Hero_Info(attacker)->maxAttack = 10;

    ret = Ability_AttackEx(&ability_default, attacker, target);

    Hero_Info(attacker)->minAttack = min;
    Hero_Info(attacker)->maxAttack = max;

    return ret;
  }

  if ((self->info != NULL) && (self->info->check(self, attacker)))
  {
    return Ability_AttackEx(self, attacker, target);
  }
  else
  {
    return Ability_AttackEx(&ability_default, attacker, target);
  }
}

struct Ability* Ability_Create(struct Hero* H, ASHANDLE hFile)
{
  struct Ability* self = Mem_new(self, struct Ability);
  memset(self, 0, sizeof(struct Ability));

  self->info = Ability_GetEntry(ASFileGetAbilityName(hFile));

  if (self->info != NULL)
  {
    self->level  = ASFileGetAbilityLevel(hFile);
    self->data_1 = ASFileGetAbilityData(hFile);
    self->info->init(self, H);
  }

  return self;
}

void Ability_Destroy(struct Ability* self)
{
  Mem_delete(self);
}
