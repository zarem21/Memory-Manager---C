// Jia Ling Chan and Majid Zare
// CSE 374 - HW6
// mem_impl.h
// 5/18/2020

#include "mem.h"

#ifndef MEM_IMPL_H
#define MEM_IMPL_H

#define DEFAULT_BLOCK 8192
#define THRESHOLD 16
#define HEADER_SIZE sizeof(freelist)

// Linked-list of free memory blocks that are available to satisfy
// memory allocation requests.
typedef struct freelist {
    // unsigned integer type that is capable of storing a data pointer.
    uintptr_t size;
    struct freelist* next;
} freelist;

extern freelist* root;
extern uintptr_t totalmalloc;

freelist * merge(freelist * block);
void split(freelist * block, uintptr_t reqSize);
void add(freelist * block);
void remove_block(freelist * block);


/*
* Uses assert to ensure that the free list data structure is
* problem-free.
*
* Checks for:
*   Blocks are ordered with strictly increasing memory addresses.
*
*   Block sizes are positive numvers and no smaller than whatever
*   minimum size you are using in your implementation.
*
*   Blocks do not overlap (start + length of a block) != another block
*
*   Blocks are not touching (start + length of a block) should not be
*   same address as the neck block on the list.
*/
void check_heap();

#endif
