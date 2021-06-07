#include <pspkernel.h>
#include <pspdisplay.h>
#include <pspctrl.h>
#include "graphics.h"
#include "game.h"
#include "highscores.h"
#include "options.h"

PSP_MODULE_INFO("Space Invaders", 0, 0, 7);

#define RGB(r, g, b) ((r)|((g)<<8)|((b)<<16))

/* Exit callback */
int exit_callback(int arg1, int arg2, void *common) {
          sceKernelExitGame();
          return 0;
}

/* Callback thread */
int CallbackThread(SceSize args, void *argp) {
          int cbid;

          cbid = sceKernelCreateCallback("Exit Callback", exit_callback, NULL);
          sceKernelRegisterExitCallback(cbid);

          sceKernelSleepThreadCB();

          return 0;
}

/* Sets up the callback thread and returns its thread id */
int SetupCallbacks(void) {
          int thid = 0;

          thid = sceKernelCreateThread("update_thread", CallbackThread, 0x11, 0xFA0, 0, 0);
          if(thid >= 0) {
                    sceKernelStartThread(thid, 0, 0);
          }

          return thid;
}

int main(void) {
    SetupCallbacks();
    initGraphics();
    SceCtrlData pad, lastpad;
    sceCtrlReadBufferPositive(&lastpad, 1);  
    Image* Background = loadImage("SpaceInvaders.png");

    Color SelectMenuColour = RGB(255, 255, 255);
    Color IdleMenuColour = RGB(155, 155, 155);
    
    int SelectMenu = 1;
    int Timer = 0;

    while(1) {
      sceCtrlReadBufferPositive(&pad, 1);
    
      if(pad.Buttons != lastpad.Buttons) {
      lastpad = pad;
      }      
      
      if(pad.Buttons & PSP_CTRL_UP)
      {     Timer++;
            if(Timer == 7) { SelectMenu--;}
            if(Timer == 8) { Timer = 1; } }
      
      if(pad.Buttons & PSP_CTRL_DOWN)
      {     Timer++;
            if(Timer == 7) { SelectMenu++;}
            if(Timer == 8) { Timer = 1; }}
            
      if(pad.Buttons & PSP_CTRL_CROSS)
      {
        switch (SelectMenu)
           {
            case 1: Game();
            SelectMenu = 1;
            break;
            
            case 2: HighScores();
            SelectMenu = 2;
            break;
            
            case 3: Options();
            SelectMenu = 3;
            break;
            
            case 4: sceKernelExitGame();
           }
      }
      if(SelectMenu <= 1) { SelectMenu = 1; }
      if(SelectMenu >= 4) { SelectMenu = 4; }
      
    blitAlphaImageToScreen(0, 0 , 480, 272, Background, 0, 0);

    if (SelectMenu == 1)
    {
    printTextScreen(40, 100, "> Start Game", SelectMenuColour);
    printTextScreen(40, 120, "High Scores", IdleMenuColour);
    printTextScreen(40, 140, "Options", IdleMenuColour);
    printTextScreen(40, 160, "Quit", IdleMenuColour);
    }
    
    if (SelectMenu == 2)
    {
    printTextScreen(40, 100, "Start Game", IdleMenuColour);
    printTextScreen(40, 120, "> High Scores", SelectMenuColour);
    printTextScreen(40, 140, "Options", IdleMenuColour);
    printTextScreen(40, 160, "Quit", IdleMenuColour);
    }
    
    if (SelectMenu == 3)
    {
    printTextScreen(40, 100, "Start Game", IdleMenuColour);
    printTextScreen(40, 120, "High Scores", IdleMenuColour);
    printTextScreen(40, 140, "> Options", SelectMenuColour);
    printTextScreen(40, 160, "Quit", IdleMenuColour);
    }
    
    if (SelectMenu == 4)
    {
    printTextScreen(40, 100, "Start Game", IdleMenuColour);
    printTextScreen(40, 120, "High Scores", IdleMenuColour);
    printTextScreen(40, 140, "Options", IdleMenuColour);
    printTextScreen(40, 160, "> Quit", SelectMenuColour);
    }
    
    printTextScreen(0, 0, "v0.7", SelectMenuColour);
    printTextScreen(310, 250, "Coded by Menace Inc", SelectMenuColour);

    sceDisplayWaitVblankStart();
    flipScreen();

    }
    sceKernelSleepThread();
    return 0;
}

