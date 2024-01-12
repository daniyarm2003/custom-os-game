#include "memory.h"

void memset(void* dest, u8 data, size_t len) {
    u8* destBytes = (u8*)dest;

    for(size_t i = 0; i < len; i++) {
        destBytes[i] = data;
    }
}

void memzero(void* dest, size_t len) {
    memset(dest, 0, len);
}

void memcpy(void* dest, const void* src, size_t len) {
    u8* destBytes = (u8*)dest;
    u8* srcBytes = (u8*)src;

    for(size_t i = 0; i < len; i++) {
        destBytes[i] = srcBytes[i];
    }
}

void memcpy_r(void* dest, const void* src, size_t len) {
    u8* destBytes = (u8*)dest;
    u8* srcBytes = (u8*)src;

    for(size_t i = 0; i < len; i++) {
        destBytes[len - i - 1] = srcBytes[len - i - 1];
    }
}

void memset_v(volatile void* dest, u8 data, size_t len) {
    volatile u8* destBytes = (volatile u8*)dest;

    for(size_t i = 0; i < len; i++) {
        destBytes[i] = data;
    }
}

void memzero_v(volatile void* dest, size_t len) {
    memset_v(dest, 0, len);
}

void memcpy_v(volatile void* dest, const volatile void* src, size_t len) {
    volatile u8* destBytes = (volatile u8*)dest;
    volatile u8* srcBytes = (volatile u8*)src;

    for(size_t i = 0; i < len; i++) {
        destBytes[i] = srcBytes[i];
    }
}

void memcpy_rv(volatile void* dest, const volatile void* src, size_t len) {
    volatile u8* destBytes = (volatile u8*)dest;
    volatile u8* srcBytes = (volatile u8*)src;

    for(size_t i = 0; i < len; i++) {
        destBytes[len - i - 1] = srcBytes[len - i - 1];
    }
}