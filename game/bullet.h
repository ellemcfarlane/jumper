#ifndef BULLET_H_INCLUDED
#define BULLET_H_INCLUDED

#include <f3d_lcd_sd.h>

typedef struct bullet_data {
  int x;
  int y;
  int prevX;
  int prevY;
  int width;
  int height;
  uint16_t color;
  int just_fired;
  float velocity;
} bullet;

bullet* create_bullet(int x, int y, int width);
void move_bullet(bullet*, int dir);
void teleport_bullet(bullet*, int x, int y);
void draw_bullet(bullet*);
void fire_bullet(bullet*, int speed);
void stop_bullet(bullet*);
void print_bullet(bullet*);

#endif

