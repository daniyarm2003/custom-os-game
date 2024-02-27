#ifndef _OS_BASIC_MACROS_H
#define _OS_BASIC_MACROS_H

#define UNUSED(x) ((void)(x))

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

#define CLAMP(x, a, b) MIN(MAX(x, a), b)

#endif