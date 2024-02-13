#include "malloc.h"
#include "memory.h"

#include "../drivers/terminal.h"
#include "../os/include/linker_symbols.h"

static uintptr_t globalMemoryPtr;
static uintptr_t globalMemoryEnd;

static MemoryBlockHeader* freeList = NULL;

void memory_manager_init(multiboot_info_t* mBootInfo) {
    globalMemoryPtr = 0;
    globalMemoryEnd = 0;

    for(multiboot_memory_map_t* mmap = (multiboot_memory_map_t*)mBootInfo->mmap_addr;
        (multiboot_uint32_t)mmap < mBootInfo->mmap_addr + mBootInfo->mmap_length;
        mmap = (multiboot_memory_map_t*)((multiboot_uint32_t)mmap + mmap->size + sizeof(mmap->size))) {

        uintptr_t addrLow = (uintptr_t)(mmap->addr & 0xFFFFFFFF);
        uintptr_t addrHigh = (uintptr_t)((mmap->addr >> 32) & 0xFFFFFFFF);

        uintptr_t sizeLow = (uintptr_t)(mmap->len & 0xFFFFFFFF);
        uintptr_t sizeHigh = (uintptr_t)((mmap->len >> 32) & 0xFFFFFFFF);

        if(addrHigh != 0 || sizeHigh != 0) {
            continue;
        }

        uintptr_t kernelEndPtr = (uintptr_t)&kernel_end;

        if(addrLow < kernelEndPtr) {
            uintptr_t memOffset = kernelEndPtr - addrLow;

            addrLow += memOffset;
            sizeLow -= memOffset;
        }

        if(sizeLow > globalMemoryEnd - globalMemoryPtr) {
            globalMemoryPtr = addrLow;
            globalMemoryEnd = globalMemoryPtr + sizeLow;
        }
    }
}

void* get_global_memory_pointer() {
    return (void*)globalMemoryPtr;
}

void* set_global_memory_pointer(void* ptr) {
    globalMemoryPtr = MALLOC_MEM_PREV_ALIGN((uintptr_t)ptr);
    return ptr;
}

void* offset_global_memory_pointer(uintptr_t offset) {
    globalMemoryPtr += MALLOC_MEM_NEXT_ALIGN(offset);
    return (void*)globalMemoryPtr;
}

static void remove_free_block_from_list(MemoryBlockHeader* block, uintptr_t alignedBlockLen) {
    if(block == freeList) {
        freeList = block->next;
    }
    else {
        block->prev->next = block->next;
    }

    if(block->next != NULL) {
        block->next->prev = block->prev;
    }

    if(alignedBlockLen + sizeof(MemoryBlockHeader) < block->size) {
        uintptr_t blockFragmentAddr = (uintptr_t)block + sizeof(MemoryBlockHeader) + alignedBlockLen;
        uintptr_t newBlockSize = block->size - alignedBlockLen - sizeof(MemoryBlockHeader);

        MemoryBlockHeader* blockFragment = (MemoryBlockHeader*)blockFragmentAddr;

        blockFragment->size = newBlockSize;
        
        blockFragment->prev = block->prev;
        blockFragment->next = block->next;

        if(blockFragment->prev != NULL) {
            blockFragment->prev->next = blockFragment;
        }
        else {
            freeList = blockFragment;
        }

        if(blockFragment->next != NULL) {
            blockFragment->next->prev = blockFragment;
        }

        block->size = alignedBlockLen;
    }
}

static MemoryBlockHeader* get_free_block_from_list(uintptr_t alignedBlockLen) {
    for(MemoryBlockHeader* block = freeList; block; block = block->next) {
        if(block->size >= alignedBlockLen) {
            remove_free_block_from_list(block, alignedBlockLen);
            return block;
        }
    }

    return NULL;
}

static MemoryBlockHeader* get_prev_free_block(uintptr_t newFreeBlockAddr) {
    MemoryBlockHeader* lastBlock = NULL;

    for(MemoryBlockHeader* block = freeList; block != NULL; block = block->next) {
        if((uintptr_t)block > newFreeBlockAddr) {
            return block->prev;
        }

        lastBlock = block;
    }

    return lastBlock;
}

static void join_adjacent_free_blocks(MemoryBlockHeader* newFreeBlock) {
    if(newFreeBlock->prev != NULL) {
        MemoryBlockHeader* prevBlock = newFreeBlock->prev;
        uintptr_t prevBlockBound = (uintptr_t)prevBlock + sizeof(MemoryBlockHeader) + prevBlock->size;

        if(prevBlockBound == (uintptr_t)newFreeBlock) {
            uintptr_t newSize = prevBlock->size + newFreeBlock->size + sizeof(MemoryBlockHeader);

            prevBlock->size = newSize;
            prevBlock->next = newFreeBlock->next;

            newFreeBlock = prevBlock;
        }
    }

    if(newFreeBlock->next != NULL) {
        MemoryBlockHeader* nextBlock = newFreeBlock->next;
        uintptr_t curBlockBound = (uintptr_t)newFreeBlock + sizeof(MemoryBlockHeader) + newFreeBlock->size;

        if(curBlockBound == (uintptr_t)nextBlock) {
            uintptr_t newSize = newFreeBlock->size + nextBlock->size + sizeof(MemoryBlockHeader);

            newFreeBlock->size = newSize;
            newFreeBlock->next = nextBlock->next;
        }
    }
}

void* malloc(size_t bytes) {
    uintptr_t alignedBlockLen = (uintptr_t)MALLOC_MEM_NEXT_ALIGN(bytes);
    MemoryBlockHeader* freeBlock = get_free_block_from_list(alignedBlockLen);

    if(freeBlock != NULL) {
        uintptr_t blockMemory = (uintptr_t)freeBlock + sizeof(MemoryBlockHeader);
        return (void*)blockMemory;
    }

    void* memoryPtr = get_global_memory_pointer();
    MemoryBlockHeader* newBlock = (MemoryBlockHeader*)memoryPtr;

    offset_global_memory_pointer(sizeof(MemoryBlockHeader) + alignedBlockLen);

    newBlock->size = alignedBlockLen;

    uintptr_t newBlockMemory = (uintptr_t)newBlock + sizeof(MemoryBlockHeader);
    return (void*)newBlockMemory;
}

void* realloc(void* block, size_t bytes) {
    uintptr_t blockHeaderAddr = (uintptr_t)block - sizeof(MemoryBlockHeader);
    MemoryBlockHeader* blockHeader = (MemoryBlockHeader*)blockHeaderAddr;

    uintptr_t alignedBlockLen = (uintptr_t)MALLOC_MEM_NEXT_ALIGN(bytes);

    if(blockHeader->size == alignedBlockLen) {
        return block;
    }

    else if(blockHeader->size > alignedBlockLen) {
        uintptr_t freeMemory = blockHeader->size - alignedBlockLen;

        if(freeMemory > sizeof(MemoryBlockHeader)) {
            uintptr_t newFreeBlockAddr = blockHeaderAddr + sizeof(MemoryBlockHeader) + alignedBlockLen;

            MemoryBlockHeader* newFreeBlock = (MemoryBlockHeader*)newFreeBlockAddr;
            void* newFreeBlockMemory = (void*)(newFreeBlockAddr + sizeof(MemoryBlockHeader));

            newFreeBlock->size = freeMemory - sizeof(MemoryBlockHeader);
            free(newFreeBlockMemory);
            
            blockHeader->size = alignedBlockLen;
        }

        return block;
    }
    else {
        void* newMemBlock = malloc((size_t)alignedBlockLen);
        memcpy(newMemBlock, block, (size_t)alignedBlockLen);

        free(block);

        return newMemBlock;
    }
}

void free(void* block) {
    uintptr_t blockHeaderAddr = (uintptr_t)block - sizeof(MemoryBlockHeader);
    MemoryBlockHeader* blockHeader = (MemoryBlockHeader*)blockHeaderAddr;
    
    blockHeader->prev = NULL;
    blockHeader->next = NULL;

    if(freeList == NULL) {
        freeList = blockHeader;
        return;
    }

    MemoryBlockHeader* prevBlock = get_prev_free_block(blockHeaderAddr);
    
    if(prevBlock == NULL) {
        blockHeader->next = freeList;
        freeList->prev = blockHeader;

        freeList = blockHeader;
    }
    else {
        blockHeader->prev = prevBlock;
        blockHeader->next = prevBlock->next;

        prevBlock->next = blockHeader;
        
        if(blockHeader->next != NULL) {
            blockHeader->next->prev = blockHeader;
        }
    }

    join_adjacent_free_blocks(blockHeader);
}

void debug_free_list() {
    if(freeList == NULL) {
        terminal_printf("EMPTY FREE LIST\n");
    }
    else {
        terminal_printf("FREE LIST:\n");
    }

    for(MemoryBlockHeader* freeBlock = freeList; freeBlock != NULL; freeBlock = freeBlock->next) {
        terminal_printf("BLOCK ADDR: %d, SIZE: %d, SIZEOF HEADER: %d\n", (uintptr_t)freeBlock, freeBlock->size, sizeof(MemoryBlockHeader));
    }
}