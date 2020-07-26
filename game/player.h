#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include <f3d_lcd_sd.h>

typedef struct player_data {
  int x;
  int y;
  int prevX;
  int prevY;
  int width;
  int height;
  uint16_t color;
  float horiz_vel;
  int vert_vel;
} player;

player* create_player(int x, int y, int length);
int is_player_moving_upward(player*);
int is_player_falling(player*);
void draw_player(player*);
void teleport_player(player*, int x, int y);
void move_player(player*, int dir);
void set_player_velocities(player*, float horiz_vel, float vert_vel);
void set_player_horiz_vel(player*, float);
void set_player_vert_vel(player*, float);
void move_player_per_horiz_vel(player* plr);
void move_player_per_vert_vel(player* plr);
void player_die(player*);
void print_player(player*);
int rebound_player(player*);

#endif
