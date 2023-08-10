#ifndef OOPS_TYPE_
#define OOPS_TYPE_

#include "memory/iterator.hpp"
#include "util/int.h"
#include "util/macros.h"

typedef struct TypeDesc {
    virtual bool protoType() const = 0;
    virtual bool arrayType() const = 0;

    virtual size_t protoTypeFieldSize() = 0;
    virtual size_t oopFieldSize() = 0;
    LP64_ONLY(size_t compressedOopFieldSize() { return oopFieldSize() / 2; })
    
    virtual OopGraph2OopClosure* new_og2cl(OopClosure*) = 0;
    virtual void oopGraph_iterate(OopGraphClosure*) = 0;
}* Type;

#endif