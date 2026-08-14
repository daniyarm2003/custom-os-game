#include "items.h"

#include "../../lib/math.h"
#include "../../include/basicmacros.h"

void item_update(GameObject* item, f32 dt) {
    UNUSED(dt);

    f32 t = item->timer;
    f32 amp = item->itemProps.oscAmplitude;
    f32 centerY = item->itemProps.oscCenterY;
    f32 period = item->itemProps.oscPeriod;

    f32 theta = 2.0 * PI * t / period;

    item->pos.y = centerY + amp * sinf(theta);
}