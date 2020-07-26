#include "tiles.h"

void init_tiles(tile *tiles[]) {
  int min_y;
  int max_y;
  int n_chunks = 3;
  int n_chunk;
  int start_idx;
  int end_idx;
  int idx_ranges[3][2] = {{0,N_TILES/3},
				{N_TILES/3, 2*N_TILES/3},
				{2*N_TILES/3, N_TILES}};
  int y_ranges[3][2] = {{2*MAX_Y/3,MAX_Y},
			      {MAX_Y/3,2*MAX_Y/3},
			      {0,MAX_Y/3}};
  for (n_chunk = 0; n_chunk < n_chunks; n_chunk++) {
    start_idx = idx_ranges[n_chunk][0];
    end_idx = idx_ranges[n_chunk][1];
    min_y = y_ranges[n_chunk][0];
    max_y = y_ranges[n_chunk][1];
    partial_init_tiles(tiles, start_idx, end_idx, min_y, max_y);
  }
}

// initialized tiles from [start_idx, end_idx]
// with random position
void partial_init_tiles(tile *tiles[], int start_idx,
			int end_idx, int min_y, int max_y) {
  int x;
  int y;
  int n_tile;
  for (n_tile = start_idx; n_tile < end_idx; n_tile++) {
    x = rand_int(MIN_X, MAX_X-TILE_WIDTH);
    y = rand_int(min_y+TILE_HEIGHT+MIN_Y, max_y);
    tiles[n_tile] = create_tile(x, y, TILE_WIDTH, TILE_HEIGHT);    
  }
}

int has_player_hit_tile(player* plr, tile* tl) {
  int plr_top_edge = plr->y - plr->height;
  int plr_bot_edge = plr->y;
  int plr_lft_edge = plr->x;
  int plr_rt_edge = plr->x + plr->width;
  
  int tl_top_edge = tl->y - tl->height;
  int tl_bot_edge = tl->y;
  int tl_lft_edge = tl->x;
  int tl_rt_edge = tl->x + tl->width;
  return have_collided(plr_top_edge, plr_bot_edge,
		       plr_lft_edge, plr_rt_edge,
		       tl_top_edge, tl_bot_edge,
		       tl_lft_edge, tl_rt_edge);      	       
}

void draw_tiles(tile *tiles[]) {
  int n_tile;
  for (n_tile = 0; n_tile < N_TILES; n_tile++) {
    tile *tl = tiles[n_tile];
    draw_tile(tl);
  }
}

// if tile out of screen view after shift,
// it is reassigned to random x location at top of screen
// otherwise it is shifted down by the shift_amt
void shift_tiles(tile *tiles[], int shift_amt) {
  int new_y;
  int new_x;
  int rand_y;
  int rand_x;
  int shift_lmt = MAX_Y-shift_amt;
  tile *tl;
  int n_tile;
  
  for (n_tile = 0; n_tile < N_TILES; n_tile++) {
    tl = tiles[n_tile];
    rand_x = rand_int(MIN_X, MAX_X-TILE_WIDTH);
    if (tl->y >= shift_lmt) {
      new_y = MIN_Y+TILE_HEIGHT;
      new_x = rand_x;
    }else {
      new_x = tl->x;
      new_y = tl->y+shift_amt;
    }    
    teleport_tile(tl, new_x, new_y);
  }
}

void free_tiles(tile *tiles[]) {
  int n_tile;
  for (n_tile = 0; n_tile < N_TILES; n_tile++) {
    tile *tl = tiles[n_tile];
    free(tl);
  }
}


