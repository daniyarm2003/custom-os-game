#ifndef _OS_GAMEOBJECT_H
#define _OS_GAMEOBJECT_H

#include "../include/basictypes.h"
#include "../drivers/graphics.h"

#include "../lib/vec2.h"

#include "../graphics/color.h"
#include "../graphics/image.h"
#include "../graphics/types.h"

#define GAMEOBJ_INSTANCE_DATA_SIZE 1024

typedef enum {
    GAMEOBJ_FLAG_NONE = 0,
    GAMEOBJ_FLAG_DESTROYED = 1 << 0,
    GAMEOBJ_FLAG_ACTIVE = 1 << 1,
    GAMEOBJ_FLAG_VISIBLE = 1 << 2
} GameObjectFlags;

typedef enum {
    GAMEOBJ_DRAW_LAYER_BACKGROUND_3 = 0,
    GAMEOBJ_DRAW_LAYER_BACKGROUND_2 = 1,
    GAMEOBJ_DRAW_LAYER_BACKGROUND_1 = 2,
    GAMEOBJ_DRAW_LAYER_FOREGROUND_1 = 3,
    GAMEOBJ_DRAW_LAYER_FOREGROUND_2 = 4,
    GAMEOBJ_DRAW_LAYER_COUNT = 5
} GameObjectDrawLayer;

typedef enum {
    GAMEOBJ_RENDER_SOLID_COLOR = 0,
    GAMEOBJ_RENDER_TEXTURED = 1,
    GAMEOBJ_RENDER_TEXT = 2,
    GAMEOBJ_RENDER_COUNT = 3
} GameObjectRenderType;

struct gameobject_t;

typedef void(*gameobj_update_func_t)(struct gameobject_t*, f32 dt);
typedef void(*gameobj_draw_func_t)(struct gameobject_t*);

typedef struct gameobject_t {
    Vec2 pos, size;
    Vec2 vel, acc;
    s32 timer;

    u8 flags;
    GameObjectDrawLayer drawLayer;

    GameObjectRenderType renderType;
    union {
        Color solidColor;
        Image* texture;

        struct {
            char* text;
            graphics_pos_t fontSize;
            Image* font;
            Color textColor;
        } textData;

    } renderData;

    gameobj_update_func_t updateFunc;
    gameobj_draw_func_t drawFunc;
} GameObject;

GameObject* gameobject_create();
void gameobject_free(GameObject* obj);

bool gameobject_is_active(GameObject* obj);
void gameobject_set_active(GameObject* obj, bool active);

bool gameobject_is_visible(GameObject* obj);
void gameobject_set_visible(GameObject* obj, bool visible);

void gameobject_destroy(GameObject* obj);
bool gameobject_is_destroyed(GameObject* obj);

void gameobject_update(GameObject* obj, f32 dt);
void gameobject_draw(GameObject* obj, GameObjectDrawLayer currentLayer);

#endif