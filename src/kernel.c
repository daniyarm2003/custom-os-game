#include "lib/string.h"
#include "lib/memory.h"
#include "include/basicmacros.h"
#include "include/multiboot.h"
#include "drivers/terminal.h"
#include "os/idt/idt.h"
#include "drivers/timer.h"
#include "os/include/linker_symbols.h"
#include "drivers/graphics.h"
#include "lib/math.h"
#include "images/images.h"
#include "game/gameobject_manager.h"

void testobj_update(GameObject* obj, f32 dt) {
    obj->pos.x += 100.0f * dt;
    obj->pos.y += 100.0f * dt;

    if(obj->pos.x > 400.0f) {
        obj->pos.x = 100.0f;
    }

    if(obj->pos.y > 300.0f) {
        obj->pos.y = 100.0f;
    }
}

void kmain(multiboot_info_t* mBootInfo, u32 magic) {
    UNUSED(magic);

    idt_init();
    terminal_init();

    memory_manager_init(mBootInfo);
    graphics_init(mBootInfo);

    GameObject* testObj = gameobject_create();

    testObj->pos.x = 100.0f;
    testObj->pos.y = 100.0f;

    testObj->renderData.solidColor.value = 0xFF8800;
    testObj->updateFunc = testobj_update;

    game_add_gameobject(testObj);

    f32 dt = 0.01f;
    timer_t lastFrameTime = timer_get_ticks();

    f32 test = 0.0f;
    char timeText[64] = { 0 };

    while(true) {
        game_update_gameobjects(dt);
        
        graphics_clear_buffer();

        game_draw_gameobjects();

        sprintf(timeText, "Time: %d seconds", (s32)test);
        graphics_draw_text(10, 10, timeText, &font_monospace_image_data, 16, (Color){ .value = 0xFFFFFF });

        graphics_update_buffer();

        sleep_for_timer_ticks(10);

        timer_t currentTime = timer_get_ticks();
        timer_t elapsedTime = currentTime - lastFrameTime;

        timer_t freq = timer_get_current_frequency();

        lastFrameTime = currentTime;
        dt = (f32)elapsedTime / (f32)freq;

        test += dt;
    }

    game_terminate_gameobjects();
    graphics_terminate();
}