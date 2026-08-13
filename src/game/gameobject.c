#include "gameobject.h"
#include "../lib/malloc.h"

static void gameobject_set_flag(GameObject* obj, GameObjectFlags flag, bool value) {
    if(value) {
        obj->flags |= (u8)flag;
    } 
    else {
        obj->flags &= ~(u8)flag;
    }
}

bool gameobject_is_active(GameObject* obj) {
    return obj->flags & (u8)GAMEOBJ_FLAG_ACTIVE;
}

void gameobject_set_active(GameObject* obj, bool active) {
    gameobject_set_flag(obj, GAMEOBJ_FLAG_ACTIVE, active);
}

bool gameobject_is_visible(GameObject* obj) {
    return obj->flags & (u8)GAMEOBJ_FLAG_VISIBLE;
}

void gameobject_set_visible(GameObject* obj, bool visible) {
    gameobject_set_flag(obj, GAMEOBJ_FLAG_VISIBLE, visible);
}

void gameobject_destroy(GameObject* obj) {
    gameobject_set_flag(obj, GAMEOBJ_FLAG_DESTROYED, true);
}

bool gameobject_is_destroyed(GameObject* obj) {
    return obj->flags & (u8)GAMEOBJ_FLAG_DESTROYED;
}

void gameobject_update(GameObject* obj, f32 dt) {
    if(obj->updateFunc && gameobject_is_active(obj) && !gameobject_is_destroyed(obj)) {
        obj->updateFunc(obj, dt);
    }

    obj->timer++;
}

void gameobject_draw(GameObject* obj, GameObjectDrawLayer currentLayer) {
    if(obj->drawLayer != currentLayer || !gameobject_is_visible(obj) || gameobject_is_destroyed(obj)) {
        return;
    }

    if(obj->drawFunc) {
        obj->drawFunc(obj);
        return;
    }

    switch(obj->renderType) {
        case GAMEOBJ_RENDER_SOLID_COLOR:
            graphics_draw_rectangle((graphics_pos_t)obj->pos.x, (graphics_pos_t)obj->pos.y, (graphics_pos_t)obj->size.x, (graphics_pos_t)obj->size.y, obj->renderData.solidColor);
            break;

        case GAMEOBJ_RENDER_TEXTURED:
            graphics_draw_image_scaled((graphics_pos_t)obj->pos.x, (graphics_pos_t)obj->pos.y, (graphics_pos_t)obj->size.x, (graphics_pos_t)obj->size.y, obj->renderData.texture);
            break;

        case GAMEOBJ_RENDER_TEXT:
            graphics_draw_text((graphics_pos_t)obj->pos.x, (graphics_pos_t)obj->pos.y, obj->renderData.textData.text, obj->renderData.textData.font, obj->renderData.textData.fontSize, obj->renderData.textData.textColor);
            break;

        default:
            break;
    }
}

GameObject* gameobject_create() {
    GameObject* obj = (GameObject*)malloc(sizeof(GameObject));
    if(!obj) {
        return NULL;
    }

    f32 defaultSize = 25.0f;

    obj->pos.x = 0.0f;
    obj->pos.y = 0.0f;

    obj->size.x = defaultSize;
    obj->size.y = defaultSize;

    obj->vel = vec2_init();
    obj->acc = vec2_init();

    obj->prevCollisions = 0;

    obj->timer = 0;

    obj->flags = (u8)GAMEOBJ_FLAG_ACTIVE | (u8)GAMEOBJ_FLAG_VISIBLE;
    obj->drawLayer = GAMEOBJ_DRAW_LAYER_FOREGROUND_1;

    obj->renderType = GAMEOBJ_RENDER_SOLID_COLOR;
    obj->renderData.solidColor.value = 0xFFFFFFFF;

    obj->updateFunc = NULL;
    obj->drawFunc = NULL;

    return obj;
}

void gameobject_free(GameObject* obj) {
    if(!obj) {
        return;
    }

    free(obj);
}