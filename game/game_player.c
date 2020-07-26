#include "game_player.h"

#include "game_constants.h"
#include "common_defs.h"

#include <stdlib.h>

// moves player vertically and horizontally
void player_normal_mode_move(player* plr) {
  move_player_per_horiz_vel(plr);
  draw_player(plr);
  keep_player_on_screen(plr);
  draw_player(plr);	
  move_player_per_vert_vel(plr);
  draw_player(plr);
}

// moves player only horizontally
void player_shift_mode_move(player* plr) {
  move_player_per_horiz_vel(plr);
  draw_player(plr);
  keep_player_on_screen(plr);
  draw_player(plr);
}

// relocates player roughly to min horiz location if past max horiz location
void keep_player_on_screen(player* plr) {
  if (plr->x <= MIN_X) {
    teleport_player(plr, MAX_X-plr->width, plr->y);
  }     
  else if (plr->x + plr->width >= MAX_X) {
    teleport_player(plr, MIN_X, plr->y);
  }     
}

// if no collision, returns -1, otherwise returns index of hit tile
int get_tile_player_hit(player* plr, tile* tiles[]) {
  tile *tl;
  int n_tile;
  
  for (n_tile = 0; n_tile < N_TILES; n_tile++) {
    tl = tiles[n_tile];
    if (has_player_hit_tile(plr, tl)) {
      return n_tile; //true
    }
  }
  return -1; //false
}

// returns PLAYER_REBOUNDED if player bounces off tile
// otherwise NO_EVENT
int player_tiles_interaction(player* plr, tile* tiles[]) {
  int hit_tile_idx = get_tile_player_hit(plr, tiles);
  // player hit tile
  if (hit_tile_idx != -1) {
    tile* tl = tiles[hit_tile_idx];
    if (has_player_crushed_tile(plr, tl)) {
      rebound_player(plr);
      return PLAYER_REBOUNDED;
    }
    draw_tile(tl);
  }
  return NO_EVENT;
}

// returns PLAYER_REBOUNDED if player bounces off monster,
// PLAYER_DIED if hits monster but does not bounce,
// and otherwise NO_EVENT
int player_monsters_interaction(player* plr, monster* monsters[]) {
  int hit_mon_idx = get_monster_player_hit(plr, monsters);
  if (hit_mon_idx != -1) {
    monster* mon = monsters[hit_mon_idx];
    // break game loop if player dies
    if (has_player_crushed_monster(plr, mon)) {
      rebound_player(plr);
      // kill monster
      reincarnate_monster(mon, MIN_X, MAX_X, MIN_Y, MAX_Y);  
      draw_monster(mon);
      return PLAYER_REBOUNDED;
    }else { // kill player
      return PLAYER_DIED;
    }
    return NO_EVENT;
  }   
}

// returns true if player bounces on top of monster
int has_player_crushed_monster(player* plr, monster* mon) {
  int top_of_mon = mon->y - mon->height;
  int hit_top_of_mon = abs(plr->y - top_of_mon) < 2;
  int not_moving_upward = is_player_falling(plr) || plr->vert_vel == 0;
  return hit_top_of_mon && not_moving_upward;
}

//todo change not_moved_upward definition lol to use fxn
int has_player_crushed_tile(player* plr, tile* tl) {
  int hit_top_of_tl = plr->y == (tl->y - tl->height);
  int not_moving_upward = is_player_falling(plr) || plr->vert_vel == 0;
  return hit_top_of_tl && not_moving_upward;
}

// if no collision, returns -1, otherwise returns index of hit monster
int get_monster_player_hit(player* plr, monster* monsters[]) {
  monster *mon;
  int n_mon;
  for (n_mon = 0; n_mon < N_MONS; n_mon++) {
    mon = monsters[n_mon];
    if (has_player_hit_monster(plr, mon)) {
      return n_mon; //true
    }
  }
  return -1; //false
}

int has_player_hit_monster(player* plr, monster* mon) {
  int plr_top_edge = plr->y - plr->height;
  int plr_bot_edge = plr->y;
  int plr_lft_edge = plr->x;
  int plr_rt_edge = plr->x + plr->width;
  
  int mon_top_edge = mon->y - mon->height;
  int mon_bot_edge = mon->y;
  int mon_lft_edge = mon->x;
  int mon_rt_edge = mon->x + mon->width;
  return have_collided(plr_top_edge, plr_bot_edge,
		       plr_lft_edge, plr_rt_edge,
		       mon_top_edge, mon_bot_edge,
		       mon_lft_edge, mon_rt_edge);
}
