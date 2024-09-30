#include "project_files.h"
int game_2_running;
int timer_game2;
int last_change_2;

void game_2_loop()
{

  if (Controller_data.button2 || timer_game2 <= 0) {
    game_2_running = 0;
    return;
  }

  int curr_time2 = millis();
  if (curr_time2 - last_change_2 >= 1000) {
    timer_game2--;
    drawRect(mode.hRes/2, mode.vRes/2+60, 0,0,255, 30,30);
    gfx.setCursor(mode.hRes/2, mode.vRes/2+80);
    gfx.print(String(timer_game2));
    last_change_2 = curr_time2;
  }
  vga.show();
}

void game_2() {
  game_2_running = 1;
  timer_game2 = 3;
  last_change_2 = 0;

  Serial.print("game_2\n");
  vga.clear(vga.rgb(0,L,0));
  gfx.setTextColor(0xFFFF);
  gfx.setCursor(mode.hRes/2, mode.vRes/2-100);
  gfx.print("No code for Game 1 yet");
  
  gfx.setCursor(mode.hRes/2, mode.vRes/2-50);
  gfx.print("Press blue button to return to menu");
  gfx.print(mode.hRes/2, mode.vRes/2+50);
  gfx.print("Returning to menu in: ");
  gfx.setCursor(mode.hRes/2, mode.vRes/2+80);
  gfx.print(String(timer_game2));

  vga.show();

  while (game_2_running) {
    game_2_loop();
  }
  return;
}