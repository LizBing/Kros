#ifndef UTIL_STACK_
#define UTIL_STACK_

#include "array"
#include "memory/allocation.hpp"
#include "util/debug.h"

template<class T>
class StackBase {
    template<class U>
    friend class Stack;

public:
    StackBase(size_t _size)
    : top(0), size(_size), next(NULL) {}

    bool push(T n) {
        auto index = top++;
        if(top > size)
            return false;

        segment[index] = n;
        return true;
    }

    bool pop(T* p) {
        if(empty())
            return false;
        auto index = --top;
        if(p)
            *p = segment[index];
    }

    bool empty() { return !top; }

private:
    StackBase* next;

    long top;
    size_t size;

    T segment[0];
};

template<class T>
class Stack : CHeapObj {
    static const size_t defaultSegSize = 128;

public:
    Stack(size_t segSize = defaultSegSize)
    : segmentSize(segSize), cur(NULL), cache(NULL) {} 

    void push(T n) {
        if(cur && cur->push(n))
            return;
        alloc_seg();
        cur->push(n);
    }

    bool pop(T* p) {
        if(!cur)
            return false;
        if(cur->pop(p))
            return true;
        
        pushCache();
        return pop(p);
    }

    bool empty() {
        if(!cur)
            return true;
        return cur->empty();
    }

private:
    void alloc_seg() {
        auto tmp = cur;

        cur = popCache();
        if(!cur) {
            cur = operator new(sizeof(StackBase<T>) + sizeof(T) * segmentSize);
            if(!cur)
                panic("out of memory(c heap)");
        }

        cur->next = tmp;
    }

    void pushCache() {
        cur->next = cache;
        cache = cur;
    }

    StackBase<T>* popCache() {
        if(!cache)
            return NULL;

        auto ret_val = cache;
        cache = cache->next;
        return ret_val;
    }

    size_t segmentSize;
    StackBase<T>* cur, *cache;
};


#endif
