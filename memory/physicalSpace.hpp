#ifndef MEMORY_PHYSICALSPACE_
#define MEMORY_PHYSICALSPACE_

#include "allocation.hpp"
#include "util/int.h"

class Partition;

// implementing using os::open_shm & os::close_shm
class PhysicalSpace : CHeapObj {
public:
    PhysicalSpace(size_t size, size_t alignment = 0);
    ~PhysicalSpace();

    size_t size() { return _size; }

private:
    const char* name;
    int fd;
    size_t _size;
};

class Partition {
public:
    Partition(PhysicalSpace* _ps, size_t size, off_t off = 0);
    
    PhysicalSpace* physicalSpace() { return ps; }
    size_t size() { return _size; }
    off_t offset() { return off; }

    bool mount(void*, bool executable);
    void unmout();

private:
    PhysicalSpace* ps;
    size_t _size;
    off_t off;
};


#endif