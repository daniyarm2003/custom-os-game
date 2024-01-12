#ifndef _OS_STRING_H
#define _OS_STRING_H

#include "../include/basictypes.h"

size_t strlen(const char* str);

void strcpy(char* dest, const char* src);
void strcat(char* dest, const char* src);

void uint_to_str(char* dest, u32 num);
void int_to_str(char* dest, s32 num);

char* strchr(const char* str, char ch);
s32 strcmp(const char* a, const char* b);

void sprintf(char* dest, const char* fmt, ...);

#endif