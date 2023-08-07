#ifndef MEMORY_ALLOCATION_
#define MEMORY_ALLOCATION_

#include <new>
#include "runtime/os.hpp"
#include "memory/allStatic.hpp"

// using malloc/free
class CHeapObj {
public:
    void* operator new(size_t s) noexcept { 
        auto ret_val = os::malloc(s);
        if(!ret_val)
            return NULL;

        return ret_val;
    }

    void* operator new[](size_t s) noexcept { return operator new(s); }

    void operator delete(void* p) { os::free(p); } 

    void operator delete[](void* p) { operator delete(p); }

    static void* reallocate(void* old, size_t s) { return os::realloc(old, s); }
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
    void operator delete(void*);
    void operator delete[](void*);
};

struct StackObj {
    void* operator new(size_t) = delete;
    void* operator new[](size_t) = delete;
    void operator delete(void*) = delete;
    void operator delete[](void*) = delete;
};

#endif