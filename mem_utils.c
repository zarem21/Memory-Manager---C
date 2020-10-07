// Jia Ling Chan and Majid Zare
// CSE 374 - HW 6
// mem_utils.c
// 5/22/2020

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <inttypes.h>
#include <string.h>
#include <errno.h>
#include "mem_impl.h"

freelist * root = NULL;
uintptr_t totalmalloc = 0;

/*
 * This method checks for possible problems with the free list data
 * structure. Specifically checks:
 *  - blocks are ordered with strictly increasing memory addresses
 *  - block sizes are positive numbers and no smaller than designated
 *      minimum size
 *  - blocks don't overlap
 *  - blocks are not touching
 */
void check_heap() {
    freelist * curr = root;
    while (curr) {
        // CHECK: blocks ordered in increasing memory addresses
        //          and not touching or overlapping
        if (curr -> next) {
            assert((uintptr_t) curr < (uintptr_t) curr -> next);
            assert((uintptr_t) curr -> next >
                                    (uintptr_t) curr + curr -> size);
        }

        // CHECK: block size > 0 and > THRESHOLD
        assert(curr -> size >= THRESHOLD);
        curr = curr -> next;
    }
}

/* The freelist behaviors: */

/*
 * This method merges adjacent blocks when a block is returned to the
 * free list.
 * Returns the pointer to the first block (first block that got merged)
 */
freelist * merge(freelist * block) {
    freelist * curr = root;
    while (curr -> next && curr -> next != block) {
        curr = curr -> next;
    }
    if ((uintptr_t)(curr) + curr -> size + HEADER_SIZE
            == (uintptr_t)(block)) {
        curr -> size += block -> size + HEADER_SIZE;
        curr -> next = block -> next;
        block = curr;
    }
    while (((uintptr_t) block + block -> size + HEADER_SIZE)
                == (uintptr_t) block -> next) {
        block -> size += (block -> next -> size + HEADER_SIZE);
        block -> next = block -> next -> next;
    }
    return block;
}

/*
 * This method splits block into two, satisfying size requirement
 */
void split(freelist * block, uintptr_t reqSize) {
    if (block -> size > reqSize + HEADER_SIZE + THRESHOLD) {
        freelist * newBlock = (freelist *)((uintptr_t)(block) + reqSize
                                                        + HEADER_SIZE);
        newBlock -> size = block -> size - reqSize - HEADER_SIZE;
        newBlock -> next = block -> next;
        block -> size = reqSize;
        block -> next = newBlock;
        assert(newBlock -> size > 0);
    }
}

/*
 * This method adds a block into the freelist linked-list.
 */
void add(freelist * block) {
    // if root is NULL, then the first block added to the list is
    // assigned to root.
    if (root) {
        freelist * curr = root;
        while (curr -> next
                && ((uintptr_t) curr -> next < (uintptr_t) block)) {
            curr = curr -> next;
        }
        block -> next = curr -> next;
        curr -> next = block;
        curr = merge(curr);
    } else {
        root = block;
    }
}

/*
 * This method removes a block from the free list
 */
void remove_block(freelist * block) {
    if (block != root) {
        freelist * curr = root;
        while (curr->next != block) {
            curr = curr->next;
        }
        curr -> next = block -> next;
        block -> next = NULL;
    } else {
        if (root -> next == NULL) {  // in case root is the only block
            root = NULL;
        } else {
            root = root -> next;
            block -> next = NULL;
        }
    }
}
