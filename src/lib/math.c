#include "math.h"

f32 sqrtf(f32 num) {
    return __fsqrt_util(num);
}

f32 sinf(f32 num) {
    return __fsin_util(num);
}

f32 cosf(f32 num) {
    return __fcos_util(num);
}

f32 floorf(f32 num) {
    s32 trunc = (s32)num;
    return (f32)trunc;
}

f32 fmodf(f32 num, f32 modulo) {
    f32 truncQuotient = floorf(num / modulo);
    return num - modulo * truncQuotient;
}