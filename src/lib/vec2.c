#include "vec2.h"
#include "math.h"

Vec2 vec2_init() {
    Vec2 vec;

    vec.x = 0.0f;
    vec.y = 0.0f;

    return vec;
}

void vec2_copy(Vec2* dest, Vec2 src) {
    dest->x = src.x;
    dest->y = src.y;
}

f32 vec2_sqr_mag(Vec2 vec) {
    return vec.x * vec.x + vec.y * vec.y;
}

f32 vec2_mag(Vec2 vec) {
    return sqrtf(vec2_sqr_mag(vec));
}

void vec2_add(Vec2* dest, Vec2 src) {
    dest->x += src.x;
    dest->y += src.y;
}

void vec2_sub(Vec2* dest, Vec2 src) {
    dest->x -= src.x;
    dest->y -= src.y;
}

void vec2_mult(Vec2* dest, f32 scalar) {
    dest->x *= scalar;
    dest->y *= scalar;
}

void vec2_div(Vec2* dest, f32 scalar) {
    dest->x /= scalar;
    dest->y /= scalar;
}

void vec2_normalize(Vec2* vec) {
    if(vec->x != 0.0f || vec->y != 0.0f) {
        f32 mag = vec2_mag(*vec);
        vec2_div(vec, mag);
    }
}

f32 vec2_dot(Vec2 a, Vec2 b) {
    return a.x * b.x + a.y * b.y;
}