#ifndef MEMORY_ITERATOR_
#define MEMORY_ITERATOR_

#include "allocation.hpp"

class Thread;
typedef class OopDesc* oop;

class Closure : StackObj {};

struct ObjectClosure : Closure {
    virtual void do_object(oop) = 0; 
};

struct OopClosure : Closure {
    virtual void do_oop(oop) = 0;
};

struct OopGraphClosure : Closure {
    virtual void walkGraph(off_t) = 0;
};

class OopGraph2OopClosure : OopGraphClosure {
public:
    OopGraph2OopClosure(oop _p, OopClosure* _cl)
    : cl(_cl), p(_p) {}

    void walkGraph(off_t off); 

private:
    OopClosure* cl;
    oop p;
};

#endif