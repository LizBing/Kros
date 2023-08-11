#include "oop.hpp"
#include "type.hpp"
#include "utils/globals.h"

char* OopDesc::actualBase() {
    if(type()->arrayType())
        return base + bytesPerWord;
    return base;
}