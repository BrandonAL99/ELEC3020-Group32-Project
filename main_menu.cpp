#include "project_files.h"


int num_games = 4;
MenuOption* games = new MenuOption[num_games];

MenuOption selected_game = {"", NULL, NULL};


void main_menu_loop() {
  Serial.println("main_menu_loop\n");
  //delay(50);
  int cursor = 0;
  int last_pressed_main = millis();
  
  tft.drawString("1: scroll, 2: select", 100, 80);
  int xShift = 0;
  int yShift = 0;
  draw_menu(games, "MAIN MENU", num_games);
  while (1) {
    
    xShift = (xShift+1)%mode.hRes;
    yShift = (yShift+1)%mode.vRes;
  //displays cursor over game, press yellow pin to go hover over next game, green button to select game
    int curr_time = millis();
    if (curr_time - last_pressed_main > 200) {
      tft.fillScreen(TFT_BLACK);
      tft.drawString("MAIN MENU", 60,40);
      tft.drawString("1: scroll, 2: select", 100, 80);
      tft.drawString(games[cursor].title, 130, 110);
      if (digitalRead(yellowPin) == HIGH) { //scroll
        //drawRect(games[cursor].xpos-15, games[cursor].ypos-10, 0,0,L, 15,15);
        gfx.setTextColor(vga.rgb(255,255,255));
        gfx.setCursor(games[cursor].xpos, games[cursor].ypos);
        gfx.print(games[cursor].title);
        cursor++;
        cursor = cursor%(num_games);
        gfx.setTextColor(vga.rgb(0,255,0));
        gfx.setCursor(games[cursor].xpos, games[cursor].ypos);
        gfx.print(games[cursor].title);
        last_pressed_main = curr_time;
        vga.show();
      } else if (digitalRead(greenPin) == HIGH) {//select
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
    //draw_menu(); 
      //game exited, restart menu
      //cursor = -1; //maybe?
      Serial.println("RESET MENU\n");
      return;
    }
    
  }
}



 
void main_menu() {
  tft.fillScreen(TFT_BLACK);
  tft.drawString("MAIN MENU", 40,60);
  Serial.print("main_menu\n");
  games[0] = {"pong", mode.hRes/2 - 4*0.0875*0.25*mode.hRes, 6*mode.vRes/16};
  games[1] = {"moving block", mode.hRes/2 - 11*0.0875*0.25*mode.hRes, 8*mode.vRes/16};
  games[2] = {"game1", mode.hRes/2 - 5*0.0875*0.25*mode.hRes, 10*mode.vRes/16};
  games[3] = {"game2", mode.hRes/2 - 5*0.0875*0.25*mode.hRes, 12*mode.vRes/16};

  
  int powerOn = 1;
  while (powerOn) {
    main_menu_loop();
    Serial.println("Resarting main_menu_loop\n");
  }
  main_menu_loop();
  
}



