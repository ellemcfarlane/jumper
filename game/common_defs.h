// common_defs.h
#ifndef COMMON_DEFS_H_INCLUDED
#define COMMON_DEFS_H_INCLUDED

enum {LEFT, UP, RIGHT, DOWN, PLAYER_DIED, PLAYER_REBOUNDED, NO_EVENT};

int rand_int(int min, int max);
int is_in_range(int x, int low_bound, int up_bound);
int have_collided(int this_top_edge, int this_bot_edge,
		  int this_lft_edge, int this_rt_edge,
		  int other_top_edge, int other_bot_edge,
		  int other_lft_edge, int other_rt_edge);
float max(float a, float b);
#endif

