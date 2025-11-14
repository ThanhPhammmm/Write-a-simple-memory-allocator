#include "memalloc.h"

header_t *head = NULL, *tail = NULL;
pthread_mutex_t global_malloc_lock;

/*C pointer arithmetic: ptr + n = ptr + n*sizeof(*ptr)*/

header_t* get_free_block(size_t size){
    header_t *current = head;
    while(current){
        if(current->s.is_free && current->s.size >= size){
            return current;
        }
        current = current->s.next;
    }
    return NULL;
}

void* mem_malloc(size_t size){
    if(size <= 0){
        return NULL;
    }
    pthread_mutex_lock(&global_malloc_lock);

    header_t *current = get_free_block(size);
    if(current){    
        current->s.is_free = 0;
        pthread_mutex_unlock(&global_malloc_lock);
        return (void*)(current + 1); // return pointer to memory after header
    }
    size_t total_size = sizeof(header_t) + size;
    current = sbrk(total_size);
    if(current == (void*) -1){
        pthread_mutex_unlock(&global_malloc_lock);
        return NULL; // sbrk failed
    }
    current->s.size = size;
    current->s.is_free = 0;
    current->s.next = NULL;

    if(head == NULL){
        head = tail = current;
    } 
    else{
        tail->s.next = current;
        tail = current;
    }
    pthread_mutex_unlock(&global_malloc_lock);
    return (void*)(current + 1); // return pointer to memory after header
}

void mem_free(void* block){
    if(!block){
        return;
    }
    pthread_mutex_lock(&global_malloc_lock);
    header_t* header = (header_t*)block - 1;

    void* program_break = sbrk(0);// the last address of the heap
    if((char*)block + header->s.size == (char*)program_break){
        if(head == tail){
            head = tail = NULL;
        } 
        else{
            header_t* current = head;
            while(current){
                if(current->s.next == tail){
                    tail = current;
                    tail->s.next = NULL;
                    break;
                }
                current = current->s.next;
            }
        }
        sbrk(0 - (sizeof(header_t) + header->s.size));
        pthread_mutex_unlock(&global_malloc_lock);
        return;
    }

    header->s.is_free = 1;
    pthread_mutex_unlock(&global_malloc_lock);
}

void* mem_calloc(size_t num, size_t nsize){
    if(num == 0 || nsize == 0){
        return NULL;
    }
    size_t total_size = num * nsize;
    if(nsize != total_size / num){ // check for overflow
        return NULL;
    }
    void* block = mem_malloc(total_size);
    if(!block){
        return NULL;
    }
    memset(block, 0, total_size);
    return block;
}

void* mem_realloc(void* block, size_t size){
    if(!block || size == 0){
        return mem_malloc(size);
    }
    header_t* header = (header_t*)block - 1;
    if(header->s.size >= size){
        return block;
    }
    void* new_block = mem_malloc(size);
    if(!new_block){
        return NULL;
    }
    memcpy(new_block, block, header->s.size);
    mem_free(block);
    return new_block;
}

