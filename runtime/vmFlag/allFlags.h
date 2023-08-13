#ifndef RUNTIME_VMFLAG_ALLFLAGS_
#define RUNTIME_VMFLAG_ALLFLAGS_

#include "memory/gc/globals.h"
#include "runtime/globals.h"

#define ALLFLAGS(f) \
    GC_FLAGS(f) \
    TLAB_FLAGS(f) \
    RUNTIME_FLAGS(f) 



#endif