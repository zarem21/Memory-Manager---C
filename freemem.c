// Jia Ling Chan and Majid Zare
// CSE 374 - HW6
// freemem.c
// 5/18/2020

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "mem.h"
#include "mem_impl.h"

/*
 * This method returns the block of storage at location "p" to the pool
 * of available free storage. If the block is physically located in
 * memory adjacent to one or more other free blocks, then the free
 * blocks involved are combined into a single larger block.
 */

void freemem(void* p) {
    // return immediately if p is NULL
    if (p == NULL) {
        return;
    }

    /*
     * If p has other value than one returned by getmem, OR
     * If block it points to has previously been freed, THEN
     * freemem operation undefined
     */

    check_heap();
    // to find real address of the block:
    freelist * pblock = (freelist*)((uintptr_t)p - HEADER_SIZE);
    freelist * curr = root;
    freelist * last = root;

    if ((uintptr_t) curr > (uintptr_t) pblock) {
        pblock -> next = curr;
        root = pblock;
    } else {
        curr = curr -> next;
        while (curr && ((uintptr_t) curr < (uintptr_t) pblock)) {
            last = curr;
            curr = curr -> next;
        }
        pblock -> next = curr;
        last -> next = pblock;
    }

    pblock = merge(pblock);
    check_heap();
}
