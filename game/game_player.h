#ifndef GAME_PLAYER_H_INCLUDED
#define GAME_PLAYER_H_INCLUDED

#include "player.h"
#include "monster.h"
#include "tile.h"

int player_tiles_interaction(player* plr, tile*[]);
int player_monsters_interaction(player* plr, monster*[]);
void keep_player_on_screen(player*);
void player_normal_mode_move(player*);
void player_shift_mode_move(player*);
int player_react_to_monster(player*, monster*);
void player_react_to_tile(player*, tile*);
int has_player_crushed_monster(player*, monster*);
int has_player_crushed_tile(player*, tile*);
int get_tile_player_hit(player*, tile*[]);
int get_monster_player_hit(player*, monster*[]);
int has_player_hit_monster(player*, monster*);
int has_player_hit_tile(player*, tile*);
#endif
