#include "Output.h"
#include "Config.h"

#include <stdio.h>
#include <stdarg.h>

#include <iconv.h>

FILE* outfile;

int Output_enable = 1;

#define CHECK do { if (!Output_enable) return;} while(0)

int Output_SetEnable(int e)
{
  int last_e = Output_enable;
  Output_enable = e;
  return last_e;
}

int Output_IsEnable()
{
  return Output_enable;
}

#include <time.h>
clock_t start;

int Output_open(const char* outfileName)
{
  if ((outfile = fopen(outfileName, "w")) == NULL)
  {
    return 0;
  }

  start = clock();

  return 1;
}

int Output_tell()
{
  return ftell(outfile);
}

void Output_seek(int pos)
{
  fseek(outfile, pos, SEEK_SET);
}

int Output_close()
{
  int cur, end, i;
  char p = 0;

  Output_print( "\n\n%.03f seconds\n", ((double)(clock() - start) / CLOCKS_PER_SEC));

  cur = ftell(outfile);
  fseek(outfile,   0, SEEK_END);
  end = ftell(outfile);
  fseek(outfile, cur, SEEK_SET);

  for (i = 0; i < end-cur; i++)
  {
    fwrite(&p, 1, 1, outfile);
  }

  return fclose(outfile);
}

char* Output_ConvertEnc(char* encFrom, char* encTo, const char* in)
{
  static char  bufout[1024], *sin, *sout;
  int  lenin, lenout, ret;
  iconv_t c_pt;

  if ((c_pt = iconv_open(encTo, encFrom)) == (iconv_t)-1)
  {
    return NULL;
  }
  iconv(c_pt, NULL, NULL, NULL, NULL);
  lenin  = strlen(in) + 1;
  lenout = 1024;
  sin    = (char *)in;
  sout   = bufout;
  ret    = iconv(c_pt, &sin, (size_t *)&lenin, &sout, (size_t *)&lenout);
  if (ret == -1)
  {
    return NULL;
  }
  iconv_close(c_pt);
  return bufout;
}

void Output_print(const char *format, ...)
{
  va_list ap;
  CHECK;

  va_start(ap, format);
  vfprintf(outfile, format, ap);
  va_end(ap);
}

void Output_BuffInfo(const char* info, const char* who)
{
  CHECK;

  Output_print(info, who, who);
  Output_print(("\n\n"));
}

void Output_Damage_name(const char* pName)
{
  CHECK;
  if (pName == NULL) return;
  Output_Damage_push(("【%s】"), pName);
}

void Output_Damage_dam(int dam, int bj, int pj)
{
  CHECK;
  if (dam <= 0) return;
  Output_Damage_push(("造成%d"), dam);

  if (!bj && !pj)
    Output_Damage_push(("伤害。"));
  else if (bj && pj)
    Output_Damage_push(("（暴击+破击）伤害。"));
  else if (bj)
    Output_Damage_push(("(暴击)伤害。"));
  else if (pj)
    Output_Damage_push(("(破击)伤害。"));
}

void Output_Damage_miss(const char* who)
{
  CHECK;
  Output_Damage_push(("但是%s身子一侧，闪了开去。"), who);
}

void Output_Damage_bingxin(const char* who, int data)
{
  CHECK;
  if (data <= 0) return;
  Output_Damage_push(("%s消耗 %d 内息吸收了另外 %d 伤害。"), who, data*2, data);
}

void Output_Damage_xixue(const char* who, int data)
{
  CHECK;
  if (data <= 0) return;
  Output_Damage_push(("%s 吸收了 %d 气血。"), who, data);
}

void Output_Damage_xinei(const char* who, int data)
{
  CHECK;
  if (data <= 0) return;
  Output_Damage_push(("%s 吸收了 %d 内息。"), who, data);
}

void Output_Damage_nizhuan(const char* who, int data)
{
  CHECK;
  if (data <= 0) return;
  Output_Damage_push(("%s 微一簇眉，将内息压回丹田，长出一口气，恢复了 %d 内息。"), who, data);
}

void Output_Damage_fantan(const char* who, int data)
{
  CHECK;
  if (data <= 0) return;
  Output_Damage_push(("%s 自身受到内息反震，闷哼一声，受到 %d 伤害。"), who, data);
}

void Output_Damage_newline()
{
  CHECK;
  Output_Damage_push(("\n\n"));
}

void Output_result(const char* winner, int winnerHP, int winnerMAXHP, const char* loser, int loserHP, int loserMAXHP)
{
  CHECK;
#define PERFORMAT(a,b) ((float)((b)-(a))/(float)(b)*100)
  Output_print(("%s总共造成对方 %.2f%% (%d 点) 伤害。\n"), winner, PERFORMAT(loserHP, loserMAXHP), loserMAXHP - loserHP);
  Output_print(("%s总共造成对方 %.2f%% (%d 点) 伤害。\n"), loser, PERFORMAT(winnerHP, winnerMAXHP), winnerMAXHP - winnerHP);
  Output_print(("%s技高一筹，获得了胜利!\n"), winner);
#undef PERFORMAT
}
/*
#define DAMAGE_BUFFER_LEN 1024
static char buffer[DAMAGE_BUFFER_LEN];
int buffer_point = 0;
*/
void Output_Damage_begin()
{
  /*
  CHECK;
  memset(buffer, 0, DAMAGE_BUFFER_LEN*sizeof(char));

  buffer_point = 0;
  */
}

/*
int Output_Damage_empty()
{
  return (buffer_point == 0);
}
*/

void Output_Damage_push(const char *format, ...)
{
  va_list ap;
  CHECK;

  va_start(ap, format);
  vfprintf(outfile, format, ap);
  va_end(ap);
  /*
  static char temp[256];
  int len;
  va_list ap;
  CHECK;

  va_start(ap, format);

  vsprintf(temp, format, ap);
  len = strlen(temp);

  if (len + buffer_point < DAMAGE_BUFFER_LEN)
  {
    strcpy(buffer + buffer_point, temp);
    buffer_point += len;
  }
  else
  {
    buffer_point = DAMAGE_BUFFER_LEN;
  }


  va_end(ap);
  */
}


void Output_Damage_end()
{
  /*
  CHECK;

  if (buffer_point >= DAMAGE_BUFFER_LEN)
  {
    buffer_point = DAMAGE_BUFFER_LEN - 1;
  }

  buffer[buffer_point] = 0;

  Output_print(buffer);
  */
}

#undef DAMAGE_BUFFER_LEN
#undef CHECK
