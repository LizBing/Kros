#ifndef OOPS_OOP_
#define OOPS_OOP_

#include "memory/iterator.hpp"
#include "runtime/globals.hpp"
#include "runtime/atomic.hpp"

using Type = class TypeDesc*;
using oop = class OopDesc*;

class OopDesc {
public:
    uintptr_t info;

private:
    Type _type;
    char base[0];

public:
    size_t length() { return *(size_t*)base; }
    char* actualBase(); 

    template<class T>
    T fieldAddr(off_t off) { return *(T*)(actualBase() + off); }

    void oop_iterate(OopClosure*);

    uintptr_t getInfo_par() { return Atomic::load(&info); }
    void setInfo_par(uintptr_t n) { Atomic::store(&info, n); }
    uintptr_t casInfo(uintptr_t exp, uintptr_t des) { return Atomic::cmpxchg_strong(&info, exp, des); }

    template<class T = TypeDesc>
    T* type() { return static_cast<T*>(_type); }
};

#endif