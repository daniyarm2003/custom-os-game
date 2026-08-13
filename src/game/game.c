#include "game.h"
#include "gameobject_manager.h"
#include "../drivers/timer.h"
#include "../drivers/graphics.h"

static score_t score = 0;

static void game_update(f32 dt) {
    game_update_gameobjects(dt);
}

static void game_render() {
    game_draw_gameobjects();
}

void game_init() {
    GameObject* testObj = gameobject_create();

    testObj->pos = (Vec2){100.0f, 100.0f};
    testObj->size = (Vec2){50.0f, 50.0f};

    testObj->renderData.solidColor.value = 0xFF0000;
    
    game_add_gameobject(testObj);
}

void game_terminate() {
    game_terminate_gameobjects();
}

void game_start() {
    f32 dt = (f32)GAME_SLEEP_TICKS / (f32)timer_get_current_frequency();
    timer_t lastFrameTime = timer_get_ticks();

    while(true) {
        game_update(dt);

        graphics_clear_buffer();
        game_render();
        graphics_update_buffer();

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