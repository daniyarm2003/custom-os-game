#ifndef _OS_GAME_H
#define _OS_GAME_H

#include "../include/basictypes.h"

#define GAME_SLEEP_TICKS 10

typedef s32 score_t;

void game_init();
void game_start();
void game_terminate();

score_t game_get_score();
void game_add_score(score_t score);

#endif