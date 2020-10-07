// Jia Ling Chan & Majid Zare
// CSE 374 - HW6
// getmem.c
// 5/18/2020

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "mem.h"
#include "mem_impl.h"

/*
 * This method returns a pointer to a new block of storage with at least
 * "size" bytes of memory.
 * Pre: size > 0 (if not, returns NULL)
 */

/*
 * If no block can satisfy getmem(size):
 *  - Acquire a good-sized block of storage from the underlying system
 *      and add to the free list
 *  - Split large block into a block that satisfies the request,
 *      and the rest onto freelist
 *  - Default allocation size will be 8k, but if size if greater than
 *      8k, then we allocate size + default_size onto the freelist.
 */

void testPrint();
void * getmem(uintptr_t size) {
    if (size == 0) {
      return NULL;
    }

    if (size % 16 != 0) {
      size = (((size -1) / 16 + 1) * 16) + 16;
    }

    check_heap();
    uintptr_t max_size = (size + HEADER_SIZE >= DEFAULT_BLOCK) ?
                (size + DEFAULT_BLOCK) : DEFAULT_BLOCK;
    freelist *currNode = root;

    while (currNode) {
      if (currNode -> size >= size) {
        if (currNode -> size >= THRESHOLD + size + HEADER_SIZE) {
            split(currNode, size);
        }
        remove_block(currNode);
        return (void*)((uintptr_t)currNode + HEADER_SIZE);
      } else {
        currNode = currNode -> next;
      }
    }

    // If no block of memory is big enough in the freelist:
    freelist* newNode = (freelist*)malloc(max_size);
    totalmalloc += max_size;

    newNode -> size = max_size - HEADER_SIZE;
    add(newNode);
    if (newNode -> size >= THRESHOLD + HEADER_SIZE + size) {
        split(newNode, size);
    }
    remove_block(newNode);

    check_heap();
    return (void*)((uintptr_t)newNode + HEADER_SIZE);
}
