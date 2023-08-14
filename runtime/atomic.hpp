#ifndef RUNTIME_ATOMIC_
#define RUNTIME_ATOMIC_

#include "memory/allStatic.hpp"

// using the same memory orders as C11
struct Atomic : AllStatic {
    template<class T>
    static T load(T volatile* p, memory_order order = memory_order_seq_cst) { 
        return atomic_load_explicit((T _Atomic*)p, order); 
    }

    template<class T, class U>
    static void store(T volatile* p, U des, memory_order order = memory_order_seq_cst) {
        atomic_store_explicit((T _Atomic*)p, des, order);
    }

    template<class T, class U>
    static T fetchAndAdd(T volatile* p, U n, memory_order order = memory_order_seq_cst) {
        return atomic_fetch_add_explicit((T _Atomic*)p, n, order);
    }

    template<class T>
    static void inc(T volatile* p, memory_order order = memory_order_seq_cst) {
        fetchAndAdd(p, 1, order);
    }

    template<class T>
    static void dec(T volatile* p, memory_order order = memory_order_seq_cst) {
        fetchAndAdd(p, -1, order);
    }

    template<class T, class U>
    static T xchg(T volatile* p, U des, memory_order order = memory_order_seq_cst) {
        return atomic_exchange_explicit((T _Atomic*)p, des, order);
    }

    template<class T, class U, class V>
    static T cmpxchg_strong(T volatile* p, U exp, V des, memory_order order = memory_order_seq_cst) {
        T ret_val = exp;
        atomic_compare_exchange_strong_explicit((T _Atomic*)p, &ret_val, des);
        return ret_val;
    }
    
    template<class T, class U, class V>
    static T cmpxchg_weak(T volatile* p, U exp, V des, memory_order order = memory_order_seq_cst) {
        T ret_val = exp;
        atomic_compare_exchange_weak_explicit((T _Atomic*)p, &ret_val, des);
        return ret_val;
    }
};

#endif