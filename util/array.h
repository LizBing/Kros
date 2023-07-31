#ifndef UTIL_ARRAY_
#define UTIL_ARRAY_

#include "bool.h"
#include "util/int.h"

typedef struct {
    void* data;
    size_t capacity, unit;
} Array;

void Array_ctor(Array*, size_t unit, size_t capacity);
void Array_dtor(Array*);

static inline void* Array_at(Array* this, uint64_t index) {
    if(index < this->capacity)
        return this->data + this->unit * index;
    return NULL;
}

bool Array_resize(Array*, size_t);


#endif
