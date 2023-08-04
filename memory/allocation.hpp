#ifndef MEMORY_ALLOCATION_
#define MEMORY_ALLOCATION_

#include <new>
#include <cstdlib>

#include "util/allStatic.hpp"

// using malloc/free
class CHeapObj {
public:
    void* operator new(size_t s) noexcept { 
        auto ret_val = malloc(s);
        if(!ret_val)
            return NULL;

        _allocated += s;
        return ret_val;
    }

    void* operator new[](size_t s) noexcept {
        return operator new(s);
    }

    void operator delete(void* p) { free(p); } 

    void operator delete[](void* p) { free(p); }

    static void initialize() { _allocated = 0; }

    static size_t allocated() { return _allocated; }
    
private:
    static size_t _allocated;
};

class MetaSpaceObj {};

class ResourceObj {};

class StackObj {};

#endif