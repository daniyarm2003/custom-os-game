#include "cookie.h"
#include "../../images/images.h"
#include "../game.h"
#include "../../include/basicmacros.h"
#include "items.h"

static void cookie_on_collect(GameObject* cookie) {
    UNUSED(cookie);
    game_add_score(COOKIE_SCORE_VALUE);
}

GameObject* cookie_create(Vec2 pos) {
    GameObject* cookie = gameobject_create();

    cookie->pos = pos;
    cookie->size = (Vec2){24.0f, 24.0f};

    cookie->renderType = GAMEOBJ_RENDER_TEXTURED;
    cookie->renderData.texture = &cookie_image_data;

    cookie->updateFunc = item_update;

    cookie->type = GAMEOBJ_TYPE_ITEM;
    cookie->itemProps.onCollect = cookie_on_collect;

    cookie->itemProps.oscCenterY = pos.y;
    cookie->itemProps.oscAmplitude = 5.0f;
    cookie->itemProps.oscPeriod = 2.5f;

    return cookie;
}