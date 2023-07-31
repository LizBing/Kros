#ifndef RUNTIME_ATOMIC_
#define RUNTIME_ATOMIC_

#include "util/any.h"

inline Any Atomic_load(Any* volatile);
inline void Atomic_store(Any* volatile, Any);

inline Any Atomic_fetchAdd(Any* volatile, Any);
inline Any Atomic_fetchSub(Any* volatile, Any);
inline Any Atomic_fetchAnd(Any* volatile, Any);
inline Any Atomic_fetchOr(Any* volatile, Any);
inline Any Atomic_fetchXor(Any* volatile, Any);

inline Any Atomic_inc(Any* volatile);

inline Any Atomic_xchg(Any* volatile, Any);
inline Any Atomic_cmpxchg(Any* volatile, Any exp, Any des);

#endif
