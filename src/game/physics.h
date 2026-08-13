#ifndef _OS_PHYSICS_H_
#define _OS_PHYSICS_H_

#include "gameobject.h"

#define PIXELS_PER_METER 100.0f
#define GRAVITY_ACCELERATION (9.81f * PIXELS_PER_METER)

void gameobject_physics_apply_gravity(GameObject* obj);
void gameobject_physics_update_kinematics(GameObject* obj, f32 dt);

f32 gameobject_physics_get_vertical_velocity_for_gravity_height(f32 height);

#endif