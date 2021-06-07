#include <pspkernel.h>
#include <pspdisplay.h>
#include <pspctrl.h>
#include <stdio.h>
#include "graphics.h"

#define RGB(r, g, b) ((r)|((g)<<8)|((b)<<16))

void Options()
{SceCtrlData pad;
  
 Color White = RGB(255, 255, 255);
 Color Black = RGB(0, 0, 0);

 while(1)
 {
 sceCtrlReadBufferPositive(&pad, 1);

 if (pad.Buttons & PSP_CTRL_SELECT)
      { 
      break;
     }
     
 if (pad.Buttons & PSP_CTRL_TRIANGLE)
      { 
      break;
     }

fillScreenRect(Black, 0, 0, 480, 272);   
printTextScreen(90,  100, "Sorry but options is not yet developed.", White);
printTextScreen(90,  110, " Press Triangle to return to the menu.", White);
sceDisplayWaitVblankStart();
flipScreen(); }}

