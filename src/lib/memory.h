#ifndef _OS_MEMORY_H
#define _OS_MEMORY_H

#include "../include/basictypes.h"

void memset(void* dest, u8 data, size_t len);
void memzero(void* dest, size_t len);

void memcpy(void* dest, const void* src, size_t len);
void memcpy_r(void* dest, const void* src, size_t len);

void memset_v(volatile void* dest, u8 data, size_t len);
void memzero_v(volatile void* dest, size_t len);

void memcpy_v(volatile void* dest, const volatile void* src, size_t len);
void memcpy_rv(volatile void* dest, const volatile void* src, size_t len);

#endif