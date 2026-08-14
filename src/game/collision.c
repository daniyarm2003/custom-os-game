#include "collision.h"
#include "game.h"
#include "gameobject_manager.h"

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

    obj->prevCollisions |= edgesHit;
}

void gameobject_push_out_of_collidables(GameObject* obj) {
    collision_mask_t wallsHit = 0;

    for(GameObjectIterator* cur = gameobject_iterator_get_head(); cur; cur = gameobject_iterator_get_next(cur)) {
        GameObject* other = gameobject_iterator_get_object(cur);

        if(other == obj || other->type != GAMEOBJ_TYPE_COLLIDABLE || !gameobject_is_colliding(obj, other)) {
            continue;
        }

        Vec2 selfBottomRight = obj->pos;
        Vec2 otherBottomRight = other->pos;

        vec2_add(&selfBottomRight, obj->size);
        vec2_add(&otherBottomRight, other->size);

        f32 directionDists[COLLISION_DIR_COUNT] = {0};

        directionDists[COLLISION_DIR_UP] = otherBottomRight.y - obj->pos.y;
        directionDists[COLLISION_DIR_DOWN] = selfBottomRight.y - other->pos.y;
        directionDists[COLLISION_DIR_LEFT] = otherBottomRight.x - obj->pos.x;
        directionDists[COLLISION_DIR_RIGHT] = selfBottomRight.x - other->pos.x;

        CollisionDirection curDir = 0;
        f32 minDist = directionDists[0];

        for(CollisionDirection dir = 1; dir < COLLISION_DIR_COUNT; dir++) {
            if(directionDists[dir] < minDist) {
                minDist = directionDists[dir];
                curDir = dir;
            }
        }

        collision_set_mask(&wallsHit, curDir, true);

        Vec2 mtv = collision_get_direction_vector(curDir);

        vec2_mult(&mtv, -minDist);
        vec2_add(&obj->pos, mtv);

        obj->prevCollisions |= wallsHit;
    }
}

void gameobject_reset_collision_state(GameObject* obj) {
    obj->prevCollisions = 0;
}

bool gameobject_is_colliding(GameObject* self, GameObject* other) {
    Vec2 selfBottomRight = self->pos;
    Vec2 otherBottomRight = other->pos;

    vec2_add(&selfBottomRight, self->size);
    vec2_add(&otherBottomRight, other->size);

    return self->pos.x <= otherBottomRight.x && selfBottomRight.x >= other->pos.x
        && self->pos.y <= otherBottomRight.y && selfBottomRight.y >= other->pos.y;
}