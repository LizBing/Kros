#ifndef RUNTIME_GLOBALS_
#define RUNTIME_GLOBALS_

#include "utils/int.h"
#include "vmFlag/vmFlag.hpp"

#define RUNTIME_FLAGS(f) \
    f(bool, enableCompressedPointer, true, "") \
    f(size_t, nativeStackSize, 1 * M, "") \

RUNTIME_FLAGS(DECLARE_VMFLAG);

#endif