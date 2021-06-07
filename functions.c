#include <pspkernel.h>
#include <pspdisplay.h>
#include <pspctrl.h>
#include <stdio.h>
#include </usr/include/sys/stat.h>
#include "graphics.h"

#define RGB(r, g, b) ((r)|((g)<<8)|((b)<<16))

//shows the current round the player is at
void RoundDisplay(int Round)
{
 char RoundAsChar[3];
 int timer = 0; 
 Color White = RGB(255, 255, 255);
 Color Black = RGB(0, 0, 0);

 while(1)
 {timer++;
  if (timer == 150)
     { break;
     }

 fillScreenRect(Black, 0, 0, 480, 272);   
 printTextScreen(200,  135, "Round", White);
 sprintf(RoundAsChar, "%d", Round);
 printTextScreen(250, 135, RoundAsChar, White);
 sceDisplayWaitVblankStart();
 flipScreen();
 }
}
//shows the game over screen
//
//
//
void GameOver(int Score)
{
 char ScoreAsChar[5];
 int timer = 0; 
 Color White = RGB(255, 255, 255);
 Color Black = RGB(0, 0, 0);

 while(1)
 {
 timer++;
 if (timer == 300)
    { break;
    }

 fillScreenRect(Black, 0, 0, 480, 272);   
 sprintf(ScoreAsChar, "%d", Score);
 printTextScreen(245, 145, ScoreAsChar, White);
 printTextScreen(200, 145, "Score:", White);
 printTextScreen(200,  135, "Game Over", White);
 sceDisplayWaitVblankStart();
 flipScreen();
 }
}




//pauses the game
//
//
//
//
void Pause(Image* theme0,Image* theme1)
{SceCtrlData pad;
 int timer = 0;
  
 Color White = RGB(255, 255, 255);
 Color Black = RGB(0, 0, 0); 

 while(1)
 {
 sceCtrlReadBufferPositive(&pad, 1);
 timer++;
 
 if (pad.Buttons & PSP_CTRL_START)
      { timer++;
        if (timer > 14)
        { break;
        }
      }
     
 if (pad.Buttons & PSP_CTRL_TRIANGLE)
      { timer++;
        if (timer > 14)
        { break;
        }
      }
      
 if (timer == 14)
    {timer = 0;
    }

fillScreenRect(Black, 0, 0, 480, 272);
blitAlphaImageToScreen(0, 0, 90, 272, theme0, 0, 0);
blitAlphaImageToScreen(0, 0, 90, 272, theme1, 390, 0);
if (timer < 7)
{
printTextScreen(210,  130, "PAUSE", White);
}
if (timer > 7)
{
printTextScreen(210,  130, "PAUSE", Black);
}

sceDisplayWaitVblankStart();
flipScreen(); }}



//Resets the Invaders status
void ResetInvadersS(int* invaderS)
                   { *invaderS = 1;
                   }
//Resets the invaders X position by switch     
void ResetInvadersX(int* invaderX, int b)
                   { switch (b)
                            { case 0: *invaderX = 105;
                              break;
                              case 1: *invaderX = 120;
                              break;
                              case 2: *invaderX = 135;
                              break;
                              case 3: *invaderX = 150;
                              break;
                              case 4: *invaderX = 165;
                              break;
                              case 5: *invaderX = 180;
                              break;
                              case 6: *invaderX = 195;
                              break;
                              case 7: *invaderX = 210;
                              break;
                              case 8: *invaderX = 225;
                              break;
                              case 9: *invaderX = 240;
                              break;
                              case 10: *invaderX = 255;
                            }
                   }

//Resets the invaders Y but adds to it as well to start them lower down the map.
void ResetInvadersY(int* invaderY, int a, int RoundCount)
                   { int added = 0;
                     switch (RoundCount)
                            {case 1: added = 10;
                             break;
                             case 2: added = 15;
                             break;
                             case 3: added = 20;
                             break;
                             case 4: added = 25;
                             break;
                             case 5: added = 30;
                             break;
                             case 6: added = 35;
                             break;
                             case 7: added = 40;
                             break;
                             case 8: added = 50;
                             break;
                             case 9: added = 60;
                             }
                   
                     switch (a)
                            {case 0: *invaderY = (70 + added);
                             break;
                             case 1: *invaderY = (85 + added);
                             break;
                             case 2: *invaderY = (100 + added);
                             break;
                             case 3: *invaderY = (115 + added);
                             break;
                             case 4: *invaderY = (130 + added);
                             }
                   }
                   
//random generator
int RandomNumber(int low, int high)
                { SceKernelUtilsMt19937Context ctx;
                  sceKernelUtilsMt19937Init(&ctx, time(NULL));
                  u32 rand_val = sceKernelUtilsMt19937UInt(&ctx);
                  rand_val = low + rand_val % high;
                  return (int)rand_val;
                }
