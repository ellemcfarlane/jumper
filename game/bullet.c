// bullet.c
#include <stdlib.h>
#include <stdio.h>
#include "bullet.h"
#include "common_defs.h"

bullet* create_bullet(int x, int y, int width) {
  bullet* bul = malloc(sizeof(bullet));
  bul->prevX = x;
  bul->prevY = y;
  bul->x = x;
  bul->y = y;
  bul->width = width;
  bul->height = width;
  bul->color = RED;
  bul->just_fired = 0;
  bul->velocity = 0;
  return bul;
}

void fire_bullet(bullet* bul, int speed) {
  bul->just_fired = 1;
  bul->velocity = -speed;
}

void stop_bullet(bullet* bul) {
  bul->just_fired = 0;
  bul->velocity = 0;
}

void move_bullet(bullet* bul, int dir) {
  bul->prevX = bul->x;
  bul->prevY = bul->y;
  switch(dir){
    case LEFT:
      bul->x -= 1;
      break;
    case UP:
      bul->y -= 1;
      break;
    case RIGHT:
      bul->x += 1;
      break;
    case DOWN:
      bul->y += 1;
      break;
  }
}

void teleport_bullet(bullet* bul, int x, int y) {
  bul->prevX = bul->x;
  bul->prevY = bul->y;
  bul->x = x;
  bul->y = y;
}


// removes drawing at previous position
// and draws at new position
void draw_bullet(bullet* bul) {
  f3d_lcd_drawRect(bul->prevX, bul->prevY,
		   bul->width, bul->width,
		   BACKGROUND);
  if (bul->just_fired == 1) {
    f3d_lcd_drawRect(bul->x, bul->y,
		     bul->width, bul->width,
		     bul->color);
  }
}

void print_bullet(bullet* bul) {
  printf("bullet {\n");
  printf("\t loc: (%d,%d)\n", bul->x, bul->y);
  printf("}\n");
}
