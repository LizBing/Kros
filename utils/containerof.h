#ifndef UTILS_CONTAINEROF_
#define UTILS_CONTAINEROF_

#include "int.hpp"

// Linux-style generic programming
#define containerof(ptr, type, member) \
    ((type*)((intptr_t)ptr - (intptr_t)&((type*)0)->member))

#endif