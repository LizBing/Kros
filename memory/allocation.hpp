#ifndef MEMORY_ALLOCATION_
#define MEMORY_ALLOCATION_

#include <new>
#include "runtime/os.hpp"
#include "memory/allStatic.hpp"

class Arena;

// using malloc/free
struct CHeapObj {
    void* operator new(size_t s) noexcept; 
    void* operator new[](size_t s) noexcept { return operator new(s); }
    void operator delete(void* p);  
    void operator delete[](void* p) { operator delete(p); }

    static void* reallocate(void* old, size_t s); 
};

struct MetaSpaceObj {
    void* operator new(size_t) noexcept;
    void* operator new[](size_t) noexcept;
    void operator delete(void*);
    void operator delete[](void*);
};

struct ResourceObj {
    enum AllocationType {
        CHEAP,
        ARENA,
    };

    void* operator new(size_t, AllocationType) noexcept;
    void* operator new[](size_t s, AllocationType t) noexcept { return operator new(s, t); }

    void* operator new(size_t, Arena* ) noexcept; 
    void* operator new[](size_t s, Arena* a) noexcept { return operator new(s, a); }

    void operator delete(void*);
    void operator delete[](void* p) { operator delete(p); }
};

struct StackObj {
    void* operator new(size_t) = delete;
    void* operator new[](size_t) = delete;
    void operator delete(void*) = delete;
    void operator delete[](void*) = delete;
};

#endif