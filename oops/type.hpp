#ifndef OOPS_TYPE_
#define OOPS_TYPE_

#include "memory/iterator.hpp"
#include "util/int.h"

typedef struct TypeDesc {
    virtual bool protoType() const = 0;
    virtual bool arrayType() const = 0;
    virtual size_t size() = 0;
    
    virtual OopGraph2OopClosure* new_og2cl() = 0;
    virtual void oopGraph_iterate(OopGraphClosure*) = 0;
}* Type;

#endif