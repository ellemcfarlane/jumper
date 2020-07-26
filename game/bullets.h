#ifndef BULLETS_H_INCLUDED
#define BULLETS_H_INCLUDED

#include "monster.h"
#include "bullet.h"
#include "player.h"

void init_bullets(bullet*[]);
void free_bullets(bullet*[]);

int handle_live_bullet(bullet* bul, monster*[]);
int bullet_monsters_interaction(bullet*, monster*[]);
int get_monster_bullet_hit(bullet* bul, monster* monsters[]);
void bullet_react_to_monster(bullet*, monster*);
void fire_avail_bullet(bullet*[], player*);
int move_live_bullets(bullet*[],monster*[]);
int has_bullet_hit_monster(bullet*, monster*);

#endif
