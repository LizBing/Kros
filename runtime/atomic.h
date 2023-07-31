#ifndef RUNTIME_ATOMIC_
#define RUNTIME_ATOMIC_

#include "util/any.h"

Any Atomic_load(Any* volatile);
void Atomic_store(Any* volatile, Any);

Any Atomic_fetchAdd(Any* volatile, Any);
Any Atomic_fetchSub(Any* volatile, Any);
Any Atomic_fetchAnd(Any* volatile, Any);
Any Atomic_fetchOr(Any* volatile, Any);
Any Atomic_fetchXor(Any* volatile, Any);

Any Atomic_inc(Any* volatile);

Any Atomic_xchg(Any* volatile, Any);
Any Atomic_cmpxchg(Any* volatile, Any exp, Any des);

#endif
