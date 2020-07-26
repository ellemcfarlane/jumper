// monster.c

#include <stdio.h>
#include <stdlib.h>
#include "common_defs.h"
#include "monster.h"

monster* create_monster(int x, int y, int width) {
  monster* mon = malloc(sizeof(monster));
  mon->x = x;
  mon->y = y;
  mon->width = width;
  mon->height = width;
  mon->color = BLUE;
  mon->prevX = x;
  mon->prevY = y;
  mon->horiz_vel = 0;
  mon->vert_vel = 0;
  return mon;
}

void set_rand_monster_movement(monster* mon, float speed) {
  int vertical_mover;
  int vel_dir;
  vertical_mover = rand_int(0,1); // decides if monster will move vertically
  vel_dir = rand_int(0,1) ? -1 : 1;
  if (vertical_mover) {
    set_monster_velocities(mon, 0, speed*vel_dir);
  }else{//horizontal mover
    set_monster_velocities(mon, speed*vel_dir, 0);
  }  
}

void set_monster_velocities(monster* mon, float horiz_vel, float vert_vel) {
  mon->horiz_vel = horiz_vel;
  mon->vert_vel = vert_vel;  
}

// removes drawing at previous position
// and draws at new position
void draw_monster(monster* mon) {
    f3d_lcd_drawRect(mon->prevX, mon->prevY,
		     mon->width, mon->height, BACKGROUND);
    f3d_lcd_drawRect(mon->x, mon->y, mon->width, mon->height, mon->color);
}

void teleport_monster(monster* mon, int x, int y) {
  mon->prevX = mon->x;
  mon->prevY = mon->y;
  mon->x = x;
  mon->y = y;
}

void move_monster(monster* mon, int dir) {
  mon->prevX = mon->x;
  mon->prevY = mon->y;
  switch(dir){
    case LEFT:
      mon->x -= 1;
      break;
    case UP:
      mon->y -= 1;
      break;
    case RIGHT:
      mon->x += 1;
      break;
    case DOWN:
      mon->y += 1;
      break;
  }
}

// reassign monster to random x location at top of screen
void reincarnate_monster(monster *mon, int min_x, int max_x,
			 int min_y, int max_y) {
  float speed = max(abs(mon->vert_vel), abs(mon->horiz_vel));  
  int rand_x = rand_int(min_x, max_x-mon->width);
  teleport_monster(mon, rand_x, min_y+mon->height);
  set_rand_monster_movement(mon, speed);
}

// moves monster up or down per vertical velocity's direction
void move_monster_per_vert_vel(monster* mon) {
  if (mon->vert_vel < 0) {
    move_monster(mon, UP);
  }
  else if (mon->vert_vel > 0) {
    move_monster(mon, DOWN);
  }
}

// moves monster left or right per horizontal velocity's direction
void move_monster_per_horiz_vel(monster* mon) {
  if (mon->horiz_vel > 0) {
    move_monster(mon, LEFT);
  }
  else if (mon->horiz_vel < 0) {
    move_monster(mon, RIGHT);
  }
}

void change_monster_direction(monster* mon) {
  set_monster_velocities(mon, -1*mon->horiz_vel, -1*mon->vert_vel);
}

void print_monster(monster* mon) {
  printf("%s", "monster {\n");
  printf("\t loc: (%d,%d)\n", mon->x, mon->y);
  printf("\t len: %d\n", mon->width);
  printf("}\n");
}

