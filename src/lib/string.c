#include "string.h"

#include <stdarg.h>

size_t strlen(const char* str) {

    const char* ch;
    for(ch = str; *ch; ch++);

    return (size_t)(ch - str);
}

void strcpy(char* dest, const char* src) {
    while(*src) {
        *(dest++) = *(src++);
    }

    *dest = '\0';
}

void strcat(char* dest, const char* src) {
    while(*dest) {
        dest++;
    }

    strcpy(dest, src);
}

void uint_to_str(char* dest, u32 num) {
    char numStack[16];
    size_t numStackSize = 0;

    if(num == 0) {
        *(dest++) = '0';
        *dest = '\0';

        return;
    }

    while(num != 0) {
        numStack[numStackSize++] = '0' + (num % 10);
        num /= 10;
    }

    while(numStackSize != 0) {
        *(dest++) = numStack[numStackSize - 1];
        numStackSize--;
    }

    *dest = '\0';
}

void int_to_str(char* dest, s32 num) {
    if(num < 0) {
        *(dest++) = '-';
        num = -num;
    }

    uint_to_str(dest, (u32)num);
}

char* strchr(const char* str, char ch) {
    const char* chPtr;
    for(chPtr = str; *chPtr; chPtr++) {
        if(*chPtr == ch) {
            return (char*)chPtr;
        }
    }

    return ch == '\0' ? (char*)chPtr : NULL;
}

s32 strcmp(const char* a, const char* b) {
    while(*a || *b) {
        if(*a != *b) {
            break;
        }

        a++;
        b++;
    }

    return (s32)((u8)*a - (u8)*b);
}

static void sprintf_str(char** destPtr, const char* str) {
    for(const char* chPtr = str; *chPtr; chPtr++) {
        **destPtr = *chPtr;
        (*destPtr)++;
    }
}

static void sprintf_int(char** destPtr, s32 num) {
    char numBuf[16];
    int_to_str(numBuf, num);

    sprintf_str(destPtr, numBuf);
}

void sprintf(char* dest, const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);

    bool formatting = false;

    for(const char* fmtCh = fmt; *fmtCh; fmtCh++) {
        if(formatting) {
            switch (*fmtCh) {
            case 'c':

                char charArg = va_arg(args, int);
                *(dest++) = charArg;

                break;

            case 's':

                const char *strArg = va_arg(args, const char *);
                sprintf_str(&dest, strArg);

                break;

            case 'd':

                s32 intArg = va_arg(args, s32);
                sprintf_int(&dest, intArg);

                break;

            default:

                *(dest++) = *fmtCh;
                break;
            }

            formatting = false;
        }
        else if(*fmtCh == '%') {
            formatting = true;
        }
        else {
            *(dest++) = *fmtCh;
        }
    }

    *dest = '\0';
    va_end(args);
}