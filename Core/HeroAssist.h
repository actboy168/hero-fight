#ifndef INCLUDE_HEROASSIST
#define INCLUDE_HEROASSIST

struct Hero;

int  HeroAssist_SetEnable(int e);
void HeroAssist_SetHero(struct Hero* A, struct Hero* B);
void HeroAssist_Display();
void HeroAssist_SetOverflow(struct Hero* loser, int overflow);

#endif
