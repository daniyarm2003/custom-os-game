#ifndef _OS_VEC2_H
#define _OS_VEC2_H

#include "../include/basictypes.h"

typedef struct vec2_t {
    f32 x, y;
} Vec2;

Vec2 vec2_init();

void vec2_copy(Vec2* dest, Vec2 src);

f32 vec2_mag(Vec2 vec);
f32 vec2_sqr_mag(Vec2 vec);

void vec2_add(Vec2* dest, Vec2 src);
void vec2_sub(Vec2* dest, Vec2 src);

void vec2_mult(Vec2* dest, f32 scalar);
void vec2_div(Vec2* dest, f32 scalar);

void vec2_normalize(Vec2* vec);

f32 vec2_dot(Vec2 a, Vec2 b);

#endif