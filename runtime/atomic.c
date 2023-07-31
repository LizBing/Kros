#include "runtime/atomic.h"
#include <stdatomic.h>

inline Any Atomic_load(Any* volatile n) { return atomic_load((atomic_llong*)n); }
inline void Atomic_store(Any* volatile n, Any v) { atomic_store((atomic_llong*)n, v); }

inline Any Atomic_fetchAdd(Any* volatile n, Any v) { return atomic_fetch_add((atomic_llong*)n, v); }
inline Any Atomic_fetchSub(Any* volatile n, Any v) { return atomic_fetch_sub((atomic_llong*)n, v); }
inline Any Atomic_fetchOr(Any* volatile n, Any v) { return atomic_fetch_or((atomic_llong*)n, v); }
inline Any Atomic_fetchAnd(Any* volatile n, Any v) { return atomic_fetch_and((atomic_llong*)n, v); }
inline Any Atomic_fetchXor(Any* volatile n, Any v) { return atomic_fetch_xor((atomic_llong*)n, v); }

inline Any Atomic_xchg(Any* volatile n, Any v) { return atomic_exchange((atomic_llong*)n, v); }
inline Any Atomic_cmpxchg(Any* volatile n, Any exp, Any des) {
    Any tmp = exp;

    if(atomic_compare_exchange_strong((atomic_llong*)n, &exp, des))
        return tmp;
    return exp;
}

