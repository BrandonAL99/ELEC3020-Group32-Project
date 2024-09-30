  #include "ESP32S3VGA.h"
  #include <TFT_eSPI.h>

  //                   r,r,r,r,r,  g,g, g, g, g, g,   b, b, b, b, b,   h,v
  //const PinConfig pins(4,5,6,7,8,  9,10,11,12,13,14,  15,16,17,18,21,  1,2);
  const PinConfig pins(-1,-1,-1,43,1,   -1,-1,-1,-1,44,2,    -1,-1,-1,18,3,  11,10);
  int yellowPin = 14;
  int greenPin =  -21;
  int redPin = -13;
  int bluePin = -12;

  int L = 255/4 + 10;
  int M = 255/2 + 10;
  int H = 255;
  int last_refresh = 0;

  VGA vga;
  Mode mode = Mode::GPT_640x480x60;//MODE_800x600x60;
  TFT_eSPI tft = TFT_eSPI();

   
  int x_pos = 30;
  int y_pos = 30;
  int last_change = 0;
  
  void setup()
  {
    tft.init();
    tft.setTextSize(3);
    tft.setTextDatum(MC_DATUM);
    tft.fillScreen(TFT_BLACK);
    tft.setTextColor(TFT_GREEN);
    tft.drawString("Starting", 100,50);

    Serial.begin(19200);
    pinMode(yellowPin, INPUT_PULLUP);
    pinMode(greenPin, INPUT);
    pinMode(redPin, INPUT);
    pinMode(bluePin, INPUT);

    //VGAMode mode = MODE_1024x768x60;
    //if(!vgaInit(pins, mode, 8)) while(1) delay(1);

    
    if(!vga.init(pins, mode, 16)) while(1) delay(1);
    vga.bufferCount = 1;
    
    
    drawBoard();
    
    drawRect(x_pos, y_pos,255,0,255); 
    //delay(2000);
    vga.start();
    //vga.show();


  }

  void loop() 
  {
    static int last_press = 0;
    static int yellow = 1;
    int current_time = millis();
    if (current_time - last_press >= 200) {
      if (digitalRead(yellowPin) == LOW) {
        drawRect(x_pos, y_pos, 125,255,255);
        x_pos++;

        y_pos++;
        if (yellow == 1) {
          tft.fillScreen(TFT_YELLOW);
          yellow = 0;
        } else {
          tft.fillScreen(TFT_BLACK);
          yellow = 1;
        }
        //delay(200);
        
        //vga.show();
      }
      //vga.show();
      last_press = current_time;
    }
    vga.show();
  }

  void drawRect(int x_pos, int y_pos, int r,  int g, int b) 
  {
    
    //vga.clear(vga.rgb(0, 0, 0));
    for(int y = y_pos/*%mode.vRes*/; y < 30+y_pos/*%mode.vRes*/; y++) {
      for(int x = x_pos/*%mode.hRes*/; x < 30+x_pos/*%mode.hRes*/; x++) {
        vga.dot(x, y, r,g,b);
      }
    }   

  }

  void drawBoard()
  {
    int border = 10;
    
    for (int x = border; x < mode.hRes - border; x++) { //red - top
      vga.dot(x,border,255,0,0);
    }
    for (int x = border; x < mode.hRes - border; x++) { //green - bottom
      vga.dot(x,mode.vRes-border,0,255,0);
    }
    for (int y = border; y < mode.vRes - border; y++) { //blue - left
      vga.dot(border, y,0,0,255);
    }
    for (int y = border; y < mode.vRes - border; y++) { //white - right
      vga.dot(mode.hRes-border, y,0,0,0);
    }
  }

  