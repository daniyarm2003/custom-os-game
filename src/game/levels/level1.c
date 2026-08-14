#include "level1.h"
#include "../gameobject_manager.h"
#include "../objects/player.h"
#include "../objects/cookie.h"
#include "../objects/platform.h"

void level1_init() {
    GameObject* player = player_create((Vec2){10.0f, 500.0f});
    game_add_gameobject(player);

    Vec2 cookiePositions[] = {
        // Starting platform
        { 70.0f, 500.0f },
        { 130.0f, 500.0f },
        { 190.0f, 500.0f },

        // Platform 2
        { 270.0f, 400.0f },
        { 340.0f, 400.0f },

        // Platform 3
        { 430.0f, 300.0f },
        { 500.0f, 300.0f },

        // Platform 4
        { 570.0f, 200.0f },
        { 640.0f, 200.0f },

        // Final platform
        { 700.0f, 100.0f }
    };

    Vec2 platformDefs[][2] = {
        // Starting platform
        { { 0.0f, 550.0f }, { 240.0f, 50.0f } },

        // Platform 2
        { { 220.0f, 450.0f }, { 180.0f, 50.0f } },

        // Platform 3
        { { 380.0f, 350.0f }, { 180.0f, 50.0f } },

        // Platform 4
        { { 540.0f, 250.0f }, { 180.0f, 50.0f } },

        // Final platform
        { { 680.0f, 150.0f }, { 120.0f, 50.0f } }
    };

    size_t numCookies = sizeof(cookiePositions) / sizeof(cookiePositions[0]);
    size_t numPlatforms = sizeof(platformDefs) / sizeof(platformDefs[0]);

    for(size_t i = 0; i < numCookies; i++) {
        game_add_gameobject(cookie_create(cookiePositions[i]));
    }

    for(size_t i = 0; i < numPlatforms; i++) {
        game_add_gameobject(platform_create(platformDefs[i][0], platformDefs[i][1]));
    }
}