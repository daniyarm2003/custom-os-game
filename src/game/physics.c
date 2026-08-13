#include "physics.h"

void gameobject_physics_update_kinematics(GameObject* obj, f32 dt) {
    Vec2 scaledAcc = obj->acc;

    vec2_mult(&scaledAcc, dt);
    vec2_add(&obj->vel, scaledAcc);

    Vec2 scaledVel = obj->vel;

    vec2_mult(&scaledVel, dt);
    vec2_add(&obj->pos, scaledVel);
}