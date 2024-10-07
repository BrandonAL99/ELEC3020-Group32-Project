#include "project_files.h";


void drawRect(int x_pos, int y_pos, int r,  int g, int b, int w, int h);
void drawBall(int x_pos, int y_pos, int radius, int r, int g, int b);
void drawBackground();
bool detectCollision();
void update_count();
void game_over();
void game_set();

MenuOption* pong_options = new MenuOption[3];
MenuOption selected_option = {"", NULL, NULL};
int num_options = 3;
int num_players;
bool game_running = false;

//Game window parameters
int gameWidth = mode.hRes-30;
int gameHeight = mode.vRes-30;
int X1 = 30;//(mode.hRes-gameWidth)/2;
int Y1 = 30;//(mode.vRes-gameHeight)/2;
int X2 = mode.hRes-30;//(mode.hRes+gameWidth)/2;
int Y2 = mode.vRes-30;//(mode.vRes+gameHeight)/2;

//paddle and ball parameters
int length = 70;
int width = 5;
int paddle1Y = mode.vRes/2 - length/2;
int paddle1X = X1+1.5*width;
int paddle2Y = mode.vRes/2 - length/2;
int paddle2X = X2-2.5*width;
int count = 0;
int ballX = mode.hRes/2;
int ballY = mode.vRes/2;
int ballR = 5;
int ballSpeedX = 1;//random(0, 2) * 2 - 1;
int ballSpeedY = random(-1, 2);
int paddleSpeed = 1;
int maxBallSpeed = 1;




void pong_loop() 
  {
    int cur_time; 
    int last_press = 0;
    drawBackground();
    vga.clear(vga.rgb(0,0,0));
    //drawRect(X1,Y1, 255,255,255, gameWidth, gameHeight);
    Serial.print("modehRes: " + String(mode.hRes) + "\n");
    Serial.print("gameWidth: " + String(gameWidth) + "\n");

    //}
    game_set();
    while (game_running) {
      //unsigned long start = millis();
      cur_time = millis();
      if (cur_time - last_press > 10) { 
        drawRect(paddle1X, paddle1Y, 0,0,0 , width, length);
        drawRect(paddle2X, paddle2Y, 0,0,0, width, length);
        drawBall(ballX, ballY, ballR, 0, 0, 0);

        ballX += ballSpeedX;
        ballY += ballSpeedY;
        
        if (digitalRead(yellowPin) == HIGH) {
          paddle1Y -= paddleSpeed;
        } else if (digitalRead(greenPin) == HIGH) {
          paddle1Y += paddleSpeed;
        }

        if (num_players == 2) {
          if (digitalRead(redPin) == HIGH) {
            paddle2Y -= paddleSpeed;
          } else if (digitalRead(bluePin) == HIGH) {
            paddle2Y += paddleSpeed;
          }
        } else if (num_players == 1) {
          if (ballY >= paddle2Y + 0.9*length) {
            paddle2Y+=paddleSpeed;
          } else if (ballY <= paddle2Y) {
            paddle2Y-=paddleSpeed;
          }
        }
    
         
        if (paddle1Y <= Y1) {
          paddle1Y = Y1 + 1;  
        } else if (paddle1Y >= Y2-length) {
          paddle1Y = Y2-length;
        }

        if (paddle2Y <= Y1) {
          paddle2Y = Y1 + 1;  
        } else if (paddle2Y >= Y2-length) {
          paddle2Y = Y2-length;
        }

        if (detectCollision()) {
          ballSpeedX *= -1;

          //ballSpeedX += random(-1, 2);
          ballSpeedX = max(ballSpeedX, -1*maxBallSpeed);
          ballSpeedX = min(ballSpeedX, maxBallSpeed);

          ballSpeedY += random(-1, 2);
          ballSpeedY = max(ballSpeedY, -1*maxBallSpeed);
          ballSpeedY = min(ballSpeedY, maxBallSpeed);
          if (ballX > mode.hRes/2 && num_players == 1) {
            count--;
          }
          count++;
          if (count%20 == 0) {
            maxBallSpeed*=1.2;
            paddleSpeed*=1.2;
          }
          ballX+=ballSpeedX;
        }
        

        if (ballY - ballR<= Y1) {
          ballSpeedY *= -1;
          ballY = Y1 + ballR + 1;
        } else if (ballY + ballR>= Y2) {
          ballSpeedY *= -1;
          ballY = Y2 - ballR - 1;
        }
        
        if (ballX - ballR - 1 <= X1 || ballX + ballR + 1 >= X2) {
          ballX = (X1+X2)/2;
          game_over();
          game_running = false;
        }
        

        update_count();
        drawRect(paddle1X, paddle1Y, 255,0,0 , width, length);
        drawRect(paddle2X, paddle2Y, 0,255,0, width, length);
        drawBall(ballX, ballY, ballR, 0, 0, 255);
        last_press = cur_time;
      }
      vga.show();
      
      //unsigned long elapsed = millis() - start;
      //Serial.println(elapsed);
    }
    return;
  }


  void drawBall(int x_pos, int y_pos, int radius, int r, int g, int b) {
    for (int x = x_pos - radius; x < x_pos + radius; x++) {
      for (int y = y_pos - radius; y < y_pos + radius; y++) {
        if ((x_pos-x)*(x_pos-x) + (y_pos-y)*(y_pos-y) <= radius*radius) {
          vga.dot(x,y,r,g,b);
        }
      }
    }
  }

  void drawBackground() {
    vga.clear(vga.rgb(0,0,0));

    for (int x = X1; x < X2; x++){
      vga.dot(x,Y1,255,255,255);
      vga.dot(x,Y2,255,255,255);
    } 
    for (int y = Y1; y < Y2; y++){
      vga.dot(X1,y,255,255,255);
      vga.dot(X2,y,255,255,255);
    } 
  }

  bool detectCollision() {
    if (ballX - ballR < paddle1X + width) {
      if (ballY + ballR > paddle1Y && ballY - ballR < paddle1Y + length) {
        return true;
      }
    }
    if (ballX + ballR > paddle2X) {
      if (ballY + ballR > paddle2Y && ballY - ballR < paddle2Y + length) {
        return true;
      }
    }
    return false;
  }

  void update_count() {
    gfx.setFont();
    gfx.setTextColor(vga.rgb(255,255,255),vga.rgb(0,0,0)) ;
    gfx.setTextSize(1);
    gfx.setCursor(X1,Y1-5);
    gfx.print(String(count));
  }

  void game_over() {
    ballSpeedX = 0;
    ballSpeedY = 0;
    paddleSpeed = 0;

    gfx.setCursor(X1+2.5*width, mode.vRes/2-25);
    gfx.setCursor(X1+10, 4*mode.vRes/16); 
    gfx.setTextSize(2);
    gfx.setTextColor(vga.rgb(0,0,255));
    gfx.print("GAME OVER!");

    gfx.setCursor(X1+10, 8*mode.vRes/16); 
    gfx.setTextSize(1);
    gfx.setTextColor(vga.rgb(255,255,255));
    gfx.print("Score: " + String(count) + "  Highscore: " + String(69));

    gfx.setCursor(X1+10, 12*mode.vRes/16); 
    gfx.setTextSize(1);
    gfx.setTextColor(vga.rgb(0,255,0));
    gfx.print("Press green button to go back to menu");
    vga.show();
    while (digitalRead(greenPin) == LOW) {
    }
    delay(500);

    return;


  }

  void game_set() {
      //Game window parameters
    gameWidth = mode.hRes-50;
    gameHeight = mode.vRes-50;
    X1 = (mode.hRes-gameWidth)/2;
    Y1 = (mode.vRes-gameHeight)/2;
    X2 = (mode.hRes+gameWidth)/2;
    Y2 = (mode.vRes+gameHeight)/2;
    //paddle and ball parameters
    length = 70;
    width = 5;
    paddle1Y = mode.vRes/2 - length/2;
    paddle1X = X1+1.5*width;
    paddle2Y = mode.vRes/2 - length/2;
    paddle2X = X2-2.5*width;
    count = 0;
    ballX = mode.hRes/2;
    ballY = mode.vRes/2;
    ballR = 5;
    ballSpeedX = 1;//random(0, 2) * 2 - 1;
    ballSpeedY = random(-1, 2);
    paddleSpeed = 1;
    maxBallSpeed = 1;

    drawBackground();
    ballSpeedX = 1;
    ballSpeedY = 1;
    paddleSpeed = 1;
    maxBallSpeed = 1;
    paddle1Y = mode.vRes/2 - length/2;
    paddle2Y = mode.vRes/2 - length/2;
    count = 0;
    ballX = mode.hRes/2;
    ballY = mode.vRes/2;
    game_running = true;
  }




void pong_menu_loop() {
  Serial.print("pong_game_menu\n");
  selected_option = {"", NULL, NULL};
  int last_pressed = millis(); 
  int cursor = 0;
  bool pong_menu_running = true;
  draw_menu(pong_options, "PONG", num_options);
  while (pong_menu_running) {
    //draw_pong_menu();
    int curr_time = millis();
    if (curr_time - last_pressed > 200) {
      if (digitalRead(yellowPin) == HIGH) {
        gfx.setTextColor(vga.rgb(2555,255,255));
        gfx.setCursor(pong_options[cursor].xpos, pong_options[cursor].ypos);
        gfx.print(pong_options[cursor].title);
        cursor++;
        cursor = cursor%(num_options);
        gfx.setTextColor(vga.rgb(0,255,0));
        //drawRect(options[cursor].xpos, options[cursor].ypos, 255, 0/*255/4 + 10, 0, 15,15);
        gfx.setCursor(pong_options[cursor].xpos, pong_options[cursor].ypos);
        gfx.print(pong_options[cursor].title);
        last_pressed = curr_time;
        vga.show();
      } else if (digitalRead(greenPin)==HIGH) {
        selected_option = pong_options[cursor];
      }
    }
    if(selected_option.title != "") {
      if (selected_option.title == "menu") {
        pong_menu_running = false;
        return;
      } else if (selected_option.title == "1p") {
        num_players = 1;
        pong_loop();
      } else if (selected_option.title == "2p") {
        num_players = 2;
        pong_loop();
      } else {
        Serial.println("WHAT HAPPENED: " + selected_option.title);
      }
      selected_option = {"", NULL, NULL};
      draw_menu(pong_options, "PONG", num_options);
    }
  }
  return; //goes to pong_game() if nothing happens
}


//analogous to setup() function, calls game menu which then calls gameplay
void pong_game() {
  
    
  Serial.print("pong_game\n");
  //draw_pong_menu();
  pong_options[0] = {"1p", mode.hRes/4-20, mode.vRes/2};
  pong_options[1] = {"2p", 3*mode.hRes/4-20, mode.vRes/2};
  pong_options[2] = {"menu", mode.hRes/2-40, 3*mode.vRes/4};  
  game_running = false;
  pong_menu_loop();
  return;
}
