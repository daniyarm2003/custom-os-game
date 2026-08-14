#include "platform.h"

GameObject* platform_create(Vec2 pos, Vec2 size) {
    GameObject* platform = gameobject_create();

    platform->pos = pos;
    platform->size = size;

    platform->renderData.solidColor.value = 0xA0A0A0;
    platform->type = GAMEOBJ_TYPE_COLLIDABLE;

    return platform;
}