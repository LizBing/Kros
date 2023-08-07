#ifndef MEMORY_ARENA_
#define MEMORY_ARENA_

#include "memory/allocation.hpp"
#include "util/align.h"
#include "util/globals.h"
#include "util/int.h"
#include "util/macros.h"
#include "runtime/debug.h"

class Chunk {
    friend class Arena;
    friend class ChunkPool;
public:
    enum {
        // refers to HotSpot
        slack = LP64_ONLY(40) NOT_LP64(20),

        tinySize = 256 - slack,
        initSize = 1 * K - slack,
        mediumSize = 8 * K - slack,
        size = 32 * K - slack,
        nonSize = initSize + 32
    };

private:
    Chunk* next;
    size_t len;
    char space[0];

public:
    Chunk(size_t length)
    : len(length), next(NULL) {}
};

class Arena : CHeapObj {
public:
    static const size_t alignment = 8;
public:
    Arena(size_t = Chunk::initSize);

    void* allocate(size_t s) {
        s = align_up(s, alignment);
        
        auto newTop = top + s;
        if(newTop >= max)
            return grow(s);

        auto ret_val = top;
        top = newTop;
        return ret_val;
    }

    void release(void* p, size_t s) {
        if((char*)p + s == top)
            top = (char*)p;
    }

private:
    void* grow(size_t s); 

    char* top, *max;
    Chunk* cur, *first;
};


#endif