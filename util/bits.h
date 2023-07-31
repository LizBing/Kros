#ifndef UTIL_BITS_
#define UTIL_BITS_

#include "util/int.h"

#define Bits_right_n(bits) ((1ull << bits) - 1)
#define Bits_mask(bits, shift) (Bits_right_n(bits) << shift)

#define Bits_1stField(name, seek, bits) \
    static const int name##_shift = 0 + seek; \
    static const int name##_bits = bits

#define Bits_field(name, prev_name, seek, bits) \
    static const int name##_shift = prev_name##_shift + prev_name##_bits + seek; \
    static const int name##_bits = bits; \
    static const uint64_t name##_mask = Bits_mask(bits, name##_shift)

#define Bits_get(n, fn) do ((n & fn##_mask) >> fn##_shift) while(0)
#define Bits_put(n, fn, v) do (n & ~fn##_mask) | v << fn##_shift); while(0)

#endif
