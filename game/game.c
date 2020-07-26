// main game.c file
#include <stm32f30x.h>
#include <f3d_uart.h>
#include <f3d_i2c.h>
#include <f3d_nunchuk.h>
#include <f3d_gyro.h>
#include <f3d_accel.h>
#include <f3d_lcd_sd.h>
#include <f3d_user_btn.h>
#include <f3d_delay.h>

#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <limits.h>

#include "common_defs.h"
#include "game.h"

// main DoodleJump game logic that dictates all moving parts
int game(void){
  // hardware vars
  float accel_axes[3];
  float board_roll_angle;
  nunchuk_t nunChkData;
  init_board_hardware();

  // game vars
  int ticks = 0;  
  int score = 0;
  int shifts_remaining = 0;
  int new_speed = 0;
  int adjusted_speed = 0;
  int gravity = 1;
  int prev_score = score;
  int player_move_period = 11;
  int outcome = -1;
  
  // character vars
  player* plr = create_player(70, 50, 10);
  set_player_vert_vel(plr, 1);
  monster *monsters[N_MONS];
  tile *tiles[N_TILES];
  bullet *bullets[N_BULLETS];

  init_monsters(monsters);
  init_tiles(tiles);
  init_bullets(bullets);

  load_game_menu();
  delay(100);
  
  draw_main_screen(plr, monsters, tiles, score);
  // main game loop for events and responses
  while(1) {
    increase_game_ticks(&ticks);
    
    if (!is_in_shift_mode(shifts_remaining) && prev_score != score) {
      redraw_score(score);
      prev_score = score;
    }
    
    // pause if button pressed
    if (user_btn_read()) {
      load_pause_menu();
      draw_main_screen(plr, monsters, tiles, score);
    }
   
    // fire bullet if nunchuck's c or z button is pressed
    f3d_nunchuk_read(&nunChkData);   
    if (nunChkData.c || nunChkData.z) {
      if (ticks % BULLET_REFRACTORY_INTERVAL == 0) {
	fire_avail_bullet(bullets, plr);
      }
    }

    // read accelerometer for player's left/right motion    
    f3d_accel_read(accel_axes);
    
    if (ticks % BULLET_MOVE_PERIOD == 0) {
      score += move_live_bullets(bullets, monsters);
    }
    
    if (ticks % player_move_period == 0) {
      board_roll_angle = calc_board_roll_angle(accel_axes);      
      set_player_horiz_vel(plr, board_roll_angle);
      // end game if player out of lower bound
      if (plr->y > MAX_Y) {
	draw_end_screen(score);
	break;
      }

      outcome = player_tiles_interaction(plr, tiles);
      if (outcome == PLAYER_REBOUNDED) {
	shifts_remaining = determine_shift_amt(plr);
      }
      
      outcome = player_monsters_interaction(plr, monsters);
      if (outcome == PLAYER_REBOUNDED) {
	shifts_remaining = determine_shift_amt(plr);
	score += 25;	
      }
      else if (outcome == PLAYER_DIED) {
	draw_end_screen(score);
	break;
      }      
            
      if (is_in_shift_mode(shifts_remaining)) {
	score += 5;
	shifts_remaining -= 1;
       // restrict player movement to only left/right motion
	player_shift_mode_move(plr);
	draw_tiles(tiles);
	advance_game(tiles, monsters, 1);
	draw_monsters(monsters);
      }else {      
	player_normal_mode_move(plr);
	// gravity changes player's velocity
	set_player_vert_vel(plr, plr->vert_vel+gravity);
      }
      player_move_period -= gravity;
      player_move_period = player_move_period > MIN_PLAYER_MOVE_PERIOD ?
	player_move_period : MIN_PLAYER_MOVE_PERIOD;      
   }

    if (ticks % MONSTER_MOVE_PERIOD == 0) {
      if (ticks % CHANGE_MONSTER_DIRECTION_INTERVAL == 0) {
	change_direction_of_monsters(monsters);
      }    
      move_monsters(monsters);
      draw_monsters(monsters);
    }
  }
  free_all(monsters, tiles, plr, bullets);
}

void increase_game_ticks(int* ticks) {
  (*ticks)++;
  *ticks %= INT_MAX;
}

int is_in_shift_mode(int shifts_remaining) {
  return shifts_remaining > 0;
}

// advances game for player by advance_amt
void advance_game(tile* tiles[], monster* monsters[], int advance_amt) {
  shift_tiles(tiles, advance_amt);
  shift_monsters(monsters, advance_amt);
}

// determines how much to advance game based on player's vertical position
int determine_shift_amt(player* plr) {
  int shift_amt;
  if (plr->y <= MOVE_SCREEN_LMT && is_player_moving_upward(plr)) {
    shift_amt = MAX_Y-MOVE_SCREEN_LMT;
  }
  return shift_amt;
}

void draw_pieces(player* plr, monster *monsters[], tile* tiles[]) {
  draw_monsters(monsters);
  draw_tiles(tiles);
  draw_player(plr);  
}

void init_board_hardware() {
  f3d_uart_init();
  f3d_lcd_init();
  f3d_gyro_init();
  f3d_user_btn_init();
  f3d_i2c1_init();
  delay(10);
  f3d_nunchuk_init();
  delay(10);
  f3d_accel_init();
}

// roll_angle used to determine left/right movement of player
float calc_board_roll_angle(float accel_axes[3]){
  float x_accel = accel_axes[0];
  float y_accel = accel_axes[1];  
  float z_accel = accel_axes[2];
  float x_z_accel = sqrt(powf(x_accel, 2) + powf(z_accel, 2));
  float roll_angle = atan2f(y_accel, x_z_accel);
  return roll_angle;
}

void free_all(monster*monsters[], tile*tiles[], player* plr, bullet*bullets[]) {
  free_monsters(monsters);
  free_tiles(tiles);
  free(plr);
  free_bullets(bullets);
}
