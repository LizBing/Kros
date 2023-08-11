#ifndef MEMORY_VIRTUALSPACE_
#define MEMORY_VIRTUALSPACE_

#include "memory/physicalSpace.hpp"
#include "utils/int.h"
#include "utils/align.h"

class VirtualSpace {
public:
    static void* map(void*, Partition);
    static void* map(Partition, bool executable = false);
    static void unmap(void*, size_t);

public:
    VirtualSpace(void* start, size_t initSize, size_t alignment, size_t maxCapacity)
    : _start((char*)start), _alignment(alignment), _maxCapacity(maxCapacity) {
        _capacity = align_up(initSize, alignment);
    }

    void* start() { return _start; }
    void* end() { return _start + _capacity; }
    size_t capacity() { return _capacity; }
    size_t maxCapacity() { return _maxCapacity; }
    bool contains(void* p) { return p >= start() && p < end(); }

    void* expand(size_t s) {
        auto tmp = _capacity + s;
        if(tmp > _maxCapacity)
            return NULL;

        auto ret_val = _start + _capacity;
        _capacity = tmp;
        return ret_val;
    }

private:
    char* _start;
    size_t _capacity, _alignment, _maxCapacity;
};


#endif