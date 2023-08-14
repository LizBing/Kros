#ifndef RUNTIME_ATOMIC_
#define RUNTIME_ATOMIC_

#include "memory/allStatic.hpp"
#include <atomic>
#include <stdatomic.h>

// using the same memory orders as C11
struct Atomic : AllStatic {
    enum MemoryOrder {
        relaxed,
        consume,
        acquire,
        release,
        acq_rel,
        seq_cst,
    };

    template<class T>
    static T load(T volatile* p, MemoryOrder order = seq_cst); 

    template<class T, class U>
    static void store(T volatile* p, U des, MemoryOrder order = seq_cst); 

    template<class T, class U>
    static T fetchAndAdd(T volatile* p, U n, MemoryOrder order = seq_cst); 

    template<class T>
    static void inc(T volatile* p, MemoryOrder order = seq_cst) { fetchAndAdd(p, 1, order); }

    template<class T>
    static void dec(T volatile* p, MemoryOrder order = seq_cst) { fetchAndAdd(p, -1, order); }

    template<class T, class U>
    static T xchg(T volatile* p, U des, MemoryOrder order = seq_cst); 

    template<class T, class U, class V>
    static T cmpxchg_strong(T volatile* p, U exp, V des, MemoryOrder order = seq_cst); 
    
    template<class T, class U, class V>
    static T cmpxchg_weak(T volatile* p, U exp, V des, MemoryOrder order = seq_cst); 
};

#endif