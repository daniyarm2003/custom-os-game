#ifndef _OS_COLLISION_H_
#define _OS_COLLISION_H_

#include "../include/basictypes.h"

typedef u8 collision_mask_t;

#define COLLISION_MASK_ALL (0x0F)

typedef enum collision_dir_t {
    COLLISION_DIR_UP,
    COLLISION_DIR_DOWN,
    COLLISION_DIR_LEFT,
    COLLISION_DIR_RIGHT,
    COLLISION_DIR_COUNT
} CollisionDirection;

#include "gameobject.h"

// Forward declaration of GameObject struct
typedef struct gameobject_t GameObject;

bool collision_get_mask(collision_mask_t mask, CollisionDirection dir);
void collision_set_mask(collision_mask_t* mask, CollisionDirection dir, bool value);

Vec2 collision_get_direction_vector(CollisionDirection dir);

void gameobject_reset_collision_state(GameObject* obj);
void gameobject_keep_in_bounds(GameObject* obj, collision_mask_t checkDirs);
void gameobject_push_out_of_collidables(GameObject* obj);

bool gameobject_is_colliding(GameObject* self, GameObject* other);

#endif