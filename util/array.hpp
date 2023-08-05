#ifndef UTIL_ARRAY_
#define UTIL_ARRAY_

#include "memory/allocation.hpp"
#include "util/debug.h"
#include "util/align.h"

template<class T>
class Array : CHeapObj {
    static const size_t capacityAlignment = 128;

    static size_t computeCapacity(size_t c) { return align_up(c, capacityAlignment); }

public:
    Array(size_t len = 128) 
    : _capacity(computeCapacity(len)) {
        data = new T[len];
        if(!data)
            panic("out of memory(c heap).");
    }

    size_t capacity() { return _capacity; }

    void resize(size_t len) {
        _capacity = computeCapacity(len);

        data = reallocate(data, capacity());
        if(!data)
            panic("out of memory(c heap).");
    }

    T* at(long index) { return data + index; }

private:
    T* data;
    size_t _capacity;
};


#endif