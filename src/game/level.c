#include "level.h"
#include "../drivers/graphics.h"
#include "game.h"
#include "gameobject_manager.h"

void level_load(Level* level) {
    if(level->initFunc) {
        level->initFunc();
    }
}

void level_terminate(Level* level) {
    if(level->terminateFunc) {
        level->terminateFunc();
    }

    game_terminate_gameobjects();
}

void level_update(Level* level, f32 dt) {
    if(level->updateFunc) {
        level->updateFunc(dt);
    }

    game_update_gameobjects(dt);
}

void level_render(Level* level) {
    graphics_draw_rectangle(0, 0, graphics_get_width(), graphics_get_height(), level->backgroundColor);
    game_draw_gameobjects();
}