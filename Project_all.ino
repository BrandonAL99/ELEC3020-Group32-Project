//consider non blocking function to update screen after each modificaiton.

//#include "ESP32S3VGA.h"
//#include <TFT_eSPI.h>
//#include <GfxWrapper.h>

#include "project_files.h"

//                   r,r,r,r,r,  g,g, g, g, g, g,   b, b, b, b, b,   h,v
//const PinConfig pins(4,5,6,7,8,  9,10,11,12,13,14,  15,16,17,18,21,  1,2);
const PinConfig pins(-1,-1,-1,43,1,   -1,-1,-1,-1,44,2,    -1,-1,-1,18,3,  11,10);
int yellowPin = 16;
int greenPin =  21;
int redPin = 13;
int bluePin = 12;
int L = 255/4 + 10;
int M = 255/2 + 10;
int H = 255;

//for 6-bit colour
//nt L = 255/4 + 10;
//int M = 255/2 + 10;
//int H = 255;


VGA vga;
Mode mode = Mode::MODE_640x480x60;//GPT_640x480x60;//MODE_800x600x60;
GfxWrapper<VGA> gfx(vga, mode.hRes, mode.vRes);
  
void setup()
{
  Serial.begin(115200);
  Serial.print("Project_all\n");
  //Serial.println("Setting pinModes\n");
  pinMode(yellowPin, INPUT);
  pinMode(greenPin, INPUT);
  pinMode(redPin, INPUT);
  pinMode(bluePin, INPUT);
  //Serial.println("Starting VGA\n");
  if(!vga.init(pins, mode, 16)) while(1) delay(1);
  vga.bufferCount = 1;
  vga.start();
  Serial.println();
  Serial.println();
  Serial.println();
  Serial.println(); 
  main_menu();
}

void loop() 
{
  vga.show();
}


