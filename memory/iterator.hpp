#ifndef MEMORY_ITERATOR_
#define MEMORY_ITERATOR_

#include "allocation.hpp"

class Thread;
typedef class OopDesc* oop;

class Closure : public StackObj {};

struct ObjectClosure : Closure {
    virtual void do_object(oop) = 0; 
};

#endif