#include <stdlib.h>
#include "tile.h"
#include "common_defs.h"

tile* create_tile(int x, int y, int width, int height) {
  tile* tl = malloc(sizeof(tile));
  tl->x = x;
  tl->y = y;
  tl->prevX = x;
  tl->prevY = y;
  tl->width = width;
  tl->height = height;
  tl->color = WHITE;
  return tl;
}

// removes drawing at previous position
// and draws at new position
void draw_tile(tile* tl) {
  f3d_lcd_drawRect(tl->prevX, tl->prevY, tl->width, tl->height, BACKGROUND);
  f3d_lcd_drawRect(tl->x, tl->y, tl->width, tl->height, tl->color);
}

void teleport_tile(tile* tl, int x, int y) {
  tl->prevX = tl->x;
  tl->prevY = tl->y;
  tl->x = x;
  tl->y = y;
}
