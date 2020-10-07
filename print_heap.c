// Jia Ling Chan and Majid Zare
// CSE 374 - HW 6
// print_heap.c
// 5/22/2020

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <inttypes.h>
#include "mem_impl.h"
/*
 * This method prints a formatted listing on file f showing the blocks
 * on the free list. Each line of output describes one free block
 * and begin with two hexadecimal numbers giving the address and length
 * of that block.
 */
void print_heap(FILE * f) {
    if (f) {
        freelist * curr = root;
        while (curr) {
            fprintf(f, "address: %ld | length: %ld \n", (uintptr_t)curr,
                        curr -> size);
            curr = curr -> next;
        }
    }
}
