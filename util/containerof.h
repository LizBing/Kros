#ifndef UTIL_CONTAINEROF_
#define UTIL_CONTAINEROF_

#include "util/int.h"

#define containerof(ptr, type, member) \
    ((type*)((intptr_t)ptr - (off_t)((type*)0)->member))

#endif
