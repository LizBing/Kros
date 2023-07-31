#ifndef MEMORY_ALLOCATION_
#define MEMORY_ALLOCATION_

#include "util/int.h"

void* CHeap_alloc(size_t);
void* CHeap_realloc(void*, size_t);
void CHeap_free(void*);

#endif
