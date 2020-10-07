// Jia Ling Chan and Majid Zare
// CSE 374 - HW 6
// get_mem_stats.c
// 5/22/2020

#include "mem.h"
#include "mem_impl.h"
/*
 * This method stores statistics about the current state of the memory
 * manager in the three integer variables given as arguments.
 *  - total_size: total amount of storage (bytes) acquired by memory
 *                  manager so far.
 *  - total_free: the total amount of storage in bytes that's currently
 *                  stored on the free list, including space occupied by
 *                  header information or links in free blocks.
 *  - n_free_blocks: total number of individual blocks currently stored
 *                      on the free list.
 */

void get_mem_stats(uintptr_t* total_size, uintptr_t* total_free,
                    uintptr_t* n_free_blocks) {
    *total_size = totalmalloc;
    *total_free = 0;
    *n_free_blocks = 0;

    freelist* currNode = root;
    check_heap();
    while (currNode) {
        *n_free_blocks = *n_free_blocks + 1;
        *total_free = *total_free + (currNode -> size + HEADER_SIZE);
        currNode = currNode -> next;
    }
}
