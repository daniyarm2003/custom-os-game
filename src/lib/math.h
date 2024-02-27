#ifndef MATH_H
#define MATH_H

#include "../include/basictypes.h"

#define PI 3.14159265358979

extern f32 __fsqrt_util(f32 num);
extern f32 __fsin_util(f32 num);
extern f32 __fcos_util(f32 num);

f32 sqrtf(f32 num);
f32 sinf(f32 num);
f32 cosf(f32 num);

f32 floorf(f32 num);
f32 fmodf(f32 num, f32 modulo);

#endif