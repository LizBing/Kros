#ifndef MEMORY_VIRTUALSPACE_
#define MEMORY_VIRTUALSPACE_

#include "util/int.h"
#include "util/align.h"

class VirtualSpace {
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

    bool expand(size_t s) {
        auto tmp = _capacity + s;
        if(tmp > _maxCapacity)
            return false;

        _capacity = tmp;
        return true;
    }

private:
    char* _start;
    size_t _capacity, _alignment, _maxCapacity;
};


#endif