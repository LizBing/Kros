#ifndef MEMORY_GC_BASE_GLOBALS_
#define MEMORY_GC_BASE_GLOBALS_

#include "runtime/vmFlag/vmFlag.hpp"

#define GC_FLAGS(f) \


#define TLAB_FLAGS(f) \


GC_FLAGS(DECLARE_VMFLAG);
TLAB_FLAGS(DECLARE_VMFLAG);

#endif