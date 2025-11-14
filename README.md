Text section: The part that contains the binary instructions to be executed by the processor.

Data section: Contains non-zero initialized static data.

BSS (Block Started by Symbol) : Contains zero-initialized static data. Static data uninitialized in program is initialized 0 and goes here.

Heap: Contains the dynamically allocated data.

<img width="898" height="296" alt="image" src="https://github.com/user-attachments/assets/3086eab8-4923-4687-ac36-97d71fed5646" />

----------------------------------------------------------------
Comparison of malloc, calloc, and realloc in C

<img width="1160" height="327" alt="image" src="https://github.com/user-attachments/assets/fdd66501-c023-4a36-82c8-70f5622138f2" />
Additional Notes:

-Malloc and calloc return NULL if allocation fails.

-Realloc can move the memory block to a new location if the existing one cannot fit the new size.

-Always free() memory when no longer needed to avoid memory leaks.
