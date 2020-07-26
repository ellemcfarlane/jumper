#include <stdlib.h>

#include "common_defs.h"

int have_collided(int this_top_edge, int this_bot_edge,
		  int this_lft_edge, int this_rt_edge,
		  int other_top_edge, int other_bot_edge,
		  int other_lft_edge, int other_rt_edge) {
  int horiz_overlap = this_lft_edge <= other_rt_edge &&
                      other_lft_edge <= this_rt_edge;
  int vert_overlap = this_bot_edge >= other_top_edge &&
                     other_bot_edge >= this_top_edge;
  return horiz_overlap && vert_overlap;
}

// returns random integer between [min, max], inclusive.
int rand_int(int min, int max) {
  return min + rand() % (max-min+1);
}

int is_in_range(int x, int low_bound, int up_bound) {
  return x >= low_bound && x <= up_bound;
}

float max(float a, float b) {
  float mx_val = (a > b) ? a : b;
  return mx_val;
}


