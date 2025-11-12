#define MEMALLOC_H
#ifdef MEMALLOC_H

#include <stdio.h>

struct header_t{
    size_t size;
    unsigned is_free;
    struct header_t* next;
};



#endif