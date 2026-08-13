#include "collision.h"
#include "game.h"

bool collision_get_mask(collision_mask_t mask, CollisionDirection dir) {
    return (mask & (1 << dir)) != 0;
}

void collision_set_mask(collision_mask_t* mask, CollisionDirection dir, bool value) {
    if (value) {
        *mask |= (1 << dir);
    } 
    else {
        *mask &= ~(1 << dir);
    }
}

Vec2 collision_get_direction_vector(CollisionDirection dir) {
    switch (dir) {
        case COLLISION_DIR_UP:
            return (Vec2){0.0f, -1.0f};

        case COLLISION_DIR_DOWN:
            return (Vec2){0.0f, 1.0f};

        case COLLISION_DIR_LEFT:
            return (Vec2){-1.0f, 0.0f};

        case COLLISION_DIR_RIGHT:
            return (Vec2){1.0f, 0.0f};
            
        default:
            return (Vec2){0.0f, 0.0f};
    }
}

void gameobject_keep_in_bounds(GameObject* obj, collision_mask_t checkDirs) {
    Vec2 screenSize = game_get_screen_size();
    collision_mask_t edgesHit = 0;

    if (collision_get_mask(checkDirs, COLLISION_DIR_LEFT) && obj->pos.x < 0.0f) {
        obj->pos.x = 0.0f;
        collision_set_mask(&edgesHit, COLLISION_DIR_LEFT, true);
    }
    if (collision_get_mask(checkDirs, COLLISION_DIR_RIGHT) && obj->pos.x + obj->size.x > screenSize.x) {
        obj->pos.x = screenSize.x - obj->size.x;
        collision_set_mask(&edgesHit, COLLISION_DIR_RIGHT, true);
    }
    if (collision_get_mask(checkDirs, COLLISION_DIR_UP) && obj->pos.y < 0.0f) {
        obj->pos.y = 0.0f;
        collision_set_mask(&edgesHit, COLLISION_DIR_UP, true);
    }
    if (collision_get_mask(checkDirs, COLLISION_DIR_DOWN) && obj->pos.y + obj->size.y > screenSize.y) {
        obj->pos.y = screenSize.y - obj->size.y;
        collision_set_mask(&edgesHit, COLLISION_DIR_DOWN, true);
    }

    obj -> prevCollisions |= edgesHit;
}

void gameobject_reset_collision_state(GameObject* obj) {
    obj->prevCollisions = 0;
}