#include "memalloc.h"

int main(){
    printf("%zu\n", sizeof(header_t));//(8(size_t) + 4(unsigned) + 4(padding) + 8(pointer)) and 32(ALIGN padding), but union takes the largest member size=32
    /*-------------------------------
    * Simulate malloc with header  *
    -------------------------------*/
    size_t user_size = 49;

    // Allocate header + user block manually
    header_t* header = (header_t*)mem_malloc(sizeof(header_t) + user_size);
    if (!header) {
        printf("malloc failed\n");
        return 1;
    }

    void* user_block = (void*)(header + 1); // pointer to user memory

    printf("Header address: %p\n", (void*)header);
    printf("User block address: %p\n", user_block);
    printf("Header size: %zu bytes\n", sizeof(header_t));
    printf("User requested size: %zu bytes\n", user_size);

    // Check alignment
    printf("Header alignment modulo 16: %zu\n", (uintptr_t)header % 16);
    printf("User block alignment modulo 16: %zu\n", (uintptr_t)user_block % 16);

    // Fill user block for demo
    unsigned char* p = (unsigned char*)user_block;
    for (size_t i = 0; i < user_size; i++) p[i] = i + 1;

    printf("User block contents first 10 bytes:\n");
    for (size_t i = 0; i < 10 && i < user_size; i++) {
        printf("%d ", p[i]);
    }
    printf("\n");

    // -------------------------------
    // Free memory
    // -------------------------------
    mem_free(header);

    return 0;
}