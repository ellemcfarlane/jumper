#include <stdio.h>
#include <stdlib.h>
#include "player.h"
#include "monster.h"
#include "game.h"

void test_player_init() {
  player* plr = create_player(1,1,3);
  print_player(plr);
  //free(plr->bullet);
  free(plr);
}

void test_move_player() {
  player* plr = create_player(1,1,3);
  printf("player before left move\n");
  print_player(plr);
  move_player(plr, LEFT);
  print_player(plr);
  printf("right move\n");
  move_player(plr, RIGHT);
  print_player(plr);
  printf("up move\n");
  move_player(plr, UP);
  print_player(plr);
  printf("down move\n");
  move_player(plr, DOWN);
  print_player(plr);
  free(plr);
}

void test_teleport_player() {
  player* plr = create_player(1,1,3);
  teleport_player(plr, 100, 104);
  print_player(plr);
  free(plr);
}

void test_bullet_init() {
  bullet* bul = create_bullet(0, 0, 3);
  print_bullet(bul);
  free(bul);
}

void test_monster_init() {
  monster* mon = create_monster(4, 5, 6);
  print_monster(mon);
  free(mon);
}

int main(void) {
  printf("exp. player {(1,1) len: 3, prev (-1,-1)}\n");
  test_player_init();
  test_move_player();
  test_teleport_player();  
  printf("exp. bullet {(0,0) len: 3}\n");
  test_bullet_init();
  printf("exp. monster {(4,5) len: 6}\n");
  test_monster_init();
  init_mons();
  
  return 0;
}
