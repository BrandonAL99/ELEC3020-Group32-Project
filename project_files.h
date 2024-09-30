#ifndef __HEADER__
#define __HEADER__

#include "ESP32S3VGA.h"  // Include libraries here to avoid duplicating in cpp files
#include <GfxWrapper.h>
#include <Fonts/FreeMonoBoldOblique12pt7b.h>

extern VGA vga;                       
extern Mode mode;                     
extern GfxWrapper<VGA> gfx;  
extern const PinConfig pins;
extern int yellowPin;
extern int greenPin;;
extern int redPin;
extern int bluePin; 

//colour levels
extern int L;
extern int M;
extern int H;

struct MenuOption {
  String title;
  int xpos;
  int ypos;
};

void main_menu();
void pong_game();
void drawRect(int x_pos, int y_pos, int r,  int g, int b, int w, int h);
void moving_block();
void game_1();
void game_2();

#endif