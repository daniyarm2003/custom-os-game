#include "level1.h"
#include "../gameobject_manager.h"
#include "../objects/player.h"
#include "../objects/cookie.h"

void level1_init() {
    GameObject* player = player_create((Vec2){100.0f, 100.0f});
    game_add_gameobject(player);

    Vec2 cookiePositions[] = {
        { 200.0f, 500.0f },
        { 250.0f, 500.0f },
        { 300.0f, 500.0f }
    };

    size_t numCookies = sizeof(cookiePositions) / sizeof(cookiePositions[0]);

    for(size_t i = 0; i < numCookies; i++) {
        game_add_gameobject(cookie_create(cookiePositions[i]));
    }
}