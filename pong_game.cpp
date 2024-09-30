#include "project_files.h"
int num_players;


MenuOption options[] = {
  {"1p", mode.hRes/2, 160},
  {"2p", mode.hRes/2, 130},
  {"menu", mode.hRes/2, 50}
};

MenuOption selected_option = {"", NULL, NULL};
int num_options = 3;

void draw_pong_menu(){
  vga.clear(vga.rgb(0,0,120));
  gfx.setTextColor(0xFFFF);
  gfx.setCursor(mode.hRes/2, 20);
  gfx.setTextSize(3);
  gfx.print("Pong");

  gfx.setTextSize(1);
  for (int i = 0; i < num_options; i++) {
    gfx.setCursor(options[i].xpos, options[i].ypos);
    gfx.print(options[i].title);
  }

}

void pong_loop()
{
  Serial.print("pong_game_loop\n");

  int pong_running = 1;
  //while (pong_running) {
    vga.clear(vga.rgb(0,0,0));  
    drawRect(2,100, 0,H,0, 5, 200); //green on left side
    drawRect(mode.hRes-7,100, H,0,0, 5, 200); //red on right side
    Serial.print("PONG thinks h and v res are (" + String(mode.hRes) + "," + String(mode.vRes)+ ")\n");
    drawRect(0,0, H,0,0, 5,5); //RED top left
    drawRect(mode.hRes-5,0, 0,M,0, 5,5); // GREEN top rigth
    drawRect(0,mode.vRes-5, H,L,H, 5,5); // pink bottom left
    drawRect(mode.hRes-5,mode.vRes-5, H,0,H, 5,5); //purple in bottom right
    gfx.setCursor(mode.hRes/2, mode.vRes/2);
    gfx.print("No pong code yet :(");
    gfx.setCursor(mode.hRes/2, mode.vRes/2+35);
    gfx.print("press blue to exit");
    delay(50);
    vga.show();
  while (pong_running) {
    if (Controller_data.button3) {
      pong_running = 0;
    }
  }
    //delay(16);
  return;  //back to pong_menu
}

void pong_menu_loop() {
  Serial.print("pong_game_menu\n");

  int last_pressed = millis(); 
  int cursor = 0;
  int pong_menu_running = 1;
  while (pong_menu_running) {
    //draw_pong_menu();
    int curr_time = millis();
    if (curr_time - last_pressed > 200) {
      if (Controller_data.button1) {
        drawRect(options[cursor].xpos, options[cursor].ypos, 0, 0/*255/4 + 10*/, 120, 15,15);
        cursor++;
        cursor = cursor%(num_options);
        drawRect(options[cursor].xpos, options[cursor].ypos, 255, 0/*255/4 + 10*/, 0, 15,15);
        gfx.setCursor(options[cursor].xpos, options[cursor].ypos);
        gfx.print(options[cursor].title);
        last_pressed = curr_time;
        Serial.print("1\n");
      } else if (Controller_data.button2) {
        selected_option = options[cursor];
        Serial.print("2\n");
      }
    }
    if(selected_option.title != "") {
      Serial.print("3\n");
      if (selected_option.title == "menu") {
        Serial.print("1\n");
        pong_menu_running = 0;
        selected_option = {"", NULL, NULL};
        return;
      } else if (selected_option.title == "1p") {
        num_players = 1;
        pong_loop();
      } else if (selected_option.title == "2p") {
        num_players = 2;
        pong_loop();
      } 
      selected_option = {"", NULL, NULL};
      //vga.clear(vga.rgb(0,0,L));
     
      draw_pong_menu();    
    }
    vga.show();
  }
  return; //goes to pong_game() if nothing happens
}



void pong_game() {
  Serial.print("pong_game\n");
  draw_pong_menu();
  
  pong_menu_loop();
  return;
}