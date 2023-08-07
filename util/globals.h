#ifndef UTIL_GLOBALS_
#define UTIL_GLOBALS_

#include "int.h"

#ifdef _LP64
static const int logBytesPerWord = 3;
#else
static const int logBytesPerWord = 2;
#endif

static const int logBitsPerByte = 3;
static const int logBitsPerWord = logBitsPerByte + logBytesPerWord;

static const int bitsPerByte = 1 << logBitsPerByte;
static const int bitsPerWord = 1 << logBitsPerWord;

static const size_t K = 1024;
static const size_t M = K * 1024;
static const size_t G = M * 1024;

template<class T>
constexpr T min2(T x, T y) { return x > y ? y : x; }

template<class T>
constexpr T max2(T x, T y) { return x > y ? x : y; }

#define oneBit ((uintptr_t)1)
#define nth_bit(n) (oneBit << (n))
#define right_nBits(s) (nth_bit(s) - 1)

inline void setBits(uintptr_t& n, uintptr_t m) { n |= m; }
inline void resetBits(uintptr_t& n, uintptr_t m) { n &= ~m; }
inline uintptr_t maskBits(uintptr_t n, uintptr_t m) { return n & m; }

inline bool areMaskBitsSet(uintptr_t n, uintptr_t m) { return maskBits(m, n) == m; }
inline bool isNthBitSet(uintptr_t x, int n) { return x & nth_bit(n); }

#endif