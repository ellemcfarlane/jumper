#ifndef TILES_H_INCLUDED
#define TILES_H_INCLUDED

#include "stdlib.h"

#include "game_constants.h"
#include "common_defs.h"

#include "tile.h"
#include "player.h"

void init_tiles(tile*[]);
void partial_init_tiles(tile*[], int start_idx, int end_idx, int min_y, int max_y);
int has_player_hit_tile(player*, tile*);
void move_tiles(tile*[]);
void draw_tiles(tile*[]);
void shift_tiles(tile*[], int shift_lmt);
void free_tiles(tile*[]);

#endif
