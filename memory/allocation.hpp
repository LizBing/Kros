#ifndef MEMORY_ALLOCATION_
#define MEMORY_ALLOCATION_

#include <new>
#include <cstdlib>

#include "memory/allStatic.hpp"

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

    void* operator new[](size_t s) noexcept { return operator new(s); }

    void operator delete(void* p) { free(p); } 

    void operator delete[](void* p) { free(p); }

    static void initialize() { _allocated = 0; }

    static size_t allocated() { return _allocated; }

    template<class T>
    static T* reallocate(T* old, size_t s) { return realloc(old, s); }
    
private:
    static size_t _allocated;
};

class MetaSpaceObj {
public:
    void* operator new(size_t) noexcept;
    void* operator new[](size_t) noexcept;
    void operator delete(void*);
    void operator delete[](void*);
};

class ResourceObj {
public:
    void* operator new(size_t) noexcept;
    void* operator new[](size_t) noexcept;
    void operator delete(void*) {}
    void operator delete[](void*) {}
};

struct StackObj {
    void* operator new(size_t) = delete;
    void* operator new[](size_t) = delete;
    void operator delete(void*) = delete;
    void operator delete[](void*) = delete;
};

#endif