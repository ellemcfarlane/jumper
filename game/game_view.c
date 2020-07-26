#include "game_view.h"

void draw_border() {
  f3d_lcd_drawRect(0, MIN_Y-1, ST7735_width, 1, RED);
}

void draw_main_screen(player* plr, monster *monsters[],
		      tile* tiles[], int score) {
  f3d_lcd_fillScreen(BACKGROUND);
  draw_pieces(plr, monsters, tiles);
  draw_score(score);
  draw_border();
}

void draw_menu_screen() {
  f3d_lcd_fillScreen(MAGENTA);
  f3d_lcd_drawRect(ST7735_width/10+2, MAX_Y/2, 100, 60, GREEN);
  f3d_lcd_drawString(MAX_X/2-34, MAX_Y/2-40, "PRESS BUTTON", BACKGROUND, GREEN);
  f3d_lcd_drawString(MAX_X/2-17, MAX_Y/2-25, "TO PLAY", BACKGROUND, GREEN);
}

void draw_pause_screen() {
  f3d_lcd_fillScreen(MAGENTA);
  f3d_lcd_drawRect(0, MAX_Y/2-22, ST7735_width, 30, GREEN);  
  f3d_lcd_drawString(MAX_X/2-16, MAX_Y/2-40, "PAUSED", BACKGROUND, GREEN);
}

void draw_end_screen(int score) {
  char score_str[20];
  sprintf(score_str, "SCORE: %d", score);
  f3d_lcd_fillScreen(GREEN);
  f3d_lcd_drawString(MAX_X/2-25, MAX_Y/2-40, "GAME OVER", BACKGROUND, GREEN);
  f3d_lcd_drawString(MAX_X/2-28, MAX_Y/2-25, score_str, BACKGROUND, GREEN);
}

void load_game_menu(void) {
  draw_menu_screen();
  while (user_btn_read() != 1);
}

void load_pause_menu(void) {
  draw_pause_screen();
  delay(100);
  // unpause if button pressed again
  while (user_btn_read() != 1);
}

void draw_score(int score) {
  f3d_lcd_drawString(3, 0, "Score: ", RED, BACKGROUND);
  redraw_score(score);
}

void redraw_score(int score) {
  char score_str[10];
  sprintf(score_str, "%d", score);
  // clear previous score
  f3d_lcd_drawString(35, 0,"          " , RED, BACKGROUND);
  // draw new score
  f3d_lcd_drawString(35, 0, score_str,  RED, BACKGROUND);
}
