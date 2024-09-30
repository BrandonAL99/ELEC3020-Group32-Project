  #include "ESP32S3VGA.h"
  //#include <TFT_eSPI.h>
  #include <GfxWrapper.h>
  //#include <Fonts/FreeMonoBoldOblique12pt7b.h>

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

  VGA vga;
  Mode mode = Mode::GPT_640x480x60;//MODE_800x600x60;
  //TFT_eSPI tft = TFT_eSPI();
  GfxWrapper<VGA> gfx(vga, mode.hRes, mode.vRes);
   
  int x_pos = 30;
  int y_pos = 30;

  hw_timer_t *timer = NULL;
  volatile int needShow = 0;
  void IRAM_ATTR onTimer() {
    needShow = 1;  // Update the VGA screen at regular intervals
  }

  void setup()
  {
    timer = timerBegin(0, 80, true);               // Timer 0, prescaler 80, count up
    timerAttachInterrupt(timer, &onTimer, true);   // Attach interrupt to timer
    timerAlarmWrite(timer, 16666, true);           // Set the timer to 16666µs for 60Hz refresh rate
    timerAlarmEnable(timer);

    Serial.begin(115200);
    Serial.println("Creating TFT\n");
    /*
    tft.init();
    tft.setTextSize(3);
    tft.setTextDatum(MC_DATUM);
    tft.fillScreen(TFT_BLACK);
    tft.setTextColor(TFT_PINK);
    //tft.drawString("Starting", 100,50);
    */
    Serial.println("Setting pinModes\n");
    pinMode(yellowPin, INPUT);
    pinMode(greenPin, INPUT);
    pinMode(redPin, INPUT);
    pinMode(bluePin, INPUT);

    //VGAMode mode = MODE_1024x768x60;
    //if(!vgaInit(pins, mode, 8)) while(1) delay(1);

    Serial.println("Starting VGA\n");
    if(!vga.init(pins, mode, 16)) while(1) delay(1);
    vga.bufferCount = 1;

    Serial.println("Drawing onto VGA\n");
    drawBoard();
    drawRect(x_pos, y_pos, 125,0,125); 
    Serial.println("...waiting...\n");
    Serial.println("starting and showing VGA\n");
    //vga.show();
    vga.start();
    gfx.setCursor(100, 100);
    //gfx.setFont(&FreeMonoBoldOblique12pt7b);
    gfx.setFont();
    //gfx.setTextSize(0.1);
    
  }

  void loop() 
  {
    static int last_press = 0;
    int cur_time = millis();

    if (cur_time - last_press > 10) { 
      drawRect(x_pos, y_pos,255,255,255);
      gfx.setCursor(1,1);

      gfx.setTextColor(0x0000, 0xFFFF);
      //gfx.setTextBackground(0, 0, 0);
      gfx.print("HELLO");
      gfx.print("(" + String(x_pos) + "," + String(y_pos) + ")");
      if (digitalRead(yellowPin) == HIGH) {
        x_pos -= 1;
        //tft.fillScreen(TFT_BLACK);
        //tft.drawString("L", 50,50);
      } else if (digitalRead(greenPin) == HIGH) {
        x_pos += 1;
        //tft.fillScreen(TFT_BLACK);
        //tft.drawString("R", 50,50);
      }
      if (digitalRead(redPin) == HIGH) {
        y_pos += 1;
        //tft.fillScreen(TFT_BLACK);
        //tft.drawString("D", 50,50);
      } else if (digitalRead(bluePin) == HIGH) {
        y_pos -= 1;
        //tft.fillScreen(TFT_BLACK);
        //tft.drawString("U", 50,50);
      }     
      
      if (x_pos < 0) {
        x_pos = mode.hRes - 1;  // Wrap to the right edge
      } else if (x_pos >= mode.hRes) {
        x_pos = 0;  // Wrap to the left edge
      }

      if (y_pos < 0) {
        y_pos = mode.vRes - 1;  // Wrap to the bottom edge
      } else if (y_pos >= mode.vRes) {
        y_pos = 0;  // Wrap to the top edge
      }
      drawRect(x_pos, y_pos,0,255,125);
      last_press = cur_time;
    }

    if (needShow == 1) {
      vga.show();
      needShow = 0;
    }
    //tft.drawString("(" + String(x_pos) + "," + String(y_pos) + ")", 70, 100);
    
  }

  void drawRect(int x_pos, int y_pos, int r,  int g, int b) 
  {
    
    //vga.clear(vga.rgb(0, 0, 0));
    //Serial.println("line 129\n");
    for(int y = y_pos%mode.vRes; y < 30+y_pos%mode.vRes; y++) {
      for(int x = x_pos%mode.hRes; x < 30+x_pos%mode.hRes; x++) {
        vga.dot(x, y, r,g,b);
      }
    }   
    //Serial.println("line 137\n");

  }

  void drawBoard() {
    vga.clear(vga.rgb(0,L,0));
    
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



  