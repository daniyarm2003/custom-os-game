#include "level1.h"
#include "../gameobject_manager.h"
#include "../objects/player.h"

void level1_init() {
    GameObject* testObj = player_create((Vec2){100.0f, 100.0f});
    game_add_gameobject(testObj);
}