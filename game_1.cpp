#include "project_files.h"
int game_1_running;
int timer_game1;
int last_change_1;

void game_1_loop()
{

  if (Controller_data.button2 || timer_game1 <= 0) {
    game_1_running = 0;
    return;
  }

  int curr_time1 = millis();
  if (curr_time1 - last_change_1 >= 1000) {
    timer_game1--;
    drawRect(mode.hRes/2, mode.vRes/2+80, 0,0,255, 30,30);
    gfx.setCursor(mode.hRes/2, mode.vRes/2+80);
    gfx.print(String(timer_game1));
    last_change_1 = curr_time1;
  }
  vga.show();
}

void game_1() {
  game_1_running = 1;
  timer_game1 = 3;
  last_change_1 = 0;
  
  Serial.print("game_1\n");
  vga.clear(vga.rgb(0,L,0));
  gfx.setTextColor(0xFFFF);
  gfx.setCursor(mode.hRes/2, mode.vRes/2-100);
  gfx.print("No code for Game 1 yet");
  
  gfx.setCursor(mode.hRes/2, mode.vRes/2-50);
  gfx.print("Press button2 to return to menu");
  gfx.print(mode.hRes/2, mode.vRes/2+50);
  gfx.print("Returning to menu in: ");
  gfx.setCursor(mode.hRes/2, mode.vRes/2+80);
  gfx.print(String(timer_game1));

  vga.show();

  while (game_1_running) {
    game_1_loop();
  }
  return;
}