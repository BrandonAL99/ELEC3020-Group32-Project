#ifndef __HEADER__
#define __HEADER__

#include "ESP32S3VGA.h"  // Include libraries here to avoid duplicating in cpp files
#include <GfxWrapper.h>
#include <Fonts/FreeMonoBoldOblique12pt7b.h>
#include <esp_now.h>
#include <WiFi.h>
#include <TFT_eSPI.h>

extern VGA vga;                       
extern Mode mode;                     
extern GfxWrapper<VGA> gfx;  
extern const PinConfig pins;
extern TFT_eSPI tft;// = TFT_eSPI();



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


typedef struct struc_inputs { //setup of datastructure which data is sent in, matches sender
  int start;
  int select;
  int button1;
  int button2;
  int button3;
  int button4;
  int button5;
  int button6;
  int JoyUp;
  int JoyDown;
  int JoyLeft;
  int JoyRight;
  }struc_inputs; //aliase that means we don't have to type struct every time defining structure

extern struc_inputs Controller_data;

void main_menu();
void pong_game();
void drawRect(int x_pos, int y_pos, int r,  int g, int b, int w, int h);
void moving_block();
void game_1();
void game_2();
void controller_setup();
void draw_menu(MenuOption *options, String title, int num_options);
void drawLine(int x0, int y0, int x1, int y1, uint16_t color);

#endif