#ifndef OOPS_MARKWORD_
#define OOPS_MARKWORD_

#include "util/globals.h"
#include "util/int.h"
#include "util/macros.h"

class LangThread;
class ObjectMonitor;
class BasicLock;

// similar to HotSpot
class MarkWord {
    static const int lock_bits = 2;
    static const int biasedLock_bits = 1;
    static const int age_bits = 4;
    static const int unusedGap_bits = LP64_ONLY(1) NOT_LP64(0);
    static const int max_hashCode_bits = 
        bitsPerWord - lock_bits - biasedLock_bits - age_bits;
    static const int hashCode_bits = min2(max_hashCode_bits, 31);   // LP64: 25 bits unused
    static const int epoch_bits = 2;

    static const int lock_shift = lock_bits;
    static const int age_shift = lock_bits + biasedLock_bits;
    static const int epoch_shift = age_shift + age_bits + unusedGap_bits;
    static const int hashCode_shift = epoch_shift;
    static const int thrd_shift = epoch_shift + epoch_bits;

    static const uintptr_t biasedLock_mask = right_nBits(biasedLock_bits + lock_bits);
    static const uintptr_t age_mask = right_nBits(age_bits);
    static const uintptr_t epoch_mask = right_nBits(epoch_bits);
    static const uintptr_t hashCode_mask = right_nBits(hashCode_bits);

    static const uintptr_t lock_maskInPlace = right_nBits(lock_bits);
    static const uintptr_t biasedLock_maskInPlace = biasedLock_mask;
    static const uintptr_t age_maskInPlace = age_mask << age_shift;
    static const uintptr_t epoch_maskInPlace = epoch_mask << epoch_shift;
    static const uintptr_t hashCode_maskInPlace = hashCode_mask << hashCode_shift;

public:
    enum : uintptr_t {
        locked_v,
        unlocked_v,
        monitor_v,
        marked_v,
        biasedLockPattern_v = 5
    };

    MarkWord(uintptr_t _v = 0)
    : v(_v) {}

    static MarkWord encode(BasicLock* l) { return (intptr_t)l | locked_v; }

    static MarkWord encode(ObjectMonitor* m) { return (intptr_t)m | monitor_v; }

    static MarkWord encode(LangThread* jt, int a, int epoch) {
        return MarkWord((intptr_t)jt << thrd_shift | epoch << epoch_shift | a << age_shift);
    }

    uintptr_t value() { return v; }

    bool locked() { return !areMaskBitsSet(value(), unlocked_v); }
    bool biasedLocked() { return areMaskBitsSet(value(), biasedLockPattern_v); }
    LangThread* biasedLocker() {
        return (LangThread*)(value() >> thrd_shift);
    }

    int age() { return maskBits(value(), age_maskInPlace) >> age_shift; }
    int epoch() { return maskBits(value(), epoch_maskInPlace) >> epoch_shift; }
    int hashCode() { return maskBits(value() >> hashCode_shift, hashCode_mask); }

    MarkWord incrAge() { return MarkWord(value() & ~age_maskInPlace | age() << age_shift); }
    MarkWord setAge(int a) { return value() & ~age_maskInPlace | a << age_shift; }
    MarkWord incrEpoch() { return MarkWord(value() & ~epoch_maskInPlace | epoch() << epoch_shift); }

    BasicLock* lock() { return (BasicLock*)(value() & ~lock_maskInPlace); }
    ObjectMonitor* monitor() { return (ObjectMonitor*)(value() & ~lock_maskInPlace); }

    MarkWord resetLocked() { return value() & ~lock_maskInPlace; }

    MarkWord setMarked() { return MarkWord(value() & ~lock_maskInPlace | marked_v); }
    MarkWord setUnmarked() { return MarkWord(value() & ~lock_maskInPlace | unlocked_v); }

    friend class OopDesc;
private:
    uintptr_t v;
};

#endif