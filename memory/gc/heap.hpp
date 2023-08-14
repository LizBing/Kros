#ifndef MEMORY_GC_HEAP_
#define MEMORY_GC_HEAP_

#include "memory/memRegion.hpp"
#include "utils/int.h"
#include "memory/iterator.hpp"

class GCHeap {
private:
    uint32_t _totalCollections, _totalFullCollections;

protected:
    virtual void* alloc_tlab(size_t) = 0;
    virtual void* mem_alloc(size_t) = 0;

    void resizeAllTLABs();
    
public:
    virtual size_t minDummySize();
    void fillWithDummy(MemRegion);

    uint32_t totalCollections() { return _totalCollections; }
    uint32_t totalFullCollections() { return _totalFullCollections; }
    void incrTotalCollections();
    void incrTotalFullCollections();

    virtual bool is_oop(oop);

public:
    virtual const char* name() const = 0;

    virtual size_t capacity() = 0;
    virtual size_t used() = 0;
    virtual size_t unused() { return capacity() - used(); } 

    virtual size_t max_tlab() const = 0;

    virtual size_t max_capacity() const = 0;

    virtual bool stackWatermarkSupported() const { return false; }

    virtual void makeParsable(bool retireTLABs);

    virtual void doMinorGC(const char* cause) = 0;
    virtual void doFullGC(const char* cause) = 0;

    virtual void object_iterate(ObjectClosure*) = 0;

};

#endif