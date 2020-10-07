Jia Ling Chan and Majid Zare (chza)
CSE 374 - HW 6
README
5/29/2020


The free list data is organized much like a linked list, where each
block of memory points to its neighbor and stores their size (in bytes).
Some features of this free list is that each individual block can split
(assuming it is big enough) into two blocks of a specified size. Blocks
can also merge to make bigger chunks of usable memory. The free list is
organized to be in increasing order of size, and adjacent blocks do not
touch or overlap.

One added improvement we made was checking that the the number of
user-specified arguments did not exceed 7 in our benchmark code.

Performance Summary:
 - time per trial (getmem or freemem) is under 1 ms. This is pretty fast
	for memory allocation. Generally, the larger the bytes, the longer
	each operation takes, but overall it is very efficient.
 - The use of memory was quite efficient because we split blocks to
	maximize usable memory in the freelist, while also merging newly
	reallocated usable memory (freemem) with their adjacent blocks.
	Thus, the number of malloc calls are significantly decreased,
	thereby saving memory.

We mostly consulted the Linked List data structure code from lecture
when building our free list. In addition, the Makefile closely resembles
the example used in class. We referenced several different git hub
accounts with different forms of memory management (some in different
languages), and we had to use sources such as Stack Overflow and Oracle
docs to learn more about types such as uintptr_t and void pointer. We
also consulted a thread from Stack Overflow to generate a random_seed
using the time of day in our bench program.
