// Jia Ling Chan and Majid Zare
// CSE 374 - HW6
// bench.c
// 5/18/2020

/*
* This program executes a large number of calls to functions getmem and
* freemem to allocate a free blocks of random sizes and in random
* order. Users can specify:
*  - ntrials: total number of getmem and freemem calls (default: 10000)
*  - pctget: percent of total getmem/freemem calls that are getmem
*              (default: 50)
*  - pctlarge: percent of getmem calls that should request "large"
*              blocks with a size greater than small_limit
*              (default: 10)
*  - small_limit: largest size (bytes) of a "small" block
*                  (default: 200)
*  - large_limit: largest size (bytes) of a "large" block.
*                  (default: 20000)
*  - random_seed: initial seed value for the random number generator.
*                  (default: system time-of-day clock)
* bench [ntrials] [pctget] [pctlarge] [small_limit] [large_limit]
* 			[random_seed]
* If no arguments are provided, bench will use its default values for
* all variables above.
*/

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <time.h>
#include "mem.h"
#include "mem_impl.h"

void initialize(int argc, char**argv, int *ntrials, int *pctget,
                int *pctlarge, int *small_limit, int *large_limit,
                unsigned int *random_seed);
int random(int lower, int upper);
void printStats(time_t start);
void fill_mem(void* ptr, uintptr_t size);

int main(int argc, char** argv) {
    // makes sure the correct number of arguments are entered.
    if (argc > 7) {
        fprintf(stderr, "bench: max 6 args only");
        return EXIT_FAILURE;
    }

    int ntrials = 10000;
    int pctget = 50;
    int pctlarge = 10;
    int small_limit = 200;
    int large_limit = 20000;
    unsigned int random_seed = (unsigned int) time(NULL);

    initialize(argc, argv, &ntrials, &pctget, &pctlarge, &small_limit,
               &large_limit, &random_seed);
    srand(random_seed);  // initializes seed for rand number generation

    // Array that keeps track of memory pointers returned by getmem()
    void* pointers[ntrials];
    int sizeArray = 0;
    time_t start_t = clock();

    int randPCTGET = 0;
    int randPCTLARGE = 0;
    int randSize = 0;
    int randomFree = 0;
    void* memPtr;

    // This block handles the calls to getmem() and freemem().
    for (int i = 0; i < ntrials; i++) {
        randPCTGET = random(1, 100);
        if (randPCTGET <= pctget) {
            randPCTLARGE = random(1, 100);
            if (randPCTLARGE <= pctlarge) {
                randSize = random(small_limit, large_limit);
            } else {
                randSize = random(1, small_limit);
            }
            memPtr = getmem(randSize);
            sizeArray++;
            pointers[sizeArray - 1] = memPtr;
            if (memPtr != NULL) {
                fill_mem(memPtr, randSize);
            }
            // This else case calls freemem(void* p)
        } else {
            if (sizeArray != 0) {
                randomFree = random(0, sizeArray - 1);
                freemem(pointers[randomFree]);
                pointers[randomFree] = pointers[sizeArray - 1];
                sizeArray--;
            }
        }
        if ((ntrials >= 10) && i % (ntrials/10) == 0) {
            printStats(start_t);
        }
    }

    return 0;
}

// Initializes parameters that control the test bench. If parameters are
// not provided by the user, default values will be used.
void initialize(int argc, char**argv, int *ntrials, int *pctget,
int *pctlarge, int *small_limit, int *large_limit,
unsigned int *random_seed) {
    if (argc > 1) {
        for (int i = 1; i < argc; i++) {
            switch (i) {
                case 1:
                *ntrials = atoi(argv[i]);
                break;
                case 2:
                *pctget = atoi(argv[i]);
                break;
                case 3:
                *pctlarge = atoi(argv[i]);
                break;
                case 4:
                *small_limit = atoi(argv[i]);
                break;
                case 5:
                *large_limit = atoi(argv[i]);
                break;
                case 6:
                *random_seed = atoi(argv[i]);
                break;
                default: printf("Default option values will be used");
                break;
            }
        }
    }
}


// Takes in a lower and upper boundary of a random number,
// and returns a random int within that range.
int random(int lower, int upper) {
    return (rand() % (upper - lower + 1)) + lower;
}

// This method prints the following statistics about
// the memory manager when called:
// Total CPU time used
// Total amount of storage acquired from the underlying system
// Total number of blocks on the freelist at point of call.
// Average number of bytes in the freelist block.
void printStats(time_t start) {
    uintptr_t storage, free_blocks_bytes, tot_blocks;
    int us;
    double avg_blocks;
    time_t time_elapsed = clock() - start;

    us = (int) ((time_elapsed * 1000000.0) / CLOCKS_PER_SEC);
    get_mem_stats(&storage, &free_blocks_bytes, &tot_blocks);

    avg_blocks = (tot_blocks > 0) ?
    (free_blocks_bytes / tot_blocks) : (0);
    printf("Time elapsed: %d micro-seconds\n", us);
    printf("Total storage: %d bytes\n", (int)storage);
    printf("Total free block bytes: %d\n", (int)free_blocks_bytes);
    printf("Free blocks: %d, Average bytes in a block = %f bytes \n",
    (int)tot_blocks, avg_blocks);
    printf("\n");
}

/*
* Assumption: ptr != NULL
* This method stores 0xFE in each of the first 16 bytes of the
* allocated block starting at the pointer address returned by getmem.
* If size < 16, all requested bytes are initialized to 0xFE.
*/
void fill_mem(void* ptr, uintptr_t size) {
    uintptr_t memadd = (uintptr_t) ptr;
    // unsigned char hexVal = 0xFE;
    for (int i = 0; i < 16 && i < size; i++) {
        *((unsigned char*) (memadd+1)) = 0xFE;
    }
}


