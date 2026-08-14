#ifndef _OS_GAME_H
#define _OS_GAME_H

#include "../include/basictypes.h"
#include "../lib/vec2.h"

#include "level.h"

#define GAME_SLEEP_TICKS 10

typedef s32 score_t;

void game_init();
void game_start();
void game_terminate();

score_t game_get_score();
void game_add_score(score_t score);

Vec2 game_get_screen_size();

Level* game_get_current_level();
void game_advance_to_next_level();

#endif