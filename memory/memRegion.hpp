#ifndef MEMORY_MEMREGION_
#define MEMORY_MEMREGION_

#include "util/int.h"
#include "allocation.hpp"

class MemRegion : CHeapObj {
public:
    MemRegion()
    : start(NULL), size(0) {}

    MemRegion(intptr_t _start, size_t _size)
    : start(_start), size(_size) {}

    MemRegion(intptr_t _start, intptr_t end)
    : start(_start), size(end - _start) {}

    bool empty() { return !size; }

    intptr_t end() { return start + size; }

    bool contains(MemRegion mr) {
        return (empty() && mr.empty()) || (mr.start >= start && mr.end() <= end());
    }

    bool contains(void* p) {
        auto _p = (intptr_t)p;
        return _p >= start && _p < end();
    }

    MemRegion* createArray(long length) {
        auto arr = new MemRegion[length];
        size_t unit = size / length;

        for(int i = 0; i < length; ++i)
            arr[i] = MemRegion(start + unit * i, unit);

        return arr;
    }

    intptr_t start;
    size_t size;
};


#endif