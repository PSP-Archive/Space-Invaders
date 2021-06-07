#include <pspkernel.h>
#include <pspdisplay.h>
#include <pspctrl.h>
#include <pspsystimer.h>
#include <stdio.h>
#include "graphics.h"
#include "functions.h"

#define RGB(r, g, b) ((r)|((g)<<8)|((b)<<16))

//=======================================================================================//
//main game

void Game()
{
 SceCtrlData pad;

//=======================//
//the players lifes
 int Players = 3;
 char LivesAsChar[2];
 int playerX = 120;
 int playerY = 245;

//======================//
//used to monitor the bullet
 int bullet = 0; 
 int bulletX = 0;
 int bulletY = 0;
 
//======================//
//used to judge speed
 int time = 100; 
 int timeA = 5;
 int timeB = 10;
 int timeC = 15;
 int timeD = 20;
 int invadersLeft = 55; 

//=======================//
//used to stop START button pressing too much
 int controlTime = 0; 

//=======================//
//used to change the direction of the invaders
 int direction = 0; 
//used to monitor which frame the invaders are on
 int FrameCounter[5] = {0,0,0,0,0};
 //used to monitor which frame the advanced bomb is on
 int BombFrame = 0;

//=======================//
//used to count rounds
 int Round = 1; 
 int RoundCount = 0;

 int randomA = 0;
 int randomB = 0;
 int randomC = 0;
 int randoma = 0;
 int randomb = 0;

 int base1X = 138;
 int base2X = 198;
 int base3X = 258;
 int base4X = 318;
 int baseY = 222;


//=======================//
//used for iterating through matrixes
 int a = 0;
 int b = 0;
 int c = 0;
 int d = 0;

//=======================//
//stats for the invaders bombs
 int bombS[5][5] = {{0, 0, 0, 0, 0},
                    {0, 0, 0, 0, 0},
                    {0, 0, 0, 0, 0},
                    {0, 0, 0, 0, 0},
                    {0, 0, 0, 0, 0}};
                  
 int bombX[5][5] = {{0, 0, 0, 0, 0},
                    {0, 0, 0, 0, 0},
                    {0, 0, 0, 0, 0},
                    {0, 0, 0, 0, 0},
                    {0, 0, 0, 0, 0}};

 int bombY[5][5] = {{0, 0, 0, 0, 0},
                    {0, 0, 0, 0, 0},
                    {0, 0, 0, 0, 0},
                    {0, 0, 0, 0, 0},
                    {0, 0, 0, 0, 0}};
 

//========================//
//invaderS is used to monitor which invaders are alive
 int invaderS[5][11] = {{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};
    
//=======================//                   
//invaderX and invaderY are used to output the X and Y co-ordinates of the invaders
 int invaderX[5][11] = {{105, 120, 135, 150, 165, 180, 195, 210, 225, 240, 255},
                        {105, 120, 135, 150, 165, 180, 195, 210, 225, 240, 255},
                        {105, 120, 135, 150, 165, 180, 195, 210, 225, 240, 255},
                        {105, 120, 135, 150, 165, 180, 195, 210, 225, 240, 255},
                        {105, 120, 135, 150, 165, 180, 195, 210, 225, 240, 255}};
 int invaderY[5][11] = {{70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70},
                        {85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85},
                        {100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100},
                        {115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115},
                        {130, 130, 130, 130, 130, 130, 130, 130, 130, 130, 130}};
                       
/* for each of the bases,i look up if that pixel has been hit,if not then use the matrix offset
   to output it onscreen with PutPixelScreen(). This puts the images on the screen at a 1:1 ratio
   but since i'm going for the whole screen in sight at all times,this is a good thing */
 int base1S[16][24] = {{0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0},
                       {0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 0},
                       {0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0},
                       {0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0},
                       {3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3},
                       {3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3},
                       {3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3},
                       {3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3},
                       {3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3},
                       {3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3},
                       {3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3},
                       {3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3},
                       {3, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3},
                       {3, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3},
                       {3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3},
                       {3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3}};

 int base2S[16][24] = {{0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0},
                       {0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 0},
                       {0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0},
                       {0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0},
                       {3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3},
                       {3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3},
                       {3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3},
                       {3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3},
                       {3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3},
                       {3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3},
                       {3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3},
                       {3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3},
                       {3, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3},
                       {3, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3},
                       {3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3},
                       {3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3}};
 
 int base3S[16][24] = {{0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0},
                       {0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 0},
                       {0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0},
                       {0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0},
                       {3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3},
                       {3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3},
                       {3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3},
                       {3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3},
                       {3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3},
                       {3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3},
                       {3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3},
                       {3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3},
                       {3, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3},
                       {3, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3},
                       {3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3},
                       {3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3}};
 
 int base4S[16][24] = {{0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0},
                       {0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 0},
                       {0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0},
                       {0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0},
                       {3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3},
                       {3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3},
                       {3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3},
                       {3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3},
                       {3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3},
                       {3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3},
                       {3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3},
                       {3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3},
                       {3, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3},
                       {3, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3},
                       {3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3},
                       {3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3}};
                       
//=================================//
//used for drawing and collision detection of players ship
 int player[8][15] = {{0,0,0,0,0,0,0,1,0,0,0,0,0,0,0},
                      {0,0,0,0,0,0,1,1,1,0,0,0,0,0,0},
                      {0,0,0,0,0,0,1,1,1,0,0,0,0,0,0},
                      {0,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
                      {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                      {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                      {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}};
                     
//=================================//
//used for drawing of the invaders
 int invader1a[8][12] = {{0,0,0,0,1,1,1,1,0,0,0,0},
                         {0,1,1,1,1,1,1,1,1,1,1,0},
                         {1,1,1,1,1,1,1,1,1,1,1,1},
                         {1,1,1,0,0,1,1,0,0,1,1,1},
                         {1,1,1,1,1,1,1,1,1,1,1,1},
                         {0,0,1,1,1,0,0,1,1,1,0,0},
                         {0,1,1,0,0,1,1,0,0,1,1,0},
                         {0,0,1,1,0,0,0,0,1,1,0,0}};
                        
 int invader1b[8][12] = {{0,0,0,0,1,1,1,1,0,0,0,0},
                         {0,1,1,1,1,1,1,1,1,1,1,0},
                         {1,1,1,1,1,1,1,1,1,1,1,1},
                         {1,1,1,0,0,1,1,0,0,1,1,1},
                         {1,1,1,1,1,1,1,1,1,1,1,1},
                         {0,0,0,1,1,0,0,1,1,0,0,0},
                         {0,0,1,1,0,1,1,0,1,1,0,0},
                         {1,1,0,0,0,0,0,0,0,0,1,1}};
                
 int invader2a[8][11] = {{0,0,1,0,0,0,0,0,1,0,0},
                         {0,0,0,1,0,0,0,1,0,0,0},
                         {0,0,1,1,1,1,1,1,1,0,0},
                         {0,1,1,0,1,1,1,0,1,1,0},
                         {1,1,1,1,1,1,1,1,1,1,1},
                         {1,0,1,1,1,1,1,1,1,0,1},
                         {1,0,1,0,0,0,0,0,1,0,1},
                         {0,0,0,1,1,0,1,1,0,0,0}};
                
 int invader2b[8][11] = {{0,0,1,0,0,0,0,0,1,0,0},
                         {1,0,0,1,0,0,0,1,0,0,1},
                         {1,0,1,1,1,1,1,1,1,0,1},
                         {1,1,1,0,1,1,1,0,1,1,1},
                         {1,1,1,1,1,1,1,1,1,1,1},
                         {0,1,1,1,1,1,1,1,1,1,0},
                         {0,0,1,0,0,0,0,0,1,0,0},
                         {0,1,0,0,0,0,0,0,0,1,0}};
                
 int invader3a[8][8] = {{0,0,0,1,1,0,0,0},
                        {0,0,1,1,1,1,0,0},
                        {0,1,1,1,1,1,1,0},
                        {1,1,0,1,1,0,1,1},
                        {1,1,1,1,1,1,1,1},
                        {0,1,0,1,1,0,1,0},
                        {1,0,0,0,0,0,0,1},
                        {0,1,0,0,0,0,1,0}};
               
 int invader3b[8][8] = {{0,0,0,1,1,0,0,0},
                        {0,0,1,1,1,1,0,0},
                        {0,1,1,1,1,1,1,0},
                        {1,1,0,1,1,0,1,1},
                        {1,1,1,1,1,1,1,1},
                        {0,0,1,0,0,1,0,0},
                        {0,1,0,1,1,0,1,0},
                        {1,0,1,0,0,1,0,1}};
               
 int saucer[7][16] = {{0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0},
                      {0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0},
                      {0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0},
                      {0,1,1,0,1,1,0,1,1,0,1,1,0,1,1,0},
                      {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                      {0,0,1,1,1,0,0,1,1,0,0,1,1,1,0,0},
                      {0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0}};
              
 int bulletI[4][2] = {{1,1},
                     {1,1},
                     {1,1},
                     {1,1}};
                     
 int bomb1[5][3] = {{0,1,0},
                    {0,1,0},
                    {0,1,0},
                    {1,1,1},
                    {0,1,0}};
                    
 int bomb2a[7][3] = {{0,0,1},
                     {0,1,0},
                     {1,0,0},
                     {0,1,0},
                     {0,0,1},
                     {0,1,0},
                     {1,0,0}};
 
 int bomb2b[7][3] = {{1,0,0},
                     {0,1,0},
                     {0,0,1},
                     {0,1,0},
                     {1,0,0},
                     {0,1,0},
                     {0,0,1}};
                      
 int invaderdeath[8][12] = {{0,0,0,0,0,1,0,0,1,0,0,0},
                            {0,0,1,0,0,1,0,0,1,0,0,1},
                            {0,0,0,1,0,0,0,1,0,0,1,0},
                            {1,1,1,0,0,0,0,0,0,0,0,0},
                            {0,0,0,0,1,0,0,0,0,0,1,1},
                            {0,0,1,1,0,0,0,0,1,0,0,0},
                            {0,1,0,0,0,0,1,0,0,1,0,0},
                            {0,0,0,0,0,0,1,0,0,0,1,0}};
                            
 int playerdeath1[8][15] = {{0,0,0,0,1,0,0,0,0,0,0,0,0,0,0},
                            {0,0,1,0,0,0,0,0,1,0,0,0,0,1,0},
                            {0,0,0,0,1,0,0,1,0,0,1,0,0,0,0},
                            {0,0,1,0,0,0,0,0,0,1,0,1,0,0,0},
                            {0,0,0,0,0,1,0,1,1,0,0,0,1,0,0},
                            {1,0,0,1,1,1,1,1,1,1,1,0,0,0,0},
                            {0,0,1,1,1,1,1,1,1,1,1,1,0,0,0},
                            {0,1,1,1,1,1,1,1,1,1,1,1,1,0,0}};
                            
 int playerdeath2[8][15] = {{0,1,0,0,0,0,0,1,0,0,0,0,1,0,0},
                            {0,0,0,0,1,0,0,0,0,0,0,0,0,0,0},
                            {0,0,1,0,0,0,0,1,0,0,0,0,1,0,0},
                            {0,0,0,0,0,0,1,0,0,0,1,0,0,0,0},
                            {0,1,0,0,0,1,1,0,1,0,0,0,0,0,1},
                            {0,0,0,0,1,1,1,1,1,1,0,0,1,0,0},
                            {0,0,0,1,1,1,1,1,1,1,1,0,0,0,0},
                            {0,1,1,1,1,1,1,1,1,1,1,1,1,0,0}};
                         
//==========================//
//used as timers                                       
 int playerTimer = 0;
 int invaderTimer = 0;
 int gameoverTimer = 0;
 int nextroundTimer = 0;

//==========================//
 int Score = 00000; //used to monitor score
 char ScoreAsChar[5]; //used to print score to screen
 
 
//==========================//
//Where I define my colours.only need these four
 Color White = RGB(255, 255, 255);
 Color Red = RGB(255, 0, 0);
 Color Green = RGB(0, 255, 0);
 Color Black = RGB(0, 0, 0);

//==========================//
//Where I load up the theme...should put in error handling
 Image* theme[2];
 theme[0] = loadImage("theme/theme1.png");
 theme[1] = loadImage("theme/theme2.png");

//========================//
//Displays the first round.
 RoundDisplay(Round);


/*=================================================================================
==================================Start Of Game Loop ==============================
==================================================================================*/
 while(1)
 { sceCtrlReadBufferPositive(&pad, 1);
 
  //=======================//
  //add to the timers
   invaderTimer++;
   playerTimer++;
   BombFrame++;
   
 //=======================// 
 //Controls.Select is Quit so it just breaks out of the loop.
   if (pad.Buttons & PSP_CTRL_SELECT)
      { break;
      }
   //===========================//
   //Start calls on the Pause function in functions.h
   if (pad.Buttons & PSP_CTRL_START)
      { controlTime++;
        if (controlTime == 7)
           { Pause(theme[0], theme[1]);
             controlTime = 0;
           }
      }
     
   //==========================//
   //nice and simple left and right.works 100%
   if (pad.Buttons & PSP_CTRL_LEFT)
      { playerX -= 2;
      }
   if (pad.Buttons & PSP_CTRL_RIGHT)
      { playerX += 2;
      }
   
   //==========================//
   //If there isn't a bullet,then it starts one at the players position   
   if(pad.Buttons & PSP_CTRL_CROSS)
     { if(bullet == 0)
         {bullet = 1;
          bulletX = playerX + 7 ;
          bulletY = 250;
         }
     }
     
 //================================//  
 //if there is a bullet fired,move it up the screen
   if (bullet == 1)
      { bulletY -= 3;
       }
       
 //===========================//
 //bomb generator
  randomC = RandomNumber(1, 75);
  if (bombS[RandomNumber(0, 4)][RandomNumber(0, 4)] == 0)
     { if (randomC > 60 && randomC < 70)
          { if ((invaderS[RandomNumber(0, 4)][RandomNumber(0, 10)]) != 0 )
               {bombS[RandomNumber(0, 4)][RandomNumber(0, 4)] = 1;
                bombX[RandomNumber(0, 4)][RandomNumber(0, 4)] = (invaderX[RandomNumber(0, 4)][RandomNumber(0, 10)]);
                bombY[RandomNumber(0, 4)][RandomNumber(0, 4)] = (invaderY[RandomNumber(0, 4)][RandomNumber(0, 10)]);
                }
           }
       if (randomC >= 70)
          { if ((invaderS[RandomNumber(0, 4)][RandomNumber(0, 10)]) != 0 )
               {bombS[RandomNumber(0, 4)][RandomNumber(0, 4)] = 2;
                bombX[RandomNumber(0, 4)][RandomNumber(0, 4)] = (invaderX[RandomNumber(0, 4)][RandomNumber(0, 10)]);
                bombY[RandomNumber(0, 4)][RandomNumber(0, 4)] = (invaderY[RandomNumber(0, 4)][RandomNumber(0, 10)]);
                }
           }
       }
   if (BombFrame == 4)
      { BombFrame = 0;
      }
 
//if there are invader bombs,move them down the screen   
   for (a=0;a<5;a++)
       { for (b=0;b<5;b++)
             { if (bombS[a][b] == 1)
                  { bombY[a][b] += 2;
                   }
               if (bombS[a][b] == 2)
                  { bombY[a][b] += 3;
                   }
              }
        }
        
   //==========================//
   //Invader speed
   if (invaderTimer == 1)
      { if (invadersLeft > 35)
           { time = 100;
             timeA = 5;
             timeB = 10;
             timeC = 15;
             timeD = 20;
            }     
        if (invadersLeft <= 35 && invadersLeft > 20)
           { time = 80;
             timeA = 4;
             timeB = 9;
             timeC = 13;
             timeD = 18;
            }     
        if (invadersLeft <= 20 && invadersLeft > 15)
           { time = 60;
             timeA = 4;
             timeB = 8;
             timeC = 12;
             timeD = 16;
            }
        if (invadersLeft <= 15 && invadersLeft > 10)
           { time = 40;
            }
        if (invadersLeft <= 10 && invadersLeft > 5)
           { time = 21;
             timeA = 3;
             timeB = 5;
             timeC = 7;
             timeD = 10;
            }
        if (invadersLeft <= 5 && invadersLeft > 3)
           { time = 15;
            timeA = 2;
            timeB = 3;
            timeC = 4;
            timeD = 5;
            }
        if (invadersLeft == 3)
           { time = 10;
            timeA = 1;
            timeB = 2;
            timeC = 3;
            timeD = 4;
            }
        if (invadersLeft == 2)
           { time = 5;
            timeA = 1;
            timeB = 2;
            timeC = 2;
            timeD = 2;
            }         
        if (invadersLeft == 1)
           { time = 2;
            timeA = 1;
            timeB = 1;
            timeC = 1;
            timeD = 1;
            }
        if (invadersLeft == 0)
           { time = 100;
             timeA = 5;
             timeB = 10;
             timeC = 15;
             timeD = 20;
            }
      }
     
  //===================================//
  //Invader stepping  
   if (invaderTimer == time)
      { if (FrameCounter[0] == 0) 
           { FrameCounter[0] = 1; }
        else { FrameCounter[0] = 0; }
        for (b =0; b < 11; b++)
            { if (invaderS[0][b] == 1) 
                 { if ( direction == 0) 
                      { invaderX[0][b] += 5;} 
                   else { invaderX[0][b] -= 5;}
                 }
            }
       }
       
   if (invaderTimer == (time + timeA))
      { if (FrameCounter[1] == 0) 
           { FrameCounter[1] = 1; }
        else { FrameCounter[1] = 0; }
        for (b =0; b < 11; b++)
            { if (invaderS[1][b] == 1) 
                 { if ( direction == 0) 
                      { invaderX[1][b] += 5;} 
                   else { invaderX[1][b] -= 5;}
                 }
            }
       }
     
   if (invaderTimer == (time + timeB))
      { if (FrameCounter[2] == 0) 
           { FrameCounter[2] = 1; }
        else { FrameCounter[2] = 0; }
        for (b =0; b < 11; b++)
            { if (invaderS[2][b] == 1) 
                 { if ( direction == 0) 
                      { invaderX[2][b] += 5;} 
                   else { invaderX[2][b] -= 5;}
                 }
            }
       }
       
   if (invaderTimer == (time + timeC))
      { if (FrameCounter[3] == 0) 
           { FrameCounter[3] = 1; }
        else { FrameCounter[3] = 0; }
        for (b =0; b < 11; b++)
            { if (invaderS[3][b] == 1) 
                 { if ( direction == 0) 
                      { invaderX[3][b] += 5;} 
                   else { invaderX[3][b] -= 5;}
                 }
            }
        }
       
   if (invaderTimer == (time + timeD))
      { invaderTimer = 0;
        if (FrameCounter[4] == 0) 
           { FrameCounter[4] = 1; }
        else { FrameCounter[4] = 0; }
        for (b =0; b < 11; b++)
            { if (invaderS[4][b] == 1) 
                 { if ( direction == 0) 
                      { invaderX[4][b] += 5;} 
                   else { invaderX[4][b] -= 5;}
                  }
             }
        }

 //=============================//
 //if the player moves beyond bounds,move ship back to bounds
   if (playerX <= (100))
      { playerX = 100;
       }   
   else if (playerX > (380 - 15))
           { playerX = (380 - 15);
            }
 //if bullet reaches top of screen,remove from screen
   if (bulletY < 50 )
      { bullet = 0;
        bulletX = 0;
        bulletY = 0;
       }
 //if bomb reaches bottom of screen,remove from screen   
   for (a=0;a<5;a++)
       { for (b=0;b<5;b++)
             { if (bombS[a][b] > 0)
                  { if (bombY[a][b] > 250)
                       {bombS[a][b] = 0;
                        bombX[a][b] = 0;
                        bombY[a][b] = 0;
                        }
                   }
              }
        }
  
 //===================================//
 //Controls left and right for the Invaders  
   for (b = 0; b < 11; b++)
       { for (a =0; a < 5; a++)
             { if (invaderX[a][b] > (380 - 15))
                  { if (invaderTimer == 0)
                       { direction = 1;
                         for (a =0; a < 5; a++)
                             { for (b = 0;b < 11; b++)
                                   { invaderY[a][b] += 10;
                                    }
                              }
                        }
                   }
              }
        }
 
   for (b = 0; b < 11; b++)
       { for (a =0; a < 5; a++)
             { if (invaderX[a][b] < 100)
                  { if (invaderTimer == 0)
                       { direction = 0;
                         for (a =0; a < 5; a++)
                             { for (b = 0;b < 11; b++)
                                   { invaderY[a][b] += 10;
                                    }
                              }
                        }
                   }
              }
        }
 
 //===================================//
 //Game Over if invaders reach the bottom of the screen
   for (a = 0; a < 5; a++)
       { for (b =0; b < 11; b++)
             { if ( invaderY[a][b] > 249)
                  { gameoverTimer++;
                    time = 10000;
                    if (gameoverTimer == 125)
                       { GameOver(Score);                           
                         break;
                        }
                    }
              }
         }
   if (gameoverTimer == 125)
      { break;
       }
       
 //====================================//   
 //Next round if all invaders killed.
   if (invadersLeft == 0)
      { nextroundTimer++;
        if (nextroundTimer == 125)
           { Round++;
             RoundCount++;
             RoundDisplay(Round);
             for (a=0;a<5;a++)
                 { for (b=0;b<11;b++)
                       { ResetInvadersS(&invaderS[a][b]);
                         ResetInvadersX(&invaderX[a][b], b);
                         ResetInvadersY(&invaderY[a][b], a, RoundCount);
                        }
                  }
             if (RoundCount == 9)
                {RoundCount = 0;
                 }
             invadersLeft = 55;
             playerX = 120;
             direction = 0;
             nextroundTimer = 0;
            }
       }
     
 //======================================//
 //fills the screen black  
   fillScreenRect(Black, 0, 0, 480, 272);   

 //======================================//
 //Collision detection
 //if the bulletX and invaderX are within each other, it then checks Y
   for (a = 0; a < 5; a++)
       { for (b =0; b < 11; b++)
             { if (invaderS[a][b] != 0)
                  { if (bulletX >= invaderX[a][b] && (bulletX + 1) <= (invaderX[a][b] + 12))
                       { if (bulletY >= invaderY[a][b] && (bulletY + 4) <= (invaderY[a][b] + 8))
                            {bullet = 0;
                             bulletX = 0;
                             bulletY = 0;
                             for (c = 0; c < 8; c++)
                                 { for (d = 0; d < 12; d++)
                                       { if ( invaderdeath[c][d] == 1)
                                            { putPixelScreen(White, (invaderX[a][b] + d), (invaderX[a][b] + c));
                                             }
                                        }
                                  }
                             invaderS[a][b] -= 1;
                             invaderX[a][b] = 150;
                             invaderY[a][b] = -20;
                             switch (a) //thought this was nice,different scores depending on what line it was on :)
                                    { case 0: Score += 30;
                                      break;
                                      case 1: Score += 20;
                                      break;
                                      case 2: Score += 20;
                                      break;
                                      case 3: Score += 10;
                                      break;
                                      case 4: Score += 10;
                                      }
                             invadersLeft--;
                            }
                       }
                  }
             }
       }
  
 //===================================//       
 //collision detection for the bases
   for (a = 0; a < 16; a++)
       { for (b =0; b < 24; b++)
             { if (base1S[a][b] > 0)
                  { if ( bulletX == ( base1X + b) || (bulletX + 1) == (base1X + b))
                      { if ( bulletY <= ( baseY + a ) && (bulletY + 4) >= (baseY + a))
                           { bullet = 0;
                             bulletX = 0;
                             bulletY = 0;
                             randoma = RandomNumber(0, 2);
                             randomb = RandomNumber(0, 2);
                             if (randoma <= 1)
                                { randomA = (a - RandomNumber(1, 3));
                                }
                             else { randomA = (a + RandomNumber(1, 3));
                                  }
                             if (randomb <= 1)
                                { randomB = (b - RandomNumber(1, 3));
                                }
                             else { randomB = (b + RandomNumber(1, 3));
                                  }
                             if (randomA > 16){randomA = 16;}
                             if (randomA < 0){randomA = 0;}
                             if (randomB > 24){randomB = 24;}
                             if (randomB < 0){randomB = 0;}
                          
                             base1S[randomA][randomB] -= RandomNumber(2, 4);
                             base1S[a][b] -= 3;
                             base1S[randomA][randomB] -= RandomNumber(2, 4);
                            }
                       }
                   }
              }
       }
   for (a = 0; a < 16; a++)
       { for (b =0; b < 24; b++)
             { if (base2S[a][b] > 0)
                  { if ( bulletX == ( base2X + b) || (bulletX + 1) == (base2X + b))
                      { if ( bulletY <= ( baseY + a ) && (bulletY + 4) >= (baseY + a))
                           { bullet = 0;
                             bulletX = 0;
                             bulletY = 0;
                             randoma = RandomNumber(0, 2);
                             randomb = RandomNumber(0, 2);
                             if (randoma <= 1)
                                { randomA = (a - RandomNumber(1, 3));
                                }
                             else { randomA = (a + RandomNumber(1, 3));
                                  }
                             if (randomb <= 1)
                                { randomB = (b - RandomNumber(1, 3));
                                }
                             else { randomB = (b + RandomNumber(1, 3));
                                  }
                             if (randomA > 16){randomA = 16;}
                             if (randomA < 0){randomA = 0;}
                             if (randomB > 24){randomB = 24;}
                             if (randomB < 0){randomB = 0;}
                          
                             base2S[randomA][randomB] -= RandomNumber(2, 4);
                             base2S[a][b] -= 3;
                             base2S[randomA][randomB] -= RandomNumber(2, 4);
                            }
                       }
                   }
              }
       }
   for (a = 0; a < 16; a++)
       { for (b =0; b < 24; b++)
             { if (base3S[a][b] > 0)
                  { if ( bulletX == ( base3X + b) || (bulletX + 1) == (base3X + b))
                      { if ( bulletY <= ( baseY + a ) && (bulletY + 4) >= (baseY + a))
                           { bullet = 0;
                             bulletX = 0;
                             bulletY = 0;
                             randoma = RandomNumber(0, 2);
                             randomb = RandomNumber(0, 2);
                             if (randoma <= 1)
                                { randomA = (a - RandomNumber(1, 3));
                                }
                             else { randomA = (a + RandomNumber(1, 3));
                                  }
                             if (randomb <= 1)
                                { randomB = (b - RandomNumber(1, 3));
                                }
                             else { randomB = (b + RandomNumber(1, 3));
                                  }
                             if (randomA > 16){randomA = 16;}
                             if (randomA < 0){randomA = 0;}
                             if (randomB > 24){randomB = 24;}
                             if (randomB < 0){randomB = 0;}
                          
                             base3S[randomA][randomB] -= RandomNumber(2, 4);
                             base3S[a][b] -= 3;
                             base3S[randomA][randomB] -= RandomNumber(2, 4);
                            }
                       }
                   }
              }
       }
   for (a = 0; a < 16; a++)
       { for (b =0; b < 24; b++)
             { if (base4S[a][b] > 0)
                  { if ( bulletX == ( base4X + b) || (bulletX + 1) == (base4X + b))
                      { if ( bulletY <= ( baseY + a ) && (bulletY + 4) >= (baseY + a))
                           { bullet = 0;
                             bulletX = 0;
                             bulletY = 0;
                             randoma = RandomNumber(0, 2);
                             randomb = RandomNumber(0, 2);
                             if (randoma <= 1)
                                { randomA = (a - RandomNumber(1, 3));
                                }
                             else { randomA = (a + RandomNumber(1, 3));
                                  }
                             if (randomb <= 1)
                                { randomB = (b - RandomNumber(1, 3));
                                }
                             else { randomB = (b + RandomNumber(1, 3));
                                  }
                             if (randomA > 16){randomA = 16;}
                             if (randomA < 0){randomA = 0;}
                             if (randomB > 24){randomB = 24;}
                             if (randomB < 0){randomB = 0;}
                          
                             base4S[randomA][randomB] -= RandomNumber(2, 4);
                             base4S[a][b] -= 3;
                             base4S[randomA][randomB] -= RandomNumber(2, 4);
                            }
                       }
                   }
              }
       }
       
/*===============================Display =============================*/
//===================================================================//
//goes through all the invaders and checks if alive
//if alive, it draws to screen
   for (a = 3; a < 5; a++)
       { for (b =0; b < 11; b++)
             {if (invaderS[a][b] == (1))
                 { if (FrameCounter[a] == (1))
                      { for (c = 0; c < 8; c++)
                            { for (d = 0; d < 12; d++)
                                  { if ( invader1a[c][d] == 1)
                                       { putPixelScreen(White, (invaderX[a][b] + d), (invaderY[a][b] + c));
                                       }
                                  }
                            }
                      }
                    else
                      { for (c = 0; c < 8; c++)
                            { for (d = 0; d < 12; d++)
                                  { if ( invader1b[c][d] == 1)
                                       { putPixelScreen(White, (invaderX[a][b] + d), (invaderY[a][b] + c));
                                       }
                                  }
                       }     }
                 }
              }
       }
       
  //===========================================//
  //draws the two middle rows     
   for (a = 1; a < 3; a++)
       { for (b =0; b < 11; b++)
             {if (invaderS[a][b] == (1))
                 { if (FrameCounter[a] == (1))
                      { for (c = 0; c < 8; c++)
                            { for (d = 0; d < 11; d++)
                                  { if ( invader2a[c][d] == 1)
                                       { putPixelScreen(White, (invaderX[a][b] + d), (invaderY[a][b] + c));
                                       }
                                  }
                            }
                      }
                    else
                      { for (c = 0; c < 8; c++)
                            { for (d = 0; d < 11; d++)
                                  { if ( invader2b[c][d] == 1)
                                       { putPixelScreen(White, (invaderX[a][b] + d), (invaderY[a][b] + c));
                                       }
                                  }
                       }     }
                 }
              }
       }
 //================================//
 //draws the top row of invaders       
   for (a = 0; a < 1; a++)
       { for (b =0; b < 11; b++)
             {if (invaderS[a][b] == (1))
                 { if (FrameCounter[a] == (1))
                      { for (c = 0; c < 8; c++)
                            { for (d = 0; d < 8; d++)
                                  { if ( invader3a[c][d] == 1)
                                       { putPixelScreen(White, (invaderX[a][b] + d), (invaderY[a][b] + c));
                                       }
                                  }
                            }
                      }
                    else
                      { for (c = 0; c < 8; c++)
                            { for (d = 0; d < 8; d++)
                                  { if ( invader3b[c][d] == 1)
                                       { putPixelScreen(White, (invaderX[a][b] + d), (invaderY[a][b] + c));
                                       }
                                  }
                       }     }
                 }
              }
       }
       
//==========================================//
//draws bombs
   for (a=0;a<5;a++)
       { for (b=0;b<5;b++)
             { if (bombS[a][b] == 1)
                  { for (c = 0; c < 5; c++)
                        { for (d = 0; d < 3; d++)
                              { if (bomb1[c][d] == 1)
                                   { putPixelScreen(White, (bombX[a][b] + d), (bombY[a][b] + c));
                                   }
                              }
                        }
                   }
               if (bombS[a][b] == 2)
                  { if (BombFrame < 2)
                       { for (c = 0; c < 7; c++)
                             { for (d = 0; d < 3; d++)
                                   { if (bomb2a[c][d] == 1)
                                        { putPixelScreen(White, (bombX[a][b] + d), (bombY[a][b] + c));
                                        }
                                    }
                              }
                        }
                  }
               else { for (c = 0; c < 7; c++)
                        { for (d = 0; d < 3; d++)
                              { if (bomb2b[c][d] == 1)
                                   { putPixelScreen(White, (bombX[a][b] + d), (bombY[a][b] + c));
                                   }
                              }
                        }
                     }
        }
   }

//==============================================//
//Draws bases
 for (a = 0; a < 16; a++)
     { for (b =0; b < 24; b++)
           {if (base1S[a][b] >= 1)
               { putPixelScreen(Green, (base1X + b), (baseY + a));
               }
           }
     }
 
  for (a = 0; a < 16; a++)
     { for (b =0; b < 24; b++)
           {if (base2S[a][b] >= 1)
               { putPixelScreen(Green, (base2X + b), (baseY + a));
               }
           }
     }
     
   for (a = 0; a < 16; a++)
     { for (b =0; b < 24; b++)
           {if (base3S[a][b] >= 1)
               { putPixelScreen(Green, (base3X + b), (baseY + a));
               }
           }
     }
     
    for (a = 0; a < 16; a++)
     { for (b =0; b < 24; b++)
           {if (base4S[a][b] >= 1)
               { putPixelScreen(Green, (base4X + b), (baseY + a));
               }
           }
     }
 //==================================//
 //Draws bullet
 if (bullet == (1))
    { for ( a = 0; a < 4; a++)
          { for (b = 0; b < 2; b++)
                { putPixelScreen(White, (bulletX + b), (bulletY + a));
                }
          }
    }
    
 //=================================//
 //Draws players ship
   for (a = 0; a < 8; a++)
       { for (b =0; b < 15; b++)
             { if (player[a][b] == 1)
                  { putPixelScreen(Green, (playerX + b), (playerY + a));
                  }
             }
       }

 drawLineScreen(95, 260, 385, 260, Green);
 blitAlphaImageToScreen(0, 0, 90, 272, theme[0], 0, 0);
 blitAlphaImageToScreen(0, 0, 90, 272, theme[1], 390, 0);

 sprintf(ScoreAsChar, "%d", Score);
 sprintf(LivesAsChar, "%d", Players);
 printTextScreen(100, 20, ScoreAsChar, White);
 printTextScreen(100, 10, "Score:", White);
 printTextScreen(350, 20, LivesAsChar, White);
 printTextScreen(350, 10, "Lives:", White);
 
 flipScreen();
 }
 
 //used to free up memory
 int i;
 for (i = 0;i < 1;i++)
     { freeImage(theme[i]);
     }
}
