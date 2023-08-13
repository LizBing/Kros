#ifndef OOPS_TYPEDESC_
#define OOPS_TYPEDESC_

#include "memory/iterator.hpp"
#include "runtime/globals.h"
#include "utils/globals.h"
#include "utils/int.h"
#include "utils/macros.h"

struct TypeDesc {
    virtual bool protoType() const = 0;
    virtual bool arrayType() const = 0;

    virtual size_t protoTypeFieldsSize() = 0;
    virtual size_t oopFields() = 0;
    size_t size() {
        size_t oopFieldsSize;
        if(enableCompressedPointer)
            oopFieldsSize = oopFields() << logBitsPerInt;
        else
            oopFieldsSize = oopFields() << logBitsPerWord;

        return oopFieldsSize + protoTypeFieldsSize();
    }
    
    virtual void oopGraph_iterate(OopGraphClosure*) = 0;
};

#endif