#ifndef INCLUDE_OUTPUT
#define INCLUDE_OUTPUT

#include <stdio.h>



int Output_SetEnable(int e);
int Output_IsEnable();
int Output_open(const char* outfileName);
int Output_close();
int Output_tell();
void Output_seek(int pos);

char* Output_ConvertEnc(char* encFrom, char* encTo, const char* in);

void Output_print(const char *format, ...);

void Output_BuffInfo(const char* info, const char* who);

void Output_Damage_name(const char* pName);
void Output_Damage_dam(int dam, int bj, int pj);
void Output_Damage_miss(const char* who);
void Output_Damage_bingxin(const char* who, int data);
void Output_Damage_xixue(const char* who, int data);
void Output_Damage_xinei(const char* who, int data);
void Output_Damage_nizhuan(const char* who, int data);
void Output_Damage_fantan(const char* who, int data);
void Output_Damage_newline();

void Output_Damage_begin();
int Output_Damage_empty();
void Output_Damage_push(const char *format, ...);
void Output_Damage_end();

void Output_result(const char* winner, int winnerHP, int winnerMAXHP, const char* loser, int loserHP, int loserMAXHP);

#endif
