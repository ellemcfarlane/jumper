#ifndef MONSTER_H_INCLUDED
#define MONSTER_H_INCLUDED

#include <f3d_lcd_sd.h>

typedef struct monster_data {
  int x;
  int y;
  int prevX;
  int prevY;
  int width;
  int height;
  float horiz_vel;
  float vert_vel;
  uint16_t color;
} monster;

monster* create_monster(int x, int y, int width);
void draw_monster(monster*);
void teleport_monster(monster*, int x, int y);
void set_monster_velocities(monster*, float horiz_vel, float vert_vel);
void set_rand_monster_movement(monster*, float speed);
void move_monster(monster*, int dir);
void reincarnate_monster(monster *mon,
			 int min_x, int max_x,int min_y, int max_y);
void move_monster_per_vert_vel(monster*);
void move_monster_per_horiz_vel(monster*);
void print_monster(monster*);

#endif

