#ifndef __FUNCTIONS__
#define __FUNCTIONS__

extern void RoundDisplay(int Round);
extern void GameOver(int Score);
extern void Pause(Image* theme0, Image* theme1);
extern void ResetInvadersS(int invaderS);
extern void ResetInvadersX(int invaderX, int b);
extern void ResetInvadersY(int invaderY, int a, int RoundCount);
int RandomNumber(int low, int high);

#endif
