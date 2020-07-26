#include "game.h"

int main(void) {
  //game_menu();
  game();
  return 0;
}

void assert_failed(uint8_t* file, uint32_t line) {
/* Infinite loop */
/* Use GDB to find out why we're here */
while(1);
}
