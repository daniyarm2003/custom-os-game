#include "physics.h"
#include "../lib/math.h"

void gameobject_physics_apply_gravity(GameObject* obj) {
    obj->acc.y += GRAVITY_ACCELERATION;
}

void gameobject_physics_update_kinematics(GameObject* obj, f32 dt) {
    vec2_mult(&obj->acc, dt);
    vec2_add(&obj->vel, obj->acc);

    Vec2 scaledVel = obj->vel;

    vec2_mult(&scaledVel, dt);
    vec2_add(&obj->pos, scaledVel);

    obj->acc = vec2_init();
}

f32 gameobject_physics_get_vertical_velocity_for_gravity_height(f32 height) {
    return -sqrtf(2.0f * GRAVITY_ACCELERATION * height);
}