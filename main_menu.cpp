#include "project_files.h"


int num_games = 4;
MenuOption* games = new MenuOption[num_games];

MenuOption selected_game = {"", NULL, NULL};

void draw_menu() {
  
  vga.clear(vga.rgb(0,0,L));
  drawRect(0,0, H,0,0, 5,5); //RED top left
  drawRect(mode.hRes-5,0, 0,H,0, 5,5); // GREEN top rigth
  drawRect(0,mode.vRes-5, H,L,H, 5,5); // pink bottom left
  drawRect(mode.hRes-5,mode.vRes-5, H,0,H, 5,5); //purple in bottom right
 
  gfx.setFont(&FreeMonoBoldOblique12pt7b);
  gfx.setTextColor(0xFFFF);
  gfx.setCursor(mode.hRes/2, 40);
  gfx.setTextSize(2);
  gfx.print("MAIN MENU");
  gfx.setTextSize(1);
  for (int i = 0; i < num_games; i++) {
    gfx.setCursor(games[i].xpos, games[i].ypos);
    gfx.print(games[i].title);
  }
}

void main_menu_loop() {
  Serial.println("main_menu_loop\n");
  //delay(50);
  int cursor = 0;
  int last_pressed_main = millis();
  draw_menu();

  while (1) {
  //displays cursor over game, press yellow pin to go hover over next game, green button to select game
    int curr_time = millis();
    if (curr_time - last_pressed_main > 200) {
      if (Controller_data.button1) {
        drawRect(games[cursor].xpos-15, games[cursor].ypos-10, 0,0,L, 15,15);
        gfx.setCursor(games[cursor].xpos, games[cursor].ypos);
        gfx.print(games[cursor].title);
        cursor++;
        cursor = cursor%(num_games);
        drawRect(games[cursor].xpos-15, games[cursor].ypos-10, 255,0,0, 15,15);
        gfx.setCursor(games[cursor].xpos, games[cursor].ypos);
        gfx.print(games[cursor].title);
        last_pressed_main = curr_time;
      } else if (Controller_data.button2) {
        selected_game = games[cursor];
      }
    }
    if (selected_game.title != "") {
      if (selected_game.title == "pong") {
        pong_game();
      } else if (selected_game.title == "moving block") {
        moving_block();
      } else if (selected_game.title == "game1") {
        game_1();
      } else if (selected_game.title == "game2") {
        game_2();
      } 
      selected_game = {"", NULL, NULL};
      draw_menu(); 
      //game exited, restart menu
      //cursor = -1; //maybe?
      Serial.println("RESET MENU\n");
      return;
    }
    vga.show();
  }
}



 
void main_menu() {
  Serial.print("main_menu\n");
  games[0] = {"pong", mode.hRes/2, mode.vRes/2-100};
  games[1] = {"moving block", mode.hRes/2, mode.vRes/2-50};
  games[2] = {"game1", mode.hRes/2, mode.vRes/2};
  games[3] = {"game2", mode.hRes/2, mode.vRes/2+50};

  
  int powerOn = 1;
  while (powerOn) {
    main_menu_loop();
    Serial.println("Resarting main_menu_loop\n");
  }
  main_menu_loop();
  
}


