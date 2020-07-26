#ifndef MONSTERS_H_INCLUDED
#define MONSTERS_H_INCLUDED

#include "game_constants.h"
#include "common_defs.h"
#include "monster.h"
#include "player.h"

void change_direction_of_monsters(monster*[]);
void change_monster_direction(monster*);
void move_monsters(monster*[]);
void init_monsters(monster*[]);
int has_player_hit_monster(player*, monster*);
void move_monsters(monster*[]);
void draw_monsters(monster*[]);
void free_monsters(monster*[]);
void shift_monsters(monster*[], int shift_lmt);
void keep_monster_on_screen_horiz(monster*);
void keep_monster_on_screen_vert(monster*);

#endif
