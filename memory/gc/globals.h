#ifndef MEMORY_GC_BASE_GLOBALS_
#define MEMORY_GC_BASE_GLOBALS_

#include "runtime/vmFlag/vmFlag.hpp"

#define GC_FLAGS(f) \
    f(int, parallelThreads, 1, "the number of parallel GC workers.") \
    f(int, concurrentThreads, 1, "the number of concurrent GC workers. ") \


#define TLAB_FLAGS(f) \
    f(bool, useTLAB, true, "use thread local allocation buffer.") \
    f(bool, resizeTLAB, true, "enable the resizability of TLAB") \
    f(size_t, TLABSize, 4 * K, "the initial size of TLAB") \


GC_FLAGS(DECLARE_VMFLAG);
TLAB_FLAGS(DECLARE_VMFLAG);

#endif