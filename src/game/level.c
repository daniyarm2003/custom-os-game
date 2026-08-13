#include "level.h"
#include "../drivers/graphics.h"
#include "game.h"
#include "gameobject_manager.h"
#include "../images/images.h"
#include "../lib/string.h"

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

    graphics_draw_text(10, 10, level->name, &font_monospace_image_data, 20, (Color){ .value = 0xFFFFFF });

    char scoreText[64] = {0};
    sprintf(scoreText, "Score: %d", game_get_score());

    graphics_draw_text(10, 35, scoreText, &font_monospace_image_data, 15, (Color){ .value = 0xFFFFFF });
}