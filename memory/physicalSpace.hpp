#ifndef MEMORY_PHYSICALSPACE_
#define MEMORY_PHYSICALSPACE_

#include "allocation.hpp"
#include "runtime/debug.h"
#include "util/int.h"
#include "util/linkedList.hpp"

class Partition;

// implementing using os::open_shm & os::close_shm
class PhysicalSpace : CHeapObj {
private:
    static PhysicalSpace* head;

public:
    static void initialize() { head = NULL; }

    // delete all physical spaces when vm exits
    static PhysicalSpace* pop() {
        if(head) {
            auto ret_val = head;
            head = head->next;
            return ret_val;
        }

        return NULL;
    }

    static PhysicalSpace* create(size_t size, size_t alignment = 8) {
        auto ret_val = new PhysicalSpace(size, alignment);
        assert(ret_val, "out of memory");

        push(ret_val);

        return ret_val;
    }

private:
    PhysicalSpace(size_t size, size_t alignment);

    static void push(PhysicalSpace* ps) {
        ps->next = head;
        head = ps;
    }

    ~PhysicalSpace();

public:
    size_t size() { return _size; }

private:
    const char* name;
    int fd;
    size_t _size;

    PhysicalSpace* next;
};

class Partition {
public:
    Partition(PhysicalSpace* _ps, size_t size, off_t off = 0);
    Partition(size_t size);     // anonymous physical memory allocation
    
    PhysicalSpace* physicalSpace() { return ps; }
    size_t size() { return _size; }
    off_t offset() { return off; }

    bool mount(void*, bool executable);

    // make managable
    // only be mounted at one virtual space at the same time
    LinkedListNode node;

private:
    PhysicalSpace* ps;
    size_t _size;
    off_t off;
};


#endif