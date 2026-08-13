#include "player.h"
#include "../../images/images.h"
#include "../game.h"
#include "../controls.h"
#include "../physics.h"
#include "../collision.h"

static void player_update(GameObject* player, f32 dt) {
    f32 playerTopSpeed = 250.0f;
    f32 playerAcceleration = 650.0f;
    f32 playerFriction = 0.05f;

    f32 jumpHeight = 2.0f * PIXELS_PER_METER;

    if (controls_is_left_control_pressed() && player->vel.x > -playerTopSpeed) {
        player->acc.x = -playerAcceleration;
    }
    else if (controls_is_right_control_pressed() && player->vel.x < playerTopSpeed) {
        player->acc.x = playerAcceleration;
    }
    else {
        player->vel.x *= (1.0f - playerFriction);
    }

    if(collision_get_mask(player->prevCollisions, COLLISION_DIR_LEFT) && player->vel.x < 0.0f) {
        player->vel.x = 0.0f;
    }

    if(collision_get_mask(player->prevCollisions, COLLISION_DIR_RIGHT) && player->vel.x > 0.0f) {
        player->vel.x = 0.0f;
    }

    if(collision_get_mask(player->prevCollisions, COLLISION_DIR_UP) && player->vel.y < 0.0f) {
        player->vel.y *= -1.0f;
    }

    if(collision_get_mask(player->prevCollisions, COLLISION_DIR_DOWN)) {
        if(controls_is_jump_control_pressed()) {
            player->vel.y = gameobject_physics_get_vertical_velocity_for_gravity_height(jumpHeight);
        }
        else {
            player->vel.y = 0.0f;
        }
    }

    gameobject_physics_apply_gravity(player);
    gameobject_physics_update_kinematics(player, dt);

    gameobject_reset_collision_state(player);
    gameobject_keep_in_bounds(player, COLLISION_MASK_ALL);
}

GameObject* player_create(Vec2 pos) {
    GameObject* player = gameobject_create();

    player->pos = pos;
    player->size = (Vec2){32.0f, 32.0f};

    player->renderType = GAMEOBJ_RENDER_TEXTURED;
    player->renderData.texture = &player_image_data;

    player->updateFunc = player_update;

    return player;
}