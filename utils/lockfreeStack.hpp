#ifndef UTILS_LOCKFREESTACK_
#define UTILS_LOCKFREESTACK_

#include "runtime/atomic.hpp"
#include "memory/iterator.hpp"

class LockFreeStackNode {
    friend class LockFreeStack;

    LockFreeStackNode* next;
};

struct LockFreeStackClosure : public Closure {
    virtual bool func(LockFreeStackNode*) = 0;
};

class LockFreeStack {
public:
    LockFreeStack()
    : top(nullptr) {}

    void push(LockFreeStackNode* n) {
        LockFreeStackNode* oldTop;
        do {
            oldTop = Atomic::load(&top);
            n->next = oldTop;
        } while(Atomic::cmpxchg_weak(&top, oldTop, n) != oldTop);
    }

    LockFreeStackNode* pop() {
        LockFreeStackNode* n, *newTop;
        do {
            n = Atomic::load(&top);
            if(!n)
                return nullptr;

            newTop = n->next;
        } while(Atomic::cmpxchg_weak(&top, n, newTop) != n);

        return n;
    }

    bool empty() { return !Atomic::load(&top); }

    void forEach(LockFreeStackClosure* cl) {
        using iterator = LockFreeStackNode*;

        for(iterator iter = Atomic::load(&top); iter; iter = iter->next)
            if(!cl->func(iter))
                return;
    }

private:
    LockFreeStackNode* top;
};

#endif
