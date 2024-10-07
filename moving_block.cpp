  #include "project_files.h"

  void moving_block_loop() 
  {
    Serial.println("moving_block_loop\n");
    int last_press = 0;
    
    int x_pos = 30;
    int y_pos = 30;
    int block_width = 30;
    int block_height = 30;
    int moving_block_running = 1;
    

    while (moving_block_running) {
      tft.fillScreen(TFT_BLACK);
      tft.drawString("joystick, 1: exit", 100, 80);
      tft.drawString("(" + String(x_pos) + "," + String(y_pos) + ")", 120, 200);

      drawRect(x_pos, y_pos,0,0,0, block_width, block_height);

      gfx.setCursor(1,1);
      int cur_time = millis();
      if (cur_time - last_press > 10) { 
        if (digitalRead(yellowPin) == HIGH) {
          x_pos -= 1;
        } 
        if (digitalRead(greenPin) == HIGH) {
          x_pos += 1;
        } 
        if (digitalRead(redPin) == HIGH) {
          y_pos += 1;
        } 
        //if (Controller_data.JoyDown) {
        //  y_pos -= 1;
        //}     
        if (digitalRead(bluePin) == HIGH) {
          return;
        }
        last_press = cur_time;
      }
      //gfx.setTextBackground(0, 0, 0);
      gfx.print("HELLO ");
      gfx.print("(" + String(x_pos) + "," + String(y_pos) + ")");
      
      
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
      drawRect(x_pos, y_pos,0,0,L, block_width, block_height);
      vga.show();
    }
  }


  void drawBoard() {
  vga.clear(vga.rgb(255,255,255));

  int border = 10;
  for (int x = border; x < mode.hRes - border; x++) { //red - top
    vga.dot(x,border,0,0,0);
  }
  for (int x = border; x < mode.hRes - border; x++) { //green - bottom
    vga.dot(x,mode.vRes-border,0,0,0);
  }
  for (int y = border; y < mode.vRes - border; y++) { //blue - left
    vga.dot(border, y,0,0,0);
  }
  for (int y = border; y < mode.vRes - border; y++) { //white - right
    vga.dot(mode.hRes-border, y,0,0,0);
  }

  }

  void moving_block()
  {
    tft.fillScreen(TFT_BLACK);
    tft.drawString("MOVING BLOCK GAME", 60,40);
    Serial.print("moving_block\n");
    //drawBoard();
    //drawRect(x_pos, y_pos, 125,0,125, block_width, block_height); 

    gfx.setCursor(100, 100);
    gfx.setFont();
    gfx.setTextColor(0x0000, 0xFFFF);
    delay(50);
    drawBoard();
    vga.show();
    moving_block_loop();
    return;

}



