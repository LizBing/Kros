#ifndef OOPS_OOP_
#define OOPS_OOP_

#include "memory/iterator.hpp"
#include "runtime/globals.hpp"
#include <sys/types.h>

using Type = class TypeDesc*;
using NarrowType = uint32_t;
using oop = class OopDesc*;
using NarrowOop = uint32_t;

class OopDesc {
private:
    union {
        struct {
            Type _type;
            volatile uintptr_t _info;
        };

        struct {
            NarrowType narrowType;
            volatile uint32_t narrowInfo;
        };
    };

public:
    template<class T>
    T fieldAddr(off_t off) { return *(T*)(actualBase() + off); }

    void oop_iterate(OopClosure*);

    char* actualBase() {
        if(enableCompressedPointer)
            return (char*)(&narrowInfo + 1);
        return (char*)(&_info + 1);
    }

    uintptr_t info() volatile {
        if(enableCompressedPointer)
            return narrowInfo;
        return _info;
    }

    void setInfo(uintptr_t n) volatile {
        if(enableCompressedPointer)
            narrowInfo = n;
        else
            _info = n;
    }

    void setInfo_par(uintptr_t n) volatile;
    uintptr_t casInfo(uintptr_t exp, uintptr_t des) volatile; 

    template<class T = TypeDesc>
    T* type(); 
};

#endif