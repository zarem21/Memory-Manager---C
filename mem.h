// Jia Ling Chan and Majid Zare
// CSE 374 - HW6
// mem.h header file
// 5/18/2020

#include <inttypes.h>
#include <stdio.h>

#ifndef MEM_H
#define MEM_H

/*
* pre: size > 0
* post: returns NULL if size is negative or getmem cannot satisfy the
*       request.
* Return a pointer to a new block of storage w/ atleast "size" bytes
* of memory.
*/
void* getmem(uintptr_t size);

/*
* Returns the block of storage at location p to the pool of available
* free storage.
* Input: p is a result of getmem(unitptr_t size)
* If p == NULL, call to freemem has no effect, returns immediately.
*
* if the block is physically located in memory adjacent to one or more
* other free blocks, then the free blocks involved should be combined
* into a single larger block, rather than adding the small blocks to the
* free list individually.
*/
void freemem(void* p);

/*
* This function stores statistics about the current state of the memory
* manager into three integer variables whose addresses are given as
* arguments.
*
* Parameters:
* total_size: Total amount of storage in bytes requested from the
*               underlying system.
* total_free: Total amount of storage in bytes that is currently stored
*               on the free list, including any space occupied by header
*               information or links in the free blocks.
* n_free_blocks: Total number of indiivdual blocks currently stored on
*                   the free list.
*
*/
void get_mem_stats(uintptr_t* total_size, uintptr_t* total_free,
                    uintptr_t* n_free_blocks);

/*
* Prints a formatted listing on file "f" showing the blocks on the free
* list. Each line of output describes one free block and begins with two
* hexadecimal numbers: 0xdddddddd where d is a hex digit giving the
* address and legnth of that block.
*/
void print_heap(FILE * f);

#endif
