#include "project_files.h"

//                   r,r,r,r,r,  g,g, g, g, g, g,   b, b, b, b, b,   h,v
//const PinConfig pins(4,5,6,7,8,  9,10,11,12,13,14,  15,16,17,18,21,  1,2);
const PinConfig pins(-1,-1,-1,43,1,   -1,-1,-1,-1,44,2,    -1,-1,-1,18,3,  11,10);

int yellowPin = 16;
int bluePin =  13;
int greenPin = 21;//13;
int redPin = 17;

int L = 255/4 + 10;
int M = 255/2 + 10;
int H = 255;

VGA vga;
Mode mode = Mode::MODE_320x240x60;//GPT_640x480x60;//MODE_800x600x60;
GfxWrapper<VGA> gfx(vga, mode.hRes, mode.vRes);
TFT_eSPI tft = TFT_eSPI();
  
void setup()
{
  Serial.begin(115200);
  Serial.print("Project_all\n");

  tft.init();
  tft.setTextSize(3);
  tft.setTextDatum(MC_DATUM);
  tft.setRotation(1);

  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_WHITE);
  tft.drawString("STARTING UP", 60, 40);
  
  pinMode(yellowPin, INPUT);
  pinMode(greenPin, INPUT);
  pinMode(redPin, INPUT);
  pinMode(bluePin, INPUT);
  
  
  if(!vga.init(pins, mode, 16)) while(1) delay(1);
  vga.bufferCount = 1;
  vga.clear(vga.rgb(0,0,0));
  gfx.setFont(&FreeMonoBoldOblique12pt7b);
  gfx.setCursor(mode.hRes/2, mode.vRes/2);
  gfx.setTextColor(vga.rgb(255,255,255));
  gfx.print("hello...");
  vga.start();
  Serial.println(); 
  controller_setup();
  main_menu();
}

void loop() 
{
  vga.show();
}


