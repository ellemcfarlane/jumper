// game header
#include <f3d_lcd_sd.h>

#include "game_constants.h"
#include "monster.h"
#include "monsters.h"
#include "tile.h"
#include "player.h"
#include "game_player.h"
#include "bullets.h"
#include "bullet.h"
#include "game_view.h"
#include "tiles.h"

int game(void);
void init_board_hardware();
void increase_game_ticks(int*);
void advance_game(tile*[], monster*[], int advance_amt);
int determine_shift_amt(player*);
int is_in_shift_mode(int remaining_shifts);
float calc_board_roll_angle(float accel_axes[3]);

void free_all(monster*[], tile*[], player*, bullet*[]);
