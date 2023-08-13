#include "oop.hpp"
#include "memory/iterator.hpp"
#include "type.hpp"
#include "utils/globals.h"

inline char* OopDesc::actualBase() {
    if(type()->arrayType())
        return base + bytesPerWord;
    return base;
}

inline void OopDesc::oop_iterate(OopClosure* cl) { OopGraph2OopClosure og2ocl(this, cl); }