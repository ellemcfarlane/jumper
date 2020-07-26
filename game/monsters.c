#include "monsters.h"
#include "stdlib.h"

// initialize monsters to random within-range locations
void init_monsters(monster *monsters[]) {
  int x;
  int y;
  int n_mon;
  monster* mon;
  float speed = max(abs(mon->vert_vel), abs(mon->horiz_vel));

  for (n_mon = 0; n_mon < N_MONS; n_mon++) {
    x = rand_int(MIN_X, MAX_X-MONSTER_WIDTH);
    y = rand_int(MIN_Y+MONSTER_HEIGHT, MAX_Y);
    mon = create_monster(x, y, MONSTER_WIDTH);
    monsters[n_mon] = mon;
    set_rand_monster_movement(mon, MONSTER_SPEED);
  }
}

void change_direction_of_monsters(monster* monsters[]) {
  int n_mon;
  monster* mon;
  for (n_mon = 0; n_mon < N_MONS; n_mon++) {
    mon = monsters[n_mon];
    change_monster_direction(mon);
  }
}

// moves monsters per their vertical/horizontal velocities
void move_monsters(monster* monsters[]) {
  int n_mon;
  monster* mon;
  for (n_mon = 0; n_mon < N_MONS; n_mon++) {
    mon = monsters[n_mon];    
    move_monster_per_horiz_vel(mon);
    draw_monster(mon);
    keep_monster_on_screen_horiz(mon);
    draw_monster(mon);
    
    move_monster_per_vert_vel(mon);
    draw_monster(mon);
    keep_monster_on_screen_vert(mon);
    draw_monster(mon);
  }
}

// relocates monster roughly to min vert location if past max vert location
void keep_monster_on_screen_vert(monster* mon) {
  int top_edge = mon->y-mon->height;
  if (top_edge < MIN_Y) {
    teleport_monster(mon, mon->x, MAX_Y);
  }     
  else if (mon->y >= MAX_Y) {
    teleport_monster(mon, mon->x, MIN_Y+mon->height);
  } 
}

// relocates monster roughly to min horiz location if past max horiz location
void keep_monster_on_screen_horiz(monster* mon) {
  if (mon->x <= MIN_X) {
    teleport_monster(mon, MAX_X-mon->width-1, mon->y);
  }     
  else if (mon->x + mon->width >= MAX_X) {
    teleport_monster(mon, MIN_X+1, mon->y);
  } 
}

// if monster out of screen view after shift,
// it is reassigned to random x location at top of screen
// otherwise it is shifted down by the shift_amt
void shift_monsters(monster* monsters[], int shift_amt) {
  int new_y;
  int new_x;
  int rand_y;
  int rand_x;
  int shift_lmt = MAX_Y-shift_amt;
  monster *mon;
  int n_mon;

  for (n_mon = 0; n_mon < N_MONS; n_mon++) {
    mon = monsters[n_mon];
    rand_x = rand_int(MIN_X, MAX_X-MONSTER_WIDTH);
    //rand_y = rand_int(MIN_Y-mon->height, MAX_Y);
    // if out of screen view after shift, reassign to random location
    if (mon->y >= shift_lmt) {
      new_y = MIN_Y + MONSTER_HEIGHT;
      new_x = rand_x;
      teleport_monster(mon, new_x, new_y);
    }else {
      new_x = mon->x;
      new_y = mon->y+shift_amt;
      teleport_monster(mon, new_x, new_y);
    }
  }
}

void draw_monsters(monster *monsters[]) {
  int n_mon;
  for (n_mon = 0; n_mon < N_MONS; n_mon++) {
    monster *mon = monsters[n_mon];
    draw_monster(mon);
  }
}

void free_monsters(monster *monsters[]) {
  int n_mon;
  for (n_mon = 0; n_mon < N_MONS; n_mon++) {
    monster *mon = monsters[n_mon];
    free(mon);
 }
}
