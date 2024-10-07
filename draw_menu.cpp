#include "project_files.h"

int xborder = 20;
int yborder = 20;

void draw_menu(MenuOption *options, String title, int num_options) {
  vga.clear(vga.rgb(255,0,0));
  int tempColourCount = 0;
  int num_col = 7;
  uint16_t colour_array[num_col] = {vga.rgb(255,0,0), vga.rgb(255,M,0), vga.rgb(255,255,0), vga.rgb(0,255,0), vga.rgb(0,0,255),vga.rgb(L,0,M),vga.rgb(255,0,255)};  
  uint16_t ci = 0;
  
  for (int y=0; y < mode.vRes; y++) {
    tempColourCount++;
    if (tempColourCount%15 == 0) {
      ci++;
      ci%=num_col;
    }
    drawLine(0, y, y, 0, colour_array[ci]);
  }
  for (int x = 0; x < mode.hRes; x++) {
    tempColourCount++;
    if (tempColourCount%15 == 0) {
      ci++;
      ci%=num_col;
    }
    drawLine(x, mode.vRes, x+mode.vRes, 0,  colour_array[ci]);
  }
  drawRect(xborder, yborder, 0,0,0, mode.hRes-2*xborder, mode.vRes-2*yborder);
  
  gfx.setFont(&FreeMonoBoldOblique12pt7b);
  gfx.setTextColor(0xFFFF);
  Serial.println(title + ":" + String(title.length()));
  gfx.setCursor(mode.hRes/2 - title.length()*0.0875*0.5*mode.hRes, 4*mode.vRes/16); //calculated using ruler, centres title
  gfx.setTextSize(2);
  gfx.print(title);
  gfx.setTextSize(1);
  for (int i = 0; i < num_options; i++) {
    gfx.setCursor(options[i].xpos, options[i].ypos);
    gfx.print(options[i].title);
  }
  delay(10);
  vga.show();
}