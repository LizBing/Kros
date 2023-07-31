#ifndef UTIL_CLOSURE_
#define UTIL_CLOSURE_

#include "util/bool.h"

typedef struct {
    bool(*func)(void* this, void* arg);
    void* arg;
} Closure;

static inline bool Closure_do(Closure cl, void* this) { return cl.func(this, cl.arg); }

#endif
