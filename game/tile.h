#ifndef TILE_H_INCLUDED
#define TILE_H_INCLUDED

#include <f3d_lcd_sd.h>

typedef struct tile_data {
  int x;
  int y;
  int prevX;
  int prevY;
  int width;
  int height;
  uint16_t color;
} tile;

tile* create_tile(int x, int y, int width, int height);
void draw_tile(tile*);
void teleport_tile(tile*, int x, int y);

#endif
