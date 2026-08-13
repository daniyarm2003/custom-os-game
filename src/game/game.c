#include "game.h"
#include "gameobject_manager.h"
#include "../drivers/timer.h"
#include "../drivers/graphics.h"
#include "objects/player.h"
#include "level.h"

static score_t score = 0;

static Level levels[] = {
    { .name = "The First Level", .backgroundColor.value = 0x00A8FF, .initFunc = level1_init, .updateFunc = NULL, .terminateFunc = NULL }
};

static size_t currentLevelIndex = 0;

static void game_update(f32 dt) {
    level_update(game_get_current_level(), dt);
}

static void game_render() {
    graphics_clear_buffer();
    level_render(game_get_current_level());
    graphics_update_buffer();
}

void game_init() {
    level_load(game_get_current_level());
}

void game_terminate() {
    level_terminate(game_get_current_level());
}

void game_start() {
    f32 dt = (f32)GAME_SLEEP_TICKS / (f32)timer_get_current_frequency();
    timer_t lastFrameTime = timer_get_ticks();

    while(true) {
        game_update(dt);
        game_render();

        sleep_for_timer_ticks(GAME_SLEEP_TICKS);

        timer_t currentTime = timer_get_ticks();
        timer_t elapsedTime = currentTime - lastFrameTime;

        timer_t freq = timer_get_current_frequency();

        lastFrameTime = currentTime;
        dt = (f32)elapsedTime / (f32)freq;
    }
}

score_t game_get_score() {
    return score;
}

void game_add_score(score_t scoreToAdd) {
    score += scoreToAdd;
}

Vec2 game_get_screen_size() {
    return (Vec2){(f32)graphics_get_width(), (f32)graphics_get_height()};
}

Level* game_get_current_level() {
    return &levels[currentLevelIndex];
}

void advance_to_next_level() {
    level_terminate(game_get_current_level());

    size_t numLevels = sizeof(levels) / sizeof(Level);
    currentLevelIndex = (currentLevelIndex + 1) % numLevels;

    level_load(game_get_current_level());
}