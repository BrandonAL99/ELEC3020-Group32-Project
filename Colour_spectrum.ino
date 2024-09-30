  #include "ESP32S3VGA.h"
  #include <TFT_eSPI.h>

  //                   r,r,r,r,r,  g,g, g, g, g, g,   b, b, b, b, b,   h,v
  //const PinConfig pins(4,5,6,7,8,  9,10,11,12,13,14,  15,16,17,18,21,  1,2);
  const PinConfig pins(-1,-1,-1,43,1,   -1,-1,-1,-1,44,2,    -1,-1,-1,18,3,  11,10);
  int yellowPin = -16;
  int greenPin =  -21;
  int redPin = -13;
  int bluePin = -12;

  int L = 255/4 + 10;
  int M = 255/2 + 10;
  int H = 255;
  VGA vga;
  Mode mode = Mode::MODE_800x600x60;//MODE_800x600x60;
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
    tft.setTextColor(TFT_WHITE);
    tft.drawString("Starting", 100,50);

    Serial.begin(115200);
    pinMode(yellowPin, INPUT);
    pinMode(greenPin, INPUT);
    pinMode(redPin, INPUT);
    pinMode(bluePin, INPUT);

    //VGAMode mode = MODE_1024x768x60;
    //if(!vgaInit(pins, mode, 8)) while(1) delay(1);

    
    if(!vga.init(pins, mode, 16)) while(1) delay(1);
    vga.bufferCount = 2;
    vga.start();
    vga.clear(vga.rgb(255,255,255));
    
    int squareSize = 30;
    for (int i = 0; i < 50; i++) {
      for (int j = 0; j < 50; j++) {
        vga.dot(i,j, 255,255,0);
      }
    }
    int colorLevels[4] = {0, L, M, H};
      // Iterate through all combinations of red and green
      vga.clear(vga.rgb(0,0,L));
      //vga.clear(vga.rgb(L,M,H));
      for (int r = 0; r < 4; r++) {
          for (int g = 0; g < 4; g++) {
              for (int b = 0; b < 4; b++) {
                  // Calculate the position for each square
                  int x = (r * 4 + g) * squareSize; // Spread horizontally
                  int y = b * squareSize; // Stack vertically
                
                  // Set the color based on the current combination
                  int red = colorLevels[r];
                  int green = colorLevels[g];
                  int blue = colorLevels[b];
                
                  // Draw the square
                  for (int i = 0; i < squareSize; i++) {
                      for (int j = 0; j < squareSize; j++) {
                          vga.dot(x + i, y + j, red, green, blue);
                      }
                  }
              }
          }
      }
    
    //vga.clear(vga.rgb(0, 0, 0));

    //vga.show();
    //vga.start();
  }

  void loop() 
  {
    /*
    static int screenRefreshTime = 0;
    int cur_time = millis();
    if (cur_time - last_change > 50) { 
      drawRect(x_pos, y_pos,0,0,0);
      if (digitalRead(yellowPin) == HIGH) {
        x_pos -= 10;
        tft.fillScreen(TFT_YELLOW);
        tft.drawString("L", 50,50);
      } else if (digitalRead(greenPin) == HIGH) {
        x_pos += 10;
        tft.fillScreen(TFT_GREEN);
        tft.drawString("R", 50,50);
      } else if (digitalRead(redPin) == HIGH) {
        y_pos += 10;
        tft.fillScreen(TFT_RED);
        tft.drawString("D", 50,50);
      } else if (digitalRead(bluePin) == HIGH) {
        y_pos -= 10;
        tft.fillScreen(TFT_BLUE);
        tft.drawString("U", 50,50);
      }      
      drawRect(x_pos, y_pos,255,255,0); 

      if (cur_time - screenRefreshTime > 100) {
        vga.show();
        screenRefreshTime = cur_time;
         last_change = cur_time;
      }
    }
    
    
  
  */
  }

  /*
  void drawRect(int x_pos, int y_pos, int r,  int g, int b) 
  {
    
    //vga.clear(vga.rgb(0, 0, 0));
    for(int y = y_pos%mode.vRes; y < 30+y_pos%mode.vRes; y++) {
      for(int x = x_pos%mode.hRes; x < 30+x_pos%mode.hRes; x++) {
        vga.dot(x, y, r,g,b);
      }
    }   

  }
  */
