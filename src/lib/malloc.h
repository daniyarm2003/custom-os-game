#ifndef _OS_MALLOC_H
#define _OS_MALLOC_H

#include "../include/basictypes.h"
#include "../include/multiboot.h"

#define MALLOC_MEM_ALIGN 0x10

#define MALLOC_MEM_PREV_ALIGN(addr) ((addr) & ~(MALLOC_MEM_ALIGN - 1))
#define MALLOC_MEM_NEXT_ALIGN(addr) (MALLOC_MEM_PREV_ALIGN((addr) - 1) + MALLOC_MEM_ALIGN)

typedef struct __attribute__((aligned(MALLOC_MEM_ALIGN))) mem_block_header_t {
    uintptr_t size;

    struct mem_block_header_t* prev;
    struct mem_block_header_t* next;
} MemoryBlockHeader;

void memory_manager_init(multiboot_info_t* mBootInfo);

void* get_global_memory_pointer();
void* set_global_memory_pointer(void* ptr);
void* offset_global_memory_pointer(uintptr_t offset);

void* malloc(size_t bytes);
void* realloc(void* block, size_t bytes);
void free(void* block);

#endif