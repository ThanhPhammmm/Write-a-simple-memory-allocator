#define MEMALLOC_H
#ifdef MEMALLOC_H

#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

typedef char ALIGN[32 ];

typedef union header{
    struct{
        size_t size;// denoting the size of user data, depending on the architecture, usually 4 or 8 bytes
        unsigned is_free;
        union header* next; // pointer to the next block in the linked list, depending on the architecture, usually 4 or 8 bytes
    } s;
    ALIGN stub;
} header_t;

header_t *head = NULL, *tail = NULL;
pthread_mutex_t global_malloc_lock;

header_t* get_free_block(size_t size);
void* mem_malloc(size_t size);
void mem_free(void* block);
void* mem_realloc(void* block, size_t size);
void* mem_calloc(size_t num, size_t nsize);

#endif