#ifndef _OS_GAMEOBJECT_H
#define _OS_GAMEOBJECT_H

#include "../include/basictypes.h"
#include "../drivers/graphics.h"

#include "../lib/vec2.h"

typedef enum gameobj_draw_type_t {
    GAME_OBJECT_DRAW_RECT,
    GAME_OBJECT_DRAW_IMAGE
} GameObjectDrawType;

struct gameoject_t;

typedef void(*gameobj_update_func_t)(struct gameobject_t*);
typedef void(*gameobj_draw_func_t)(struct gameobject_t*);

typedef struct gameobject_t {
    Vec2 pos, size;
    s32 timer;

    GameObjectDrawType drawType;
    union {
        struct {
            Color color;
        } rectProps;

        struct {
            const Image* image;
        } imageProps;
    } graphicsInfo;

    bool visible;

    gameobj_update_func_t updateFunc;
    gameobj_draw_func_t drawFunc;
} GameObject;

#endif