#ifndef _OS_LEVEL_H_
#define _OS_LEVEL_H_

#include "../include/basictypes.h"
#include "../graphics/color.h"

#include "levels/level1.h"

typedef void(*level_init_func_t)();
typedef void(*level_update_func_t)(f32 dt);
typedef void(*level_terminate_func_t)();

typedef struct level_t {
    const char* name;
    Color backgroundColor;

    level_init_func_t initFunc;
    level_update_func_t updateFunc;
    level_terminate_func_t terminateFunc;
} Level;

void level_load(Level* level);
void level_terminate(Level* level);

void level_update(Level* level, f32 dt);
void level_render(Level* level);

#endif