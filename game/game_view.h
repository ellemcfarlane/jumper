#ifndef GAME_VIEW_H_INCLUDED
#define GAME_VIEW_H_INCLUDED

#include <stdio.h>

#include "f3d_user_btn.h"
#include "f3d_lcd_sd.h"
#include "f3d_delay.h"

#include "game_constants.h"
#include "player.h"
#include "monster.h"
#include "tile.h"

void draw_pieces(player*, monster*[], tile*[]);
void draw_border();
void draw_main_screen(player*, monster*[], tile*[], int score);
void draw_end_screen(int score);
void draw_pause_screen();
void draw_menu_screen();
void load_game_menu();
void load_pause_menu();
void draw_score(int score);
void redraw_score(int score);

#endif
