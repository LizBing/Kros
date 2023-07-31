#ifndef UTIL_LOCKFREESTACK_
#define UTIL_LOCKFREESTACK_

#include "runtime/atomic.h"
#include "util/bool.h"
#include "util/closure.h"

typedef struct LockFreeStackNode LockFreeStackNode;
struct LockFreeStackNode {
    Any next;
};

typedef struct {
    Any top;    // in order to support 32 bits atomic operation
} LockFreeStack;

static inline void LockFreeStack_ctor(LockFreeStack* this) { this->top = null; }

static inline void LockFreeStack_push(LockFreeStack* this, LockFreeStackNode* n) {
    Any next, tmp = Atomic_load(&this->top);;
    do {
        next = tmp;
        n->next = next;
        tmp = Atomic_cmpxchg(&this->top, tmp, (Any)n);
    } while(tmp != next);
}

static inline LockFreeStackNode* LockFreeStack_pop(LockFreeStack* this) {
    Any newTop, tmp = Atomic_load(&this->top);
    LockFreeStackNode* n;

    do {
        n = (void*)tmp;
        if(!n)
            return NULL;

        newTop = n->next;
        tmp = Atomic_cmpxchg(&this->top, tmp, newTop);
    } while(tmp != (Any)n);

    return n;
}

static inline bool LockFreeStack_empty(LockFreeStack* this) {
    return !Atomic_load(&this->top);
}

static inline bool LockFreeStack_iterate(LockFreeStack* this, Closure cl) {
    for(LockFreeStackNode* iter = (void*)Atomic_load(&this->top); iter; iter = (void*)iter->next) 
        if(!Closure_do(cl, iter))
            return false;
    return true;
}


#endif
