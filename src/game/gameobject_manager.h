#ifndef _OS_GAMEOBJECT_MANAGER_H
#define _OS_GAMEOBJECT_MANAGER_H

#include "gameobject.h"

typedef struct gameobject_iterator_t GameObjectIterator;

GameObjectIterator* gameobject_iterator_get_head();
GameObjectIterator* gameobject_iterator_get_next(GameObjectIterator* iter);
GameObject* gameobject_iterator_get_object(GameObjectIterator* iter);

void game_add_gameobject(GameObject* obj);

void game_update_gameobjects(f32 dt);
void game_draw_gameobjects();

void game_terminate_gameobjects();

#endif