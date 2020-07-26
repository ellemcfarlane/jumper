// player.c
#include <stdio.h>
#include <stdlib.h>
#include <f3d_delay.h>
#include "player.h"
#include "common_defs.h"

player* create_player(int x, int y, int width){
  player* plr = malloc(sizeof(player));
  plr->x = x;
  plr->y = y;
  plr->width = width;
  plr->height = width;
  plr->prevX = x;
  plr->prevY = y;
  plr->horiz_vel = 0;
  plr->vert_vel = 0;
  plr->color = GREEN;
  return plr;
}

// returns 1 if true, 0 otherwise
int is_player_falling(player* plr) {
  return plr->vert_vel > 0;
}

// returns 1 if true, 0 otherwise
int is_player_moving_upward(player* plr) {
  return plr->vert_vel < 0;
}

// removes drawing at previous position
// and draws at new position
void draw_player(player* plr) {
  f3d_lcd_drawRect(plr->prevX, plr->prevY,
		   plr->width, plr->height,
		   BACKGROUND);
  f3d_lcd_drawRect(plr->x, plr->y,
		   plr->width, plr->height,
		   plr->color);
}

void teleport_player(player* plr, int x, int y) {
  plr->prevX = plr->x;
  plr->prevY = plr->y;
  plr->x = x;
  plr->y = y;
}

int rebound_player(player* plr) {
  set_player_vert_vel(plr, -1*plr->vert_vel);
}

void set_player_vert_vel(player* plr, float vert_vel) {
  plr->vert_vel = vert_vel;
}

void set_player_horiz_vel(player* plr, float horiz_vel) {
  plr->horiz_vel = horiz_vel;
}

void set_player_velocities(player* plr, float horiz_vel, float vert_vel) {
  set_player_horiz_vel(plr, horiz_vel);  
  set_player_vert_vel(plr, vert_vel);
}

void move_player(player* plr, int dir) {
  plr->prevX = plr->x;
  plr->prevY = plr->y;
  switch(dir){
    case LEFT:
      plr->x -= 1;
      break;
    case UP:
      plr->y -= 1;
      break;
    case RIGHT:
      plr->x += 1;
      break;
    case DOWN:
      plr->y += 1;
      break;
  }
}

// moves player up or down per vertical velocity's direction
void move_player_per_vert_vel(player* plr) {
  if (plr->vert_vel < 0) {
    move_player(plr, UP);
  }
  else if (plr->vert_vel > 0) {
    move_player(plr, DOWN);
  }
}

// moves player left or right per horizontal velocity's direction
void move_player_per_horiz_vel(player* plr) {
  if (plr->horiz_vel > 0) {
      move_player(plr, LEFT);
  }
  else if (plr->horiz_vel < 0) {
      move_player(plr, RIGHT);
  }
}

void print_player(player* plr) {
  printf("player {\n");
  printf("\tloc: (%d,%d)\n", plr->x, plr->y);
  printf("\tprev: (%d,%d)\n", plr->prevX, plr->prevY);  
  printf("\twidth: %d\n\t", plr->width);
  printf("}\n");
}
