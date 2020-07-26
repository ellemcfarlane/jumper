#include "bullets.h"
#include "game_constants.h"
#include "common_defs.h"

void init_bullets(bullet *bullets[]) {
  int n_bullet;
  for (n_bullet = 0; n_bullet < N_BULLETS; n_bullet++) {
    bullets[n_bullet] = create_bullet(0, 0, BULLET_WIDTH);
  }
}

// moves bullets that have been fired
// returns points from any monsters killed by bullets
int move_live_bullets(bullet *bullets[], monster *monsters[]) {
  int n_bullet = 0;
  bullet *bul;
  monster *mon;
  int hit_mon_idx;
  int add_to_score = 0;
  for (n_bullet; n_bullet < N_BULLETS; n_bullet++) {
    bul = bullets[n_bullet];
    if (bul->just_fired) {
      add_to_score = handle_live_bullet(bul, monsters);
      draw_bullet(bul);
    }
  }
  return add_to_score;
}

// deactivates bullets that go off screen
// kills monsters when shot
int handle_live_bullet(bullet* bul, monster *monsters[]) {
  int bullet_on_screen = 0;  
  int add_to_score = 0;
  bullet_on_screen = bul->y >= MIN_Y+bul->height-1;
  if (!bullet_on_screen) {
    stop_bullet(bul);
  }
  else {
    add_to_score = bullet_monsters_interaction(bul, monsters);	
    move_bullet(bul, UP);
  }
  return add_to_score;
}

// returns 15 if monster shot, 0 otherwise
int bullet_monsters_interaction(bullet* bul, monster *monsters[]) {
  int add_to_score = 0;  
  int hit_mon_idx = get_monster_bullet_hit(bul, monsters);
  monster *mon;  
  if (hit_mon_idx != -1) { // bullet hit monster
    mon = monsters[hit_mon_idx];
    stop_bullet(bul);
    reincarnate_monster(mon, MIN_X, MAX_X, MIN_Y, MAX_Y);
    draw_monster(mon);
    add_to_score = 15;
  }else {
    add_to_score = 0;
  }
  return add_to_score;
}

// returns first bullet that has not been just fired
void fire_avail_bullet(bullet *bullets[], player* plr) {
  int n_bullet = 0;
  bullet *bul;
  int x = plr->x+plr->width/2;
  int y = plr->y-plr->width;
  for (n_bullet; n_bullet < N_BULLETS; n_bullet++) {
    bul = bullets[n_bullet];
    if (bul->just_fired != 1) {
      teleport_bullet(bul, x, y);
      fire_bullet(bul, BULLET_SPEED);
      break;
    }
  }
}

// if no collision, returns -1, otherwise returns index of hit tile
int get_monster_bullet_hit(bullet* bul, monster* monsters[]) {
  monster *mon;
  int n_mon;
  for (n_mon = 0; n_mon < N_MONS; n_mon++) {
    mon = monsters[n_mon];
    if (has_bullet_hit_monster(bul, mon)) {
      return n_mon; //true
    }
  }
  return -1; //false
}

int has_bullet_hit_monster(bullet* bul, monster* mon) {
  int bul_top_edge = bul->y - bul->width;
  int bul_bot_edge = bul->y;
  int bul_lft_edge = bul->x;
  int bul_rt_edge = bul->x + bul->width;
  
  int mon_top_edge = mon->y - mon->width;
  int mon_bot_edge = mon->y;
  int mon_lft_edge = mon->x;
  int mon_rt_edge = mon->x + mon->width;
  return have_collided(bul_top_edge, bul_bot_edge,
		       bul_lft_edge, bul_rt_edge,
		       mon_top_edge, mon_bot_edge,
		       mon_lft_edge, mon_rt_edge);      	      
}

void free_bullets(bullet *bullets[]) {
  int n_bullet;
  for (n_bullet = 0; n_bullet < N_BULLETS; n_bullet++) {
    bullets[n_bullet] = create_bullet(0, 0, BULLET_WIDTH);
  }
}


