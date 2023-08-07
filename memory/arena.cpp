#include "arena.hpp"
#include "memory/allocation.hpp"
#include "runtime/threadCritical.hpp"

class ChunkPool : CHeapObj {
public:
    static ChunkPool 
        *tinyPool,
        *initPool,
        *mediumPool,
        *normalPool;

    static void initialize() {
        tinyPool = new ChunkPool(Chunk::tinySize);
        initPool = new ChunkPool(Chunk::initSize);
        mediumPool = new ChunkPool(Chunk::mediumSize);
        normalPool = new ChunkPool(Chunk::size);
    }

public:
    ChunkPool(size_t s)
    : size(s), top(NULL) {}

    Chunk* allocate() {
        ThreadCritical tc;

        auto ret_val = top;
        if(top) {
            top = top->next;
            return ret_val;
        }

        ret_val = (Chunk*)operator new(sizeof(Chunk) + size);
        assert(ret_val, "out of memory(c heap)");

        return new(ret_val) Chunk(size);
    }

    void release(Chunk* c) {
        ThreadCritical tc;

        c->next = top;
        top = c;
    }

private:
    size_t size;
    Chunk* top;
};

Arena::Arena(size_t initSize) { grow(initSize); }

void* Arena::grow(size_t s) {
    Chunk* c;

    switch (s) {
    case Chunk::tinySize: c = ChunkPool::tinyPool->allocate(); break;
    case Chunk::initSize: c = ChunkPool::initPool->allocate(); break;
    case Chunk::mediumSize: c = ChunkPool::mediumPool->allocate(); break;
    case Chunk::size: c = ChunkPool::normalPool->allocate(); break;

    default:
        void* p = operator new(sizeof(Chunk) + s);
        assert(p, "out of memory(c heap)");

        c = new(p) Chunk(s);
    }

    max = c->space + c->len;

    if(cur) {
        top = c->space + s;
        cur->next = c;
        cur = c;
    } else {
        top = c->space;
        first = cur = c;
    }
    return c->space;
}