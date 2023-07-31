#include "runtime/atomic.h"
#include <stdatomic.h>

Any Atomic_load(Any* volatile n) { return atomic_load((atomic_long*)n); }
void Atomic_store(Any* volatile n, Any v) { atomic_store((atomic_long*)n, v); }

Any Atomic_fetchAdd(Any* volatile n, Any v) { return atomic_fetch_add((atomic_long*)n, v); }
Any Atomic_fetchSub(Any* volatile n, Any v) { return atomic_fetch_sub((atomic_long*)n, v); }
Any Atomic_fetchOr(Any* volatile n, Any v) { return atomic_fetch_or((atomic_long*)n, v); }
Any Atomic_fetchAnd(Any* volatile n, Any v) { return atomic_fetch_and((atomic_long*)n, v); }
Any Atomic_fetchXor(Any* volatile n, Any v) { return atomic_fetch_xor((atomic_long*)n, v); }

Any Atomic_xchg(Any* volatile n, Any v) { return atomic_exchange((atomic_long*)n, v); }
Any Atomic_cmpxchg(Any* volatile n, Any exp, Any des) {
    Any tmp = exp;

    if(atomic_compare_exchange((atomic_long*)n, &exp, des))
        return tmp;
    return exp;
}

