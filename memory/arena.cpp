#include "arena.hpp"
#include "memory/allocation.hpp"
#include "runtime/threadCritical.hpp"

class ChunkPool : public CHeapObj {
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

    static ChunkPool* select(size_t s) {
        switch (s) {
        case Chunk::tinySize: return ChunkPool::tinyPool; 
        case Chunk::initSize: return ChunkPool::initPool; 
        case Chunk::mediumSize: return ChunkPool::mediumPool; 
        case Chunk::size: return ChunkPool::normalPool; 

        default:
            return NULL;
        }
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

void* Arena::grow(size_t s) {
    Chunk* c;
    auto cp = ChunkPool::select(s);
    if(cp)
        c = cp->allocate();
    else {
        auto p = operator new(sizeof(Chunk) + s);
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

void Chunk::operator delete(void* p) {
    auto c = (Chunk*)p;
    auto cp = ChunkPool::select(c->len);

    if(cp)
        cp->release(c);
    else
        ChunkPool::operator delete(c);
}