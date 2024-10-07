#include "project_files.h"

void drawRect(int x_pos, int y_pos, int r, int g, int b, int w, int h) 
{
  for (int y = y_pos % mode.vRes; y < h + y_pos % mode.vRes; y++) {
      for (int x = x_pos % mode.hRes; x < w + x_pos % mode.hRes; x++) {
          vga.dot(x, y, r, g, b);
      }
  }
}
