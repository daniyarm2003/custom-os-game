#include "goal.h"
#include "../../images/images.h"
#include "../game.h"
#include "../../include/basicmacros.h"
#include "items.h"

static void goal_on_collect(GameObject* goal) {
    UNUSED(goal);

    game_advance_to_next_level();
    game_add_score(GOAL_SCORE_VALUE);
}

GameObject* goal_create(Vec2 pos) {
    GameObject* goal = gameobject_create();

    goal->pos = pos;
    goal->size = (Vec2){35.0f, 35.0f};

    goal->renderType = GAMEOBJ_RENDER_TEXTURED;
    goal->renderData.texture = &goal_image_data;

    goal->updateFunc = item_update;

    goal->type = GAMEOBJ_TYPE_ITEM;
    goal->itemProps.onCollect = goal_on_collect;

    goal->itemProps.oscCenterY = pos.y;
    goal->itemProps.oscAmplitude = 7.5f;
    goal->itemProps.oscPeriod = 2.5f;

    return goal;
}