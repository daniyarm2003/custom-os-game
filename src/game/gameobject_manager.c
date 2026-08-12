#include "gameobject_manager.h"
#include "../lib/malloc.h"

struct gameobject_iterator_t {
    GameObject* obj;
    GameObjectIterator* next;
};

static GameObjectIterator* gameObjectListHead = NULL;
static GameObjectIterator* gameObjectListTail = NULL;

GameObjectIterator* gameobject_iterator_get_head() {
    return gameObjectListHead;
}

GameObjectIterator* gameobject_iterator_get_next(GameObjectIterator* iter) {
    return iter ? iter->next : NULL;
}

GameObject* gameobject_iterator_get_object(GameObjectIterator* iter) {
    return iter ? iter->obj : NULL;
}

void game_add_gameobject(GameObject* obj) {
    GameObjectIterator* newIter = malloc(sizeof(GameObjectIterator));
    newIter->obj = obj;
    newIter->next = NULL;

    if(gameObjectListTail) {
        gameObjectListTail->next = newIter;
    }
    else {
        gameObjectListHead = newIter;
    }

    gameObjectListTail = newIter;
}

void game_update_gameobjects(f32 dt) {
    for(GameObjectIterator* iter = gameobject_iterator_get_head(); iter; iter = gameobject_iterator_get_next(iter)) {
        GameObject* obj = gameobject_iterator_get_object(iter);
        gameobject_update(obj, dt);
    }

    // Remove destroyed game objects after updating
    GameObjectIterator* prev = NULL;
    GameObjectIterator* cur = gameobject_iterator_get_head();

    while(cur) {
        GameObject* obj = gameobject_iterator_get_object(cur);

        if(gameobject_is_destroyed(obj)) {
            GameObjectIterator* toRemove = cur;

            if(prev) {
                prev->next = cur->next;
            }
            else {
                gameObjectListHead = cur->next;
            }

            if(cur == gameObjectListTail) {
                gameObjectListTail = prev;
            }

            cur = cur->next;

            gameobject_free(obj);
            free(toRemove);
        }
        else {
            prev = cur;
            cur = cur->next;
        }
    }
}

void game_draw_gameobjects() {
    for(GameObjectDrawLayer layer = 0; layer < GAMEOBJ_DRAW_LAYER_COUNT; layer++) {
        for(GameObjectIterator* iter = gameobject_iterator_get_head(); iter; iter = gameobject_iterator_get_next(iter)) {
            GameObject* obj = gameobject_iterator_get_object(iter);
            gameobject_draw(obj, layer);
        }
    }
}

void game_terminate_gameobjects() {
    GameObjectIterator* iter = gameobject_iterator_get_head();

    while(iter) {
        GameObject* obj = gameobject_iterator_get_object(iter);
        gameobject_free(obj);

        GameObjectIterator* toFree = iter;
        iter = gameobject_iterator_get_next(iter);
        free(toFree);
    }

    gameObjectListHead = NULL;
    gameObjectListTail = NULL;
}