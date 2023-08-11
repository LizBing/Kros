#ifndef MEMORY_ARENA_
#define MEMORY_ARENA_

#include "memory/allocation.hpp"
#include "utils/align.h"
#include "utils/globals.h"
#include "utils/int.h"
#include "utils/macros.h"
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

private:
    void operator delete(void* p);

public:
    Chunk(size_t length)
    : len(length), next(NULL) {}


    void chop() {
        auto iter = this;
        while(iter) {
            auto next = iter->next;
            delete iter;
            iter = next;
        }
    }

    void chopFollowings() {
        if(next)
            next->chop();
    }
};

class Arena : CHeapObj {
public:
    static const size_t alignment = 8;
public:
    Arena(size_t initSize = Chunk::initSize) { grow(initSize); }
    ~Arena() { first->chop(); }

    // no need to check if the return value equals null
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

public:
    class SavedStates {
        friend class Arena;

        char* top, *max;
        Chunk* cur, *first;

    public:
        SavedStates(Arena* a) {
            top = a->top;
            max = a->max;
            cur = a->cur;
            first = a->first;
        }
    };

    void rollback(SavedStates* s) {
        top = s->top;
        max = s->max;
        cur = s->cur;
        first = s->first;

        if(cur)
            cur->chopFollowings();
    }

private:
    void* grow(size_t s); 

    char* top, *max;
    Chunk* cur, *first;
};

class ResourceMark {
public:
    ResourceMark(Arena* _arena)
    : arena(_arena), ss(_arena) {} 

    ~ResourceMark() {
        arena->rollback(&ss);
    }

private:
    Arena::SavedStates ss;
    Arena* arena;
};

#endif